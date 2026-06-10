### 作者信息
**第一作者**：Yong Du, Yuchen Yan（ZJU，Central South University）
**第一通讯作者**：Yongliang Shen(ZJU)
### 研究背景、方法、目的、结论
#### 研究背景
当前对于GUI Agent的研究打量依赖于大量的强化学习手段，需要大量的像素级别的标注数据，成本较高。并且无法充分利用预测结果
#### 目的
使用模型对同一界面多次预测产生的位置分布的置信度信息引导对图像界面更加精确的定位，从而实现没有额外标注数据的情况下提升模型的预测精度
#### 方法
##### GUI-RC (Region Consistency)
该方法可以分为三个阶段
* 多样本生成（Multi-Sample Generation）
对指定的输入$s(i,j)$,生成多个预测，并且使用Temperature机制，从而提供多样的样本数据
* 空间投票机制（Spatial Voting Mechanism）

##### GUI-RCPO (Region Consistency Policy Optimization)
