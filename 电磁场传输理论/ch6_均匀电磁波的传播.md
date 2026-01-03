### 均匀平面波
* 定义：等相位面各点的场量相同，即 $\vec{E},\vec{H}$ 的方向，振幅，相位都保持不变
* 在无源无损耗区域的均匀平面波的场方程的通解
$$
\dot{E_x(z)} = E_0^+ e^{-jkz} +E_0^- e^{jkz}
$$
其中，$k = \omega \sqrt{\epsilon \mu}$
所以有
$$
\dot{\vec{E}} = \dot{E_x} \vec{e_x} = (E_0^+ e^{-jkz}+E_0^- e^{jkz})\vec{e_x}
$$
同理，磁场强度满足
$$
\dot{\vec{H}}=(H_0^+ e^{-jkz}+H_0^- e^{jkz}) \vec{e_y}
$$
* 波阻抗
$$
Z_{\omega} = \frac{E_0^+}{H_0^+} = - \frac{E_0^-}{H_0^-} = \sqrt{\frac{\mu}{\epsilon}}
$$
真空中的波阻抗为 $\frac{\mu_0}{\epsilon_0} = 120 \pi$ ，电场，磁场，传播方向三者互相垂直且满足右手螺旋关系
### 均匀平面波的传播特性
* 电磁波的时域表达式
$$
\begin{cases}
\vec{E} = Re(\dot{\vec{E}}e^{j \omega t}) = \vec{e_x} E_{om} cos (\omega t -kz \phi_0)\\
\vec{H} = \vec{e_y} H_{om} cos(\omega t -kz +\phi_0)
\end{cases}
$$
称 $\omega t$ 为时间相位， $kz$ 为空间相位
* 等位面方程
$$
\omega t -kz + \phi_0 = C
$$
* 相速度
$$
V_p = \frac{dz}{dt} = \frac{\omega}{k}=\frac{1}{\sqrt{\mu \epsilon}}
$$
* 波长 $\lambda$:空间相位 $k \lambda$ 变化  $2\pi$ 所经过的距离
$$
\lambda = \frac{2 \pi}{k}
$$
* 周期T：时间相位 $\omega t$ 变化 $2 \pi$ 所经过的时间
$$
T = \frac{2\pi}{\omega}
$$

* 波速
$$
V_p = f \lambda = \frac{\lambda}{T}
$$
#### 向任意方向传播的平面正弦波
取电磁波的传播方向为z轴，一般表达式

### 电磁波的极化
* 定义：沿z方向传播的均匀电磁波 $E_x$ 与 $E_y$ 均存在，可表示为
$$
\begin{cases}
E_x = E_{x_0}cos(\omega t-kz +\phi_{ex})\\
E_y = E_{y_0} cos (\omega t-kz+\phi_{ey})
\end{cases}
$$