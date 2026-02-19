### 作者信息
* **第一作者（同时是第一通讯作者）**：Xu Yang:School of Computer Science & Engineering, Key Lab of New Generation Artificial Intelligence Technology & Its Interdisciplinary Applications (Ministry of Education), Southeast University
### 研究背景、目的、方法和结论
#### 研究背景
语言模型（LM）已经被证实为可以通过一些模板化的提示词配置变成优秀的*few shot learner*,且学界对如何配置这些模板已经有了比较深入的研究，可以使LM再不经过重新训练的情况下完成多样的NLP任务。与此同时，对VLM的提示词工程仅仅停留在从数据库中随机提取图片-文本数据，并且效果并不好
#### 研究目的
在VLM领域复刻LM领域提示词工程的巨大成就，改善当前给予上下文的方法。
#### 研究方法
##### 图像选择策略（4种）

| 策略 | 全称 | 作用 | 实际意义 |
|------|------|------|----------|
| Random Sampling | 随机采样 | 无差别随机选图 | 当前主流做法（如Flamingo），但论文证明其效果差 |
| Similarity-based Image-Image Retrieval (SIIR) | 基于相似度的图像-图像检索 | 用视觉特征（如CLIP）找最相似的图 | 例：测试图是"骑自行车的人"，选到"骑摩托车的人" |
| Similarity-based Image-Caption Retrieval (SICR) | 基于相似度的图像-文本检索 | 先找语义匹配的文本，再取对应图像 | 例：测试图含"街道"，选到所有描述"街道"的图像 |
| Diversity-based Image-Image Retrieval (DIIR) | 基于多样性的图像-图像检索 | 按物体/场景/属性分组选代表性图像 | 例：测试图含"自行车+人+街道"，每类各选1张 |

##### 文本分配策略（4种）

| 策略 | 全称 | 作用 | 实际意义 |
|------|------|------|----------|
| Ground-Truth Captions (GTC) | 真实标注文本 | 直接用人工标注的描述 | 语言丰富但模式多样（可能干扰模型学习） |
| Model-Generated Captions (MGC) | 模型生成文本 | 用弱模型（如BLIP）生成简单描述 | 语言简单一致，但可能漏关键细节 |
| Iteratively Prompting (IP) | 迭代提示 | 用模型生成文本迭代优化 | 类似"自我修正"机制 |
| Model-Generated Captions as Anchors (MGCA) | 以模型生成文本为锚点 | 用MGC作"锚"筛选高质量GTC | 论文核心创新：结合MGC的简洁性+GTC的准确性 |
#### 结论
1. 当作为案例的图片与测试图片相似度足够高时，对于文字信息，简单并且一致的句式要比复杂多样的句式取得更加好的效果
2. 当作为案例的图片与测试图片相似度过高时，模型会有“抄捷径”的行为，不是学习文本描述的模式，而是直接照用文本描述
3. 采用MGCA方法可以让CIDEr分数平均提高20.9分

### 好在哪
对当前VLM的提示词工程作出了补充，弥补了这一块的空白，并且提出了MGCA这种相对有效的方法
