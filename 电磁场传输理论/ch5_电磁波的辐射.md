
### 时谐电磁场
* 定义：场量的诸分量都随时间做正弦或余弦形式的变化，即随时间做简谐变化
*  直角坐标系中的电场强度
\[
\vec{E}(x,y,z,t) = \vec{e}_x E_x(x,y,z,t) + \vec{e}_y E_y(x,y,z,t) + \vec{e}_z E_z(x,y,z,t)
\]

 其中
\[
\begin{cases}
E_x(x,y,z,t) = E_{xm}(x,y,z)\cos\left[\omega t + \varphi_x(x,y,z)\right] = Re[E_{xm} e^{j(\omega t+ \phi_x)}]\\[6pt]
E_y(x,y,z,t) = E_{ym}(x,y,z)\cos\left[\omega t + \varphi_y(x,y,z)\right] =Re[E_{ym} e^{j(\omega t+ \phi_y)}\\[6pt]
E_z(x,y,z,t) = E_{zm}(x,y,z)\cos\left[\omega t + \varphi_z(x,y,z) = Re[E_{ym} e^{j(\omega t+ \phi_y)}\right]
\end{cases}
\]

$E_{xm},\ E_{ym},\ E_{zm}$ ——三个坐标分量的振幅
$\varphi_x,\ \varphi_y,\ \varphi_z$ ——三个坐标分量的初始相位
从上可看出，三个分量的频率相同，但相位和振幅不同
把 $E_{xm} e^{\varphi_x} \vec{e_x}$  记作 $\vec{\dot{E_x}}$(复振幅)，则可以写成
$$
\vec{E}(x,y,z,t) = Re[(\vec{\dot{E_x}}+\vec{\dot{E_y}}+\vec{\dot{E_z}}) e^{j \omega t}]
$$
#### 场方程的复数形式
$$
\begin{cases}
\vec{\nabla} \times \dot{\vec{H}} = \dot{\vec{J}} + j \omega \dot{\vec{D}}\\ \nabla \cdot \dot{\vec{B}} = 0 \\ \nabla \cdot \dot{\vec{D} = \dot{\rho}} \\ \nabla \times \dot{\vec{E}} = - j \omega \dot{\vec{B}}
\end{cases}
$$
### 时变电磁场的边界条件
#### 电位移矢量的法向分量不连续
$$
\vec{n} \cdot (\vec{D_2}-\vec{D_1}) = \rho_s
$$
#### 电场强度的切向分量连续
$$
\vec{n} \times (\vec{E_2}-\vec{E_1}) = 0
$$
#### 磁感应强度的法向分量连续
$$
\vec{n} \cdot (\vec{B_2}-\vec{B_1}) = 0;
$$
#### 磁场强度的切向分量不连续
$$
\vec{n} \times (\vec{H_2}-\vec{H_1}) = \vec{J_s}
$$
对于理想导体来说(内部电场为0,磁场为0)
$$
\begin{cases}
\vec{n} \cdot \vec{D} = \rho_s\\
\vec{n} \times \vec{E} = 0 \\
\vec{n} \cdot \vec{B} = 0;\\
\vec{n} \times \vec{H} = \vec{J_s}
\end{cases}
$$
### 坡印廷定理
#### 电磁能量
* 储存电磁场中的能量
$$
\begin{cases}
w_e = \frac{1}{2} \vec{E} \cdot \vec{D}\\
w_m = \frac{1}{2} \vec{B} \cdot \vec{H}
\end{cases}
$$
* 转换成热能
$$
\vec{p} = \vec{J} \cdot \vec{E} 
$$
#### 坡印廷定理
$$
\begin{cases}
-\int_{V} \nabla \cdot (\vec{E} \times \vec{H})dV = \int_V (\vec{H }\cdot \frac{\partial{\vec{B}}}{\partial t}+\vec{E} \cdot \frac{\partial \vec{D}}{\partial t}+\vec{J} \cdot \vec{E})dV\\
-\int_{V} \nabla \cdot (\vec{E} \times \vec{H})dV = \frac{\partial}{\partial t} \int_V (w_m +w_e)dV +\int_V \vec{J} \cdot \vec{E} dV
\end{cases}
$$
#### 坡印亭矢量
$$
\vec{S} = \vec{E} \times \vec{H}
$$
结合坡印亭定理，得到
$$
\int_V \nabla \cdot \vec{S}dV:流出能量的功率
$$
平均坡印亭矢量：
$$
\vec{S}_{av} =  \frac{1}{T} \int_0^T \vec{S}dt
$$
#### 矢量磁位
$$
\vec{B} = \nabla \times \vec{A} = \frac{1}{2}Re(\dot{\vec{E}}\times\dot{\vec{H^*}})
$$
其中 $\vec{A}$ 称为矢量磁位