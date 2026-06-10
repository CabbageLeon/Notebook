#type:ignore
import torch
from torch import nn
from typing import Optional,Tuple,List
from torch.nn import CrossEntropyLoss
import math
from siglip_model import SiglipVisonConfig,SiglipVisionModel

class GemmaConfig():
    def __init__(
            self,
            vocab_size,
            hidden_size,
            intermediate_size,
            num_hidden_layers,
            num_attention_heads,
            num_key_value_heads,
            head_dim=256,
            max_position_embeddings=8192,
            rms_norm_eps=1e-6,
            rope_theta=10000.0,
            attention_bias=False,
            attention_dropout=0.0,
            pad_token_id=None,
            **kwargs,
        ):
        super().__init__()
        self.vocab_size = vocab_size
        self.max_position_embeddings = self.max_position_embeddings
        self.hidden_size = hidden_size
        self.intermediate_size = intermediate_size
        self.num_hidden_layers = num_hidden_layers
        self.num_attention_heads = num_attention_heads
        self.head_dim = head_dim
        self.max_position_embeddings = max_position_embeddings
        self.num_key_value_heads = num_key_value_heads
        self.rms_norm_eps = rms_norm_eps
        self.rope_theta = rope_theta
        self.attention_bias = attention_bias
        self.attention_dropout = attention_dropout
        self.pad_token_id = pad_token_id



class PliGemmaConfig():
    def __init__(
            self,
            vision_config=None,
            text_config=None,
            ignore_index=-100,
            image_token_index=256000,
            vocab_size=257152,
            projection_dim=2048,
            pad_token_id=None,
            **kwargs,            
    ):
        super().__init__()
        self.ignore_index = ignore_index
        self.image_token_index = image_token_index
        self.vocab_size = vocab_size
        self.projection_dim = projection_dim
        self.hidden_size = vocab_size
        self.projection_dim = projection_dim
        self.vocab_size = vocab_size
        self.vision_config = vision_config
        self.pad_token_id = pad_token_id

        self.vision_config = SiglipVisonConfig(**vision_config)
        self.text_config = text_config
        self.text_config = GemmaConfig(**text_config,pad_token_id=pad_token_id)
        self.vocab_size = self.text_config.vocab_size

        self.text_config.num_image_tokens = (self.vision_config.image_size // self.vision_config.patch_size) ** 2
        self.vision_config.projection_dim = projection_dim

class PaliGemmaForConditionalGeneration(nn.Module):
    def __init__(self, config:PaliGemmaConfig) -> None:
        super().__init__()
        self.config = config
        self.vision_tower = SiglipVisionModel(config.vision_config)
        self.multi_modal_projector = PaliGemmaMultiModalProjector(config)
        self.vocab_size = config.vocab_size

        language_model = GemmaFoeCasualLM(config.text_config)
        self.language_model = language_model

        self.pad_token_id = self.config.pad_token_id if self.config.pad_token_id is not None else -1
    # embedding层的操作和最后的projection层的操作可以看作互逆运算，因此可以权重共享来节省显存开销
    def tie_weights(self):
        return self.language_model.tie_weights()
    
    def _merge_input_ids_with_image_features(
            self,
            image_features: torch.Tensor,
            input_embeds:torch.Tensor,
            input_ids:torch.Tensor,
            attention_mask:torch.Tensor,
            kv_cache:Optional[KVCache] = None
    ):
        _,_,embed_dim = image_features.shape
        batch_size,seq_len = input_ids.shape
        dtype,device = input_embeds.dtype,input_embeds.device

        # [batch_size,seq_len,hidden_size]
        scaled_image_features = image_features/(self.config.hidden_size**0.5)
        #Combine the embeddings of image tokens,the text tokens and mask tokens
        final_embedding = torch.zeros(batch_size,seq_len,embed_dim,dtype=input_embeds.dtype,device=input_embeds.device)
        #[batch,size,seq_len]:text tokens
        text_mask = (input_ids != self.config.image_token_index) & (input_ids != self.pad_token_id)
        #[batch_size,seq_len]:image_tokens
        image_mask = input_ids == self.config.image_token_index
        #[batch_size,seq_len]:padding tokens
        pad_mask = input_ids == self.pad_token_id
        #扩展mask的维度
        #[batch_size,seq_len]->[batch_size,seq_len,embed_dim]
        text_mask_expanded = text_mask.unsqueeze(-1).expand(-1,-1,embed_dim)
        pad_mask_expaned = pad_mask.unsqueeze(-1).expand(-1,-1,embed_dim)
        image_mask_expanded = image_mask.unsqueeze(-1).expand(-1,-1,embed_dim)

        final_embedding = torch.where(text_mask_expanded,input_embeds,final_embedding)
        final_embedding = final_embedding.masked_scatter(image_mask_expanded,scaled_image_features)
        final_embedding = torch.where(pad_mask_expaned,torch.zeros_like(final_embedding),final_embedding)
    def forward(
            self,
            input_ids: torch.LongTensor = None,
            pixel_values: torch.FloatTensor = None,
            attention_mask:Optional[torch.Tensor] = None,
            kv_cache: Optional[KVCache] = None,
    )-> Tuple:
        assert torch.all(attention_mask == 1),"the input can't be padded"
        #1.extra the input embeddings
        # shape: (batch_size,seq_len,hidden_size)
        input_embeds = self.language_model.get_input_embeddings()(input_ids)

        #2. merge text and images
        #[batch_size,channels,height,width]-> [batch_size,num_patches,embed_dim]
        seleted_image_features = self.vision_tower([pixel_values.to(input_embeds.dtype)])
        # [batch_size,num_patches,embed_dim]->[batch_size,num_patches,hidden_size]
        image_features = self.multi_modal_projector(seleted_image_features)

        #merge the embeddings of the text tokens and the image tokens
        input_embeds, attention_mask, position_ids = self._merge_input_ids_with_image_features(
            image_features,
            input_embeds,
            input_ids,
            attention_mask,
            kv_cache
        )

        outputs = self.language_model(
            attention_mask=attention_mask,
            position_ids=position_ids,
            input_embeds=input_embeds,
            kv_cache=kv_cache
        )
        return outputs
