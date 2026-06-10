import torch
from torch import nn
from torch.nn import functional as F

class VAE_Encoder(nn.Sequential):

    def __init__():
        super.__init__(
            #(batch_size,channel,height,width)->(batch_size,128,height,width)
            nn.Conv2d(3,128,kernel_size=3,padding=1),
            #(batch_size,128,height,width)->(batch_size,128,height,width)
            VAE_ResidualBlock(128,128),
            #(batch_size,128,height,width)->(batch_size,128,height,width)
            VAE_ResidualBlock(128,128),
            #(batch_size,128,height,width)->(batch_size,128,height/2,width/2)
            nn.Conv2d(128,128,kernel_size=3,stride=2,padding=0),
            #(batch_size,128,height/2,width/2)->(batch_size,256,height/2,width/2)
            VAE_ResidualBlock(128,256),
            #(batch_size,128,height/2,width/2)->(batch_size,256,height/2,width/2)
            VAE_ResidualBlock(256,256),
            #(batch_size,256,height/2,width/2)->(batch_size,256,height/4,width/4)
            nn.Conv2d(256,256,kernel_size=3,stride=2,padding=0),
            #(batch_size,256,height/4,width/4)->(batch_size,512,height/4,width/4)
            VAE_ResidualBlock(256,512),
            #(batch_size,512,height/4,width/4)->(batch_size,512,height/4,width/4)
            VAE_ResidualBlock(512,512),
            #(batch_size,512,height/4,width/4)->(batch_size,512,height/8,width/8)
            nn.Conv2d(512,512,kernel_size=3,stride=2,padding=0),
            #(batch_size,512,height/8,width/8)->(batch_size,512,height/8,width/8)
            VAE_ResidualBlock(512,512),
            VAE_ResidualBlock(512,512),
            VAE_ResidualBlock(512,512),
            #(batch_size,512,height/8,width/8)->(batch_size,512,height/8,width/8)
            VAE_AttentionBlock(512),
            #(batch_size,512,height/8,width/8)->(batch_size,512,height/8,width/8)
            nn.GroupNorm(32,512),
            #(batch_size,512,height/8,width/8)->(batch_size,512,height/8,width/8)
            nn.SiLU(),
            #(batch_size,512,height/8,width/8)->(batch_size,8,height/8,width/8)
            nn.Conv2d(8,8,kernel_size=1,padding=0)
        )

    def forward(self,x:torch.Tensor,noise:torch.Tensor)->torch.Tensor:
        # x:(batch_size,channel,height,width)
        # noise:(batch_size,out_channels,height/8,width/8)

        for module in self:
            if getattr(module,'stride',None) == (2,2):
                #(padding_left,padding_right,padding_top,padding_bottom)
                x = F.pad(x,(0,1,0,1))
            x = module(x)
        
        #这步操作把x沿着维度序号为1（channel）切分，变成(batch_size,8,height/8,width/8)->两个(batch_size,4,height/8,width/8)
        #分别解释成均值和对数方差
        mean,log_variance = torch.chunk(x,2,dim=1)
        log_variance = torch.clamp(log_variance,-30,20)
        variance = log_variance.exp()
        std_variance = variance.sqrt()

        #重采样（reparameter）
        x = mean + std_variance*noise
        #缩放输出
        x*=0.1825
        return x
         