# Chapter 3 对称密钥加密以及伪随机性

!!! quote 引言
    在上一讲中，我们假设敌手拥有无限计算能力，这样的方案叫做**信息理论安全（information-theoretic notions of security）**，又称**完美安全**，而本讲讨论的**计算安全（Computational security）** 稍弱一些，包含了以下两个放宽条件：
      1. 安全性仅在对抗**有效 (指在可行的时间里运行)** 的敌手时存在
      2. 敌手潜在的成功概率是**非常小**的

## 1 密码学的计算方法
### 1. 1 有效的算法和可忽略的成功概率

!!! info 概念补充
    <br>

    * 如果对于每个多项式 $p(\cdot)$ ，存在一个 $N$ ，使得对于所有的整数 $n > N$ ，都满足 $f(n) < \frac{1}{p(n)}$，则称函数 $f$ 为**可忽略的（negligible）**

    * 如果存在一个多项式 $p(\cdot)$ ，使得对于每个输入 $x \in \{0,1\}^*$ ，$A(x)$ 的计算最多在 $p(|x|)$ 个步骤内终止（$|x|$ 指字符串 $x$ 的长度），则该算法 $A$ 被认为**在多项式时间内运行**

    * 有效的运算是指能够在**概率多项式时间（PPT, probabilistic polynomial-time）** 内执行的计算

在课程中，我们使用渐进方法来定义计算安全，即：

* 如果每个 $\text{PPT}$ 敌手以**可忽略的**概率成功攻破一个方案，那么该方案是安全的。

!!! example
    函数 $2^{-n}$，$2^{-\sqrt{n}}$ 以及 $n^{-\log n}$ 都是可忽略的函数，但它们接近零的速度是非常不同的

!!! note 补充
    令 $\text{negl}_1$ 和 $\text{negl}_2$ 为可忽略函数，则：
      1. 函数 $\text{negl}_3 (n) = \text{negl}_1 (n) + \text{negl}_2 (n)$ 是可忽略的
      2. 对于任何正多项式 $p$，函数 $\text{negl}_4 (n) = p(n) \cdot \text{negl}_1 (n)$ 是可忽略的

### 1. 2 规约证明
1. 指定 $\text{PPT}$ 敌手 $\mathcal{A}$ 攻击 $\Pi$，将敌手的成功概率表示为 $\varepsilon(n)$
2. 构造一个叫做**规约**的有效算法 $\mathcal{A}'$，该算法将敌手 $\mathcal{A}$ 作为子程序来使用，试图解决难题 $X$。这里很重要的一点是，$\mathcal{A}'$ 对 $\mathcal{A}$ 是如何工作的一无所知，$\mathcal{A}'$ 知道的唯一的事情就是 $\mathcal{A}$ 想要攻击 $\Pi$。所以，指定难题 $X$ 的某个输入实例 $x$，算法 $\mathcal{A}'$ 将会对 $\mathcal{A}$ 模拟出一个 $\Pi$ 的实例，满足：
   1. 就 $\mathcal{A}$ 而言，它和 $\Pi$ 交互。更正式地说，当 $\mathcal{A}$ 作为子程序被 $\mathcal{A}'$ 运行时，$\mathcal{A}$ 的分布应该和当 $\mathcal{A}$ 自身和 $\Pi$ 交互时的分布是相同的（或至少是很接近的）
   2. 如果 $\mathcal{A}$ 成功攻破了由 $\mathcal{A}'$ 模拟的 $\Pi$ 的实例，则 $\mathcal{A}'$ 解决给出的难题实例 $x$ 成功的概率至少为多项式的倒数，即 $1/p(n)$

<img src="images/image3-1.png" style="display: block; width: 50%; margin: 0 auto;" />
<br>

3. 总起来考虑，如果 $\varepsilon(n)$ 不是可忽略的，则 $\mathcal{A}'$ 解决难题 $X$ 的概率为不可忽略的概率 $\varepsilon(n)/p(n)$。如果 $\mathcal{A}$ 是有效的，则存在有效的算法 $\mathcal{A}'$ 以不可忽略的概率解决 $X$，与原假设矛盾
4. 因而结论是，给定一个关于 $X$ 的假设，不存在有效的敌手 $\mathcal{A}$ 能够以不可忽略的概率成功攻破 $\Pi$，换句话说，$\Pi$ 是计算上安全的

!!! hint
    规约证明的纯文字叙述较为晦涩，简而言之，就是假设有敌手 $\mathcal{A}$ 能攻破 $\Pi$，则可构造以 $\mathcal{A}$ 为子程序的敌手 $\mathcal{R}^{\mathcal{A}}$ 攻破 $\Pi'$，常用于反证法

## 2 EAV-Secure
!!! info 对称密钥加密方案
      <br>

      1. $k \leftarrow \text{Gen}(1^n)$，$|k| \geq n$
    
      2. $c \leftarrow \text{Enc}_k(m)$，$m \in \{0,1\}^*$ 

      3. $m := \text{Dec}_k(c)$

* 如果对于所有 $\text{PPT}$ 敌手 $\mathcal{A}$ ，存在一个可忽略函数 $\text{negl}$ 使得：
$$\Pr\left[\text{PrivK}^{\text{eav}}_{\mathcal{A},\Pi}(n) = 1\right] \leqslant \frac{1}{2} + \text{negl}(n)$$

  则一个对称密钥加密方案 $\Pi = (\text{Gen}, \text{Enc}, \text{Dec})$ 具备**在窃听者存在的情况下不可区分**的加密

使用一个固定比特 $b$，用 $\text{output}\left( \text{PrivK}^{\text{eav}}_{\mathcal{A},\Pi}(n,b) \right)$ 来表示 $\mathcal{A}$ 在 $\text{PrivK}^{\text{eav}}_{\mathcal{A},\Pi}(n,b)$ 中的输出比特 $b'$，则有等价定义：

* 如果对所有的概率多项式时间的敌手 $\mathcal{A}$ ，存在一个可忽略函数 $\text{negl}$ 使得：
$$\left| \Pr\left[ \text{output}\left( \text{PrivK}^{\text{eav}}_{\mathcal{A},\Pi}(n,0) \right) = 1 \right] - \Pr\left[ \text{output}\left( \text{PrivK}^{\text{eav}}_{\mathcal{A},\Pi}(n,1) \right) = 1 \right] \right| \leqslant \text{negl}(n)$$

  则对称密钥加密方案 $\Pi = (\text{Gen}, \text{Enc}, \text{Dec})$ 具有**窃听者存在的情况下不可区分性**


## 3 伪随机发生器（Pseudorandom Generator, PRG）
### 3. 1 直观定义
直观上来看，如果**没有多项式时间的区分器能够区分一个根据 $D$ 采样的字符串和一个均匀随机选择的字符串**，则一个分布 $D$ 是伪随机的。

* 令 $\ell(\cdot)$ 为多项式，$G$ 为确定多项式时间算法，该算法满足：对于任何输入 $s \in \{0,1\}^n$ ，算法 $G$ 输出一个长度为 $\ell(n)$ 的字符串。如果满足下面两个条件，则称 $G$ 是一个伪随机发生器：
  1. （**扩展性：**）对每个 $n$ 来说，满足 $\ell(n) > n$
  2. （**伪随机性：**）对所有的概率多项式时间的区分器 $D$ 来说，存在一个可忽略函数 $\text{negl}$ ，满足 $$|\Pr[D(r) = 1] - \Pr[D(G(s)) = 1]| \leq \text{negl}(n)$$

  其中 $r$ 是从 $\{0,1\}^{\ell(n)}$ 中均匀随机选择的，种子 $s$ 是从 $\{0,1\}^n$ 中均匀随机选择的，函数 $\ell(\cdot)$ 被称为 $G$ 的扩展系数。

### 3.2 计算不可区分性（Computational Indistinguishability）
!!! info 概念补充
    <br>

    * **概率总体（Probability Ensemble）**
      * 无限的概率分布序列
      * 若对每个自然数 $n$ ，都存在一个概率分布 $X_n$ ，则集合 $\mathcal{X} = \{ X_n \}_{n \in \mathbb{N}}$ 称为一个概率总体
      * 若分布 $X_n$ 可通过某个函数 $t$ 与另一序列的分布关联，即 $X_n = Y_{t(n)}$ ，则概率总体可表示为 $\{ Y_{t(n)} \}_{n \in \mathbb{N}}$
    <br>
    * **高效可采样的概率总体（Efficiently Sampleable Probability Ensemble）**
      * 若概率总体 $\mathcal{X} = \{ X_n \}_{n \in \mathbb{N}}$ 满足：存在一个**概率多项式时间算法 $S$ **，使得“算法 $S$ 输入 $1^n$ （长度为 $n$ 的全 1 字符串，传递安全参数规模）后输出的随机变量”与“分布 $X_n$ 的随机变量”**同分布**，则称 $\mathcal{X}$ 是**高效可采样的**

计算不可区分性的实际定义与概率总体有关，以下是对两个分布不可区分的形式化定义：

* 两个概率总体 $X = \{X_n\}_{n \in \mathbb{N}}$ 和 $Y = \{Y_n\}_{n \in \mathbb{N}}$ 是**计算不可区分**的，表示为 $X \stackrel{c}{\equiv} Y$，如果对于每一个概率多项式时间的区分器 $D$ ，都存在一个可忽略函数 $\text{negl}$，使得：
$$|\Pr[D(1^n, X_n) = 1] - \Pr[D(1^n, Y_n) = 1]| \leq \text{negl}(n)$$

  其中标记 $D(1^n, X_n)$ 表明 $x$ 的选取符合分布 $X_n$ ，然后运行 $D(1^n, x)$ 。

!!! 
    计算不可区分性具有传递性，即：若 $\mathcal{X} \stackrel{c}{\equiv} \mathcal{Y}$ 且 $\mathcal{Y} \stackrel{c}{\equiv} \mathcal{Z}$，则 $\mathcal{X} \stackrel{c}{\equiv} \mathcal{Z}$


伪随机性只是计算不可区分性的一个特例，令 $U_{l(n)}$ 表示 $\{0,1\}^{l(n)}$ 上的**均匀分布(uniform distribution)**，则有下列定义：

* 如果对于某个多项式 $l$ ，全体 $X$ 和全体 $U = \{U_{l(n)}\}_{n \in \mathbb{N}}$ 是计算不可区分的，则全体 $X = \{X_n\}_{n \in \mathbb{N}}$ 是伪随机的。

据此，我们可以对伪随机发生器重新进行定义：

* 令 $l(\cdot)$ 是多项式，同时令 $G$ 为（确定的）多项式时间算法，其中对于所有 $s$ 有 $|G(s)| = l(|s|)$ 成立。如果下列两个条件成立，就称 $G$ 是伪随机发生器：
  1. （**可扩展性：**）对于每一个 $n$ 有 $l(n) > n$ 成立
  2. （**伪随机性：**）全体 $\{G(U_n)\}_{n \in \mathbb{N}}$ 是伪随机的

## 4 构造安全加密方案
### 4. 1 一个安全的定长加密方案
给出使用伪随机发生器的加密方案如下：

<img src="images/image3-2.png" style="display: block; width: 40%; margin: 0 auto;" />
<br>
<img src="images/image3-3.png" style="display: block; width: 90%; margin: 0 auto;" />
<br>

* **若 $G$ 是伪随机发生器，则上述加密方案是窃听者存在下的不可区分长密钥对称加密方案。**

!!! abstract 证明（教材中给出的证明方法）
    假设存在概率多项式时间敌手 $\mathcal{A}$ ，定义敌手优势：
    $$\varepsilon(n) \stackrel{\text{def}}{=} \Pr\left[ \text{PrivK}^{\text{eav}}_{\mathcal{A},\Pi}(n) = 1 \right] - \frac{1}{2}$$

    构造区分器 $D$，指定字符串 $w \in \{0,1\}^{\ell(n)}$ 作为输入，假设 $n$ 能够被 $\ell(n)$ 确定：
      1. 运行 $\mathcal{A}(1^n)$ 获取消息对 $m_0, m_1 \in \{0,1\}^{\ell(n)}$
      2. 随机选比特 $b \leftarrow \{0,1\}$ ，计算密文 $c := w \oplus m_b$
      3. 将 $c$ 给 $\mathcal{A}$ ，若 $\mathcal{A}$ 输出 $b' = b$ ，则 $D$ 输出 1，否则输出 0

    * **当 $w$ 是真随机串**：此时加密等价于一次一密（完善保密），令 $\widetilde{\Pi}$ 为带安全参数的一次一密方案，则：
    $$\Pr\left[ D(w) = 1 \right] = \Pr\left[ \text{PrivK}^{\text{eav}}_{\mathcal{A},\widetilde{\Pi}}(n) = 1 \right] = \frac{1}{2}$$

    * **当 $w = G(k)$**：此时加密是方案 $\Pi$ ，故
      \[
      \Pr\left[ D(G(k)) = 1 \right] = \Pr\left[ \text{PrivK}^{\text{eav}}_{\mathcal{A},\Pi}(n) = 1 \right] = \frac{1}{2} + \varepsilon(n)
      \]

    由上述分析，区分器 $D$ 对真随机串和 $G$ 输出的区分优势为：
    $$\left| \Pr\left[ D(w) = 1 \right] - \Pr\left[ D(G(k)) = 1 \right] \right| = \varepsilon(n)$$
    
    因为 $G$ 是伪随机发生器，所以 $\varepsilon(n)$ 必须是**可忽略函数**，结合 $\varepsilon(n)$ 的定义可得，加密方案 $\Pi$ 满足“窃听者存在下的不可区分加密”，证毕。

!!! abstract 证明（规约证明）
    运用反证法，假设**存在敌手 A 能攻破上述加密方案的 EAV-安全**，则可以**构造一个敌手 B 来攻破 PRG 的安全性**

    <img src="images/image3-4.jpg" style="display: block; width: 60%; margin: 0 auto;" />

    作规约图如上，假设 $Pr[\text{A wins EAV}] = \frac{1}{2} + \Delta$，其中 $\Delta$ 表示 not small，则：
    $$\begin{align*}
    Pr[R^A \text{ wins PRG}] &= P[b = 0] \cdot Pr[R^A \text{ wins} \mid b = 0] + P[b = 1] \cdot Pr[R^A \text{ wins} \mid b = 1] \\
    &= \frac{1}{2}Pr[\text{A wins EAV}] + \frac{1}{2} \cdot \frac{1}{2} = \frac{1}{2} + \frac{\Delta}{2}
    \end{align*}$$

    说明 $R^A$ 可以攻破 PRG，矛盾！故有 EAV-Secure.

!!! hint
    其实上述两种证明方法本质上是一样的，本门课程中通常使用规约证明的方法

### 4. 2 处理变长消息 
* 一个确定的多项式时间算法 $G$，如果满足以下三个条件，则 $G$ 是一个**输出长度可变的伪随机发生器**，如果满足以下条件：
    1. 令 $s$ 为一个字符串，整数 $\ell > 0$。则 $G(s,1^\ell)$ 输出一个长度为 $\ell$ 的字符串
    2. 对所有的 $s, \ell, \ell'$， $\ell < \ell'$，字符串 $G(s,1^\ell)$ 是 $G(s,1^{\ell'})$ 的前缀
    3. 定义 $G_\ell(s) \stackrel{\text{def}}{=} G(s,1^{\ell(|s|)})$，则对于每个多项式 $\ell(\cdot)$，有 $G_\ell$ 是一个扩展因子为 $\ell$ 的伪随机发生器

任何标准的伪随机发生器都能够被转化成为一个输出长度可变的伪随机发生器。

与定长加密方案相似的，可以给出构造方案：
$$c := G(k,1^{|m|}) \oplus m，m := G(k,1^{|c|}) \oplus c$$

### 4. 3 流密码（Stream Ciphers）和多个加密
上述构造方案被称作流密码，其加密的执行是先生成一个伪随机比特流，然后将该比特流和明文做异或运算。


!!! note
    流密码有同步模式与非同步模式两种工作机制：

    <img src="images/image3-5.png" style="display: block; width: 80%; margin: 0 auto;" />

* 一个对称密钥加密方案 $\Pi = (\text{Gen}, \text{Enc}, \text{Dec})$，如果对所有的概率多项式时间敌手 $\mathcal{A}$，存在一个可忽略函数 $\text{negl}$，满足 $$\Pr\left[ \text{PrivK}^{\text{mult}}_{\mathcal{A},\Pi}(n) = 1 \right] \leqslant \frac{1}{2} + \text{negl}$$

  则称其具备**窃听者存在的情况下不可区分多次加密**

!!! info 多消息窃听实验 $\text{PrivK}^{\text{mult}}_{\mathcal{A},\Pi}(n)$
    <br>

    1. 敌手 $\mathcal{A}$ 被给定输入 $1^n$ ，输出一对消息向量 $\vec{M_0} = (m_0^1, \dots, m_0^t)$ 以及 $\vec{M_1} = (m_1^1, \dots, m_1^t)$ ，对于所有 $i$ ，满足 $|m_0^i| = |m_1^i|$
    2. 通过运行 $\text{Gen}(1^n)$ 生成一个密钥 $k$ 和选择一个随机比特 $b \leftarrow \{0,1\}$ 。对于所有 $i$ ，计算密文 $c^i \leftarrow \text{Enc}_k(m_b^i)$ ，并且将密文向量 $\vec{C} = (c^1, \dots, c^t)$ 给 $\mathcal{A}$
    3. $\mathcal{A}$ 输出一个比特 $b'$
    4. 如果 $b' = b$ ，该实验的输出为 1，否则输出 0。

值得注意的，**单个加密的安全并不意味着在多次加密下的安全**，即：
* 存在这样的对称密钥加密方案，满足窃听者存在情况下不可区分的加密，但不满足窃听者存在情况下不可区分的多次加密。

!!! abstract 证明
    仍然使用前面构造的加密方案，其单次加密的安全性已经得证，构造敌手 $\mathcal{A}$ 参与多消息窃听实验 $\text{PrivK}^{\text{mult}}_{\mathcal{A},\Pi}(n)$ ，执行如下操作：
    * 输出消息向量 $\vec{M_0} = (0^n, 0^n)$ 和 $\vec{M_1} = (0^n, 1^n)$，满足所有位置明文长度相等

    * 接收密文向量 $\vec{C} = (c^1, c^2)$ ，若 $c^1 = c^2$ 则输出 $b' = 0$ ，否则输出 $b' = 1$

    我们采用的构造方法的加密函数 $\text{Enc}$ 是**确定函数**，相同密钥和明文会产生相同密文，所以有：
    * 若 $b = 0$ ：加密 $\vec{M_0}$ ，两个明文均为 $0^n$ ，故 $c^1 = \text{Enc}_k(0^n) = c^2$ ，敌手输出 $b' = 0 = b$
    * 若 $b = 1$ ：加密 $\vec{M_1}$ ，明文分别为 $0^n$ 和 $1^n$ ，故 $c^1 = \text{Enc}_k(0^n) \neq \text{Enc}_k(1^n) = c^2$ ，敌手输出 $b' = 1 = b$

    综上，敌手 $\mathcal{A}$ 输出 $b' = b$ 的概率为 $1$，该加密方案不具备窃听者存在情况下的不可区分多次加密，命题得证

根据以上可以知道，**相同消息被重复发送是危险的，概率加密是必要的**，可形式化为以下定理：
* 令 $\Pi = (\text{Gen}, \text{Enc}, \text{Dec})$ 为一个加密方案， $\text{Enc}$ 是密钥和消息的一个确定函数，则 $\Pi$ 不具备窃听者存在情况下不可区分多次加密。

### 4. 4 提高扩展系数
* 如果存在扩展系数为 $l(n) = n + 1$ 的伪随机发生器 $\hat{G}$，那么对于任意多项式 $p(n) > n$，存在扩展系数为 $l(n) = p(n)$ 的伪随机发生器 $G$ 

!!! hint 构造方法
    令输入的种子 $s \in \{0,1\}^n$，则 $G'$ 的构造方法如下：
    1. 令 $p'(n) = p(n) - n$，这是所期望的 $G$ 对输入长度的扩展量
    2. 设 $s_0 := s$ ，对于 $i = 1, \cdots, p'(n)$ ，则：
       1. 令 $s'_{i-1}$ 表示 $s_{i-1}$ 的开始 $n$ 比特，令 $\sigma_{i-1}$ 表示剩下的 $n - 1$ 比特（当 $i = 1$ 时， $\sigma_0$ 为空串）
       2. 设 $s_i := (\hat{G}(s'_{i-1}), \sigma_{i-1})$ 
    3. 输出 $s_{p'(n)}$

    简而言之，就是如果我们有一个 “每次能多造 1 位伪随机数” 的基础工具，想造多长的伪随机串，就把这个工具反复用多少次，每次多攒 1 位，最后凑出需要的长度。

    另外，密码学中常用 $||$ 表示拼接，例如上式可以写作 $s_i := \hat{G}(s'_{i-1}) \, || \, \sigma_{i-1}$

## 5 选择明文攻击（CPA）的安全性
**加密预言机 (encryption oracle)** 可视为一个黑盒子，会使用密钥 $k$ 加密 $\mathcal{A}$ 选择的消息，在 **选择明文攻击 (chosen-plaintext attacks)** 中，敌手 $\mathcal{A}$ 被允许和加密预言机自由交互。当 $\mathcal{A}$ 询问预言机并提供明文消息 $m$ 作为输入时，预言机将返回密文 $c \leftarrow \text{Enc}_k(m)$，当 $\text{Enc}$ 是随机的时，预言机每次回答一个询问时都会保证新的随机性。

安全性的定义要求：即使 $\mathcal{A}$ 具备访问加密预言机能力， $\mathcal{A}$ 也不能区分两个任意消息的加密。

!!! info CPA 不可区分实验 $\text{PrivK}^{\text{cpa}}_{\mathcal{A},\Pi}(n)$
    <br>

    1. $k \leftarrow \text{Gen}(1^n)$
    2. 输入 $1^n$ 给敌手 $\mathcal{A}$，敌手 $\mathcal{A}$ 可以访问预言机 $\text{Enc}_k(\cdot)$ ，输出一对长度相等的消息 $m_0, m_1$
    3. $b \leftarrow \{0,1\}$，$c \leftarrow \text{Enc}_k(m_b)$，交给 $\mathcal{A}$
    4. 敌手 $\mathcal{A}$ 继续访问预言机 $\text{Enc}_k(\cdot)$ ，输出一个比特 $b'$
    5. 如果 $b = b'$，该实验的输出被定义为 1，否则定义为 0，若 $\text{PrivK}^{\text{cpa}}_{\mathcal{A},\Pi}(n) = 1$ ，则认为 $\mathcal{A}$ 成功

* 一个对称密钥加密方案 $\Pi = (\text{Gen}, \text{Enc}, \text{Dec})$，如果对所有的概率多项式敌手 $\mathcal{A}$，存在一个可忽略函数 $\text{negl}$，使得
$$\Pr\left[ \text{PrivK}^{\text{cpa}}_{\mathcal{A},\Pi}(n) = 1 \right] \leqslant \frac{1}{2} + \text{negl}(n)$$

  则是选择明文攻击（CPA）条件下的不可区分加密

**任何方案如果是选择明文攻击条件下的不可区分加密，则也是窃听者存在的情况下不可区分加密**，因为 $\text{PrivK}^{\text{eav}}$ 是 $\text{PrivK}^{\text{cpa}}$ 的一种特殊情况，即敌手没有使用预言机。

和多次加密的安全一样，任何确定加密方案都不能抵御选择明文攻击，即：**任何 CPA 安全的加密方案必须是概率性的**。

!!! info LR 预言机实验 $\text{PrivK}^{\text{LR-cpa}}_{\mathcal{A},\Pi}(n)$
    <br>

    1. $k \leftarrow \text{Gen}(1^n)$，$b \leftarrow \{0,1\}$
    2. 输入 $1^n$ 给敌手 $\mathcal{A}$，敌手 $\mathcal{A}$ 可以访问预言机 $\text{LR}_{k,b}(\cdot,\cdot)$
    3. 敌手 $\mathcal{A}$ 输出一个比特 $b'$
    4. 如果 $b = b'$，该实验的输出被定义为 1，否则定义为 0，若 $\text{PrivK}^{\text{LR-cpa}}_{\mathcal{A},\Pi}(n) = 1$ ，则认为 $\mathcal{A}$ 成功

相似的，将 CPA 单次加密扩展到多次加密，则有：

* 一个对称密钥加密方案 $\Pi = (\text{Gen}, \text{Enc}, \text{Dec})$，如果对所有的概率多项式敌手 $\mathcal{A}$，存在一个可忽略函数 $\text{negl}$，使得
$$\Pr\left[ \text{PrivK}^{\text{LR-cpa}}_{\mathcal{A},\Pi}(n) = 1 \right] \leqslant \frac{1}{2} + \text{negl}(n)$$

  则是选择明文攻击（CPA）条件下的不可区分多次加密

!!! hint 注意
    CPA 实验是敌手先自由要密文，再选消息对赌密文；LR 实验是敌手直接和预言机赌加密的是左消息还是右消息，两者本质等价，但交互形式和预言机功能不同，LR 实验更直接地刻画了 CPA 下的不可区分性，可直接运用于多次加密。

与窃听敌手（EAV）的情况不同的是，**单次加密的 CPA 安全即意味着多次加密的 CPA 安全**，即：任何在选择明文攻击条件下的不可区分加密的对称密钥加密方案，也是在选择明文攻击条件下的不可区分多次加密方案。

!!! note 证明：混合论证（Hybrid Argument）
    定义 $n+1$ 个中间游戏 $\text{Game}_0, \text{Game}_1, \dots, \text{Game}_n$，其中：  
    
    **$\text{Game}_k$规则** 为对第 $1 \sim k$ 个消息对用 $b=1$ 处理，对第 $k+1 \sim n $个消息对用 $b=0$ 处理，其返回的密文序列为：$$(c_1, \dots, c_k, c_{k+1}, \dots, c_n) = (\text{Enc}(sk, m_1^1), \dots, \text{Enc}(sk, m_1^k), \text{Enc}(sk, m_0^{k+1}), \dots, \text{Enc}(sk, m_0^n))$$  
    
    考虑相邻游戏 $\text{Game}_k$ 和 $\text{Game}_{k+1}$，二者仅第 $k+1$ 个消息对的处理方式不同，构造IND-CPA攻击者 $\mathcal{B}$，其行为如下：  
    1. $\mathcal{B}$接收IND-CPA挑战者的公钥$pk$，并需要猜测IND-CPA的挑战比特$b$（$b=0$对应加密$m_0$，$b=1$对应加密$m_1$）。  
    2. $\mathcal{B}$模拟$\text{Game}_k$或$\text{Game}_{k+1}$的挑战者，与LR-IND-CPA攻击者$\mathcal{A}$交互：  
      - 接收$\mathcal{A}$提交的$n$个消息对$(m_0^1, m_1^1), \dots, (m_0^n, m_1^n)$。  
      - 对第$1 \sim k$个消息对：加密$m_1^i$（生成$c_1, \dots, c_k$）。  
      - 对第$k+1$个消息对：将$(m_0^{k+1}, m_1^{k+1})$作为IND-CPA的挑战消息对提交给IND-CPA挑战者，接收挑战密文$c_{k+1}$（此时$c_{k+1}$是$\text{Enc}(sk, m_b^{k+1})$，$b$是IND-CPA的挑战比特）。  
      - 对第$k+2 \sim n$个消息对：加密$m_0^i$（生成$c_{k+2}, \dots, c_n$）。  
      - 将密文序列$(c_1, \dots, c_n)$发送给$\mathcal{A}$，接收$\mathcal{A}$的猜测$b'$。  
    3. $\mathcal{B}$输出$b'$作为对IND-CPA挑战比特的猜测。  

    * 若 IND-CPA 的挑战比特$b=0$，则$c_{k+1} = \text{Enc}(sk, m_0^{k+1})$，此时$\mathcal{B}$模拟的是$\text{Game}_k$；  
    - 若IND-CPA的挑战比特$b=1$，则$c_{k+1} = \text{Enc}(sk, m_1^{k+1})$，此时$\mathcal{B}$模拟的是$\text{Game}_{k+1}$。  

    因此，$\mathcal{A}$在$\text{Game}_k$和$\text{Game}_{k+1}$中的区分优势，等于$\mathcal{B}$在IND-CPA中的优势：  
    $$\left| \Pr[\mathcal{A} \text{在}\text{Game}_k\text{中输出}1] - \Pr[\mathcal{A} \text{在}\text{Game}_{k+1}\text{中输出}1] \right| = \text{Adv}_{\text{IND-CPA}}(\mathcal{B})$$  

    由IND-CPA的安全性，$\text{Adv}_{\text{IND-CPA}}(\mathcal{B})$是**可忽略的**，因此$\text{Game}_k$与$\text{Game}_{k+1}$不可区分。

    $\because \left| \Pr[\mathcal{A} \text{在}\text{Game}_0\text{中输出}1] - \Pr[\mathcal{A} \text{在}\text{Game}_n\text{中输出}1] \right| \leq \sum_{k=0}^{n-1} \left| \Pr[\mathcal{A} \text{在}\text{Game}_k\text{中输出}1] - \Pr[\mathcal{A} \text{在}\text{Game}_{k+1}\text{中输出}1] \right|$ 

    $\therefore \text{Adv}_{\text{LR-IND-CPA}}(\mathcal{A}) \leq \sum_{k=0}^{n-1} \text{Adv}_{\text{IND-CPA}}(\mathcal{B}_k)$$  

    其中$\mathcal{B}_k$是针对第$k$对相邻游戏的归约算法。由于$n$是**多项式有界的**（攻击者$\mathcal{A}$的询问次数在多项式时间内），且每个$\text{Adv}_{\text{IND-CPA}}(\mathcal{B}_k)$是可忽略的，因此总和仍是可忽略的。



## 6 CPA 安全的加密方案构建

!!! info 伪随机函数的定义
    令 $F:\{0,1\}^*×\{0,1\}^*→\{0,1\}^*$ 是有效的、长度保留的、带密钥的函数。如果对所有多项式时间区分器 $D$，存在一个可忽略函数 $\text{negl}$，满足：$$\left| \Pr\left[D^{F_k(\cdot)}(1^n) = 1\right] - \Pr\left[D^{f(\cdot)}(1^n) = 1\right] \right| \leq \text{negl}(n),$$

    则称 $F$ 是一个伪随机函数，其中 $k \leftarrow \{0,1\}^n$ 是均匀随机选择的，并且 $f$ 是从将 $n$ 比特字符串映射到 $n$ 比特字符串的函数集合中均匀随机选择出来的。

设 $F$ 是一个伪随机函数，则有构造 CPA 安全的加密方案如下：

* $k \leftarrow \text{Gen} \, (1^n)$，$c := <r , F_{k}(r) \oplus m>$，$m := F_{k}(r) \oplus s$

其中 $r$ 为随机数，$s = F_{k}(r) \oplus m$

## ？ 单向函数（One-Way Functions）

!!! info 求逆实验 $\text{Invert}_{\mathcal{A},f}(n)$
    <br>

    1. $x \leftarrow \{0,1\}^n$ ，$y := f(x)$
    2. $1^n$ 和 $y$ 作为 $\mathcal{A}$ 的输入，输出为 $x'$
    3. 如果 $f(x') = y$ ，那么定义该实验的输出为 $1$，否则为 $0$

* 如果一个函数 $f : \{0,1\}^* \to \{0,1\}^*$ 满足下述两个条件，那么它就是**单向函数**：
  1. （**Easy to compute:**）存在一个多项式时间算法 $M_f$ 来计算 $f$ ；也就是说，对所有 $x$ ，有 $M_f(x) = f(x)$ 
  2. （**Hard to invert:**）对任意概率多项式时间算法 $\mathcal{A}$ ，存在一个可忽略函数 $\text{negl}$ ，满足 $$\Pr\left[ \text{Invert}_{\mathcal{A},f}(n) = 1 \right] \leqslant \text{negl}(n)$$

!!! hint
    上式第二条可用符号表示法表述为：$$\Pr_{x \leftarrow \{0,1\}^n}\left[ \mathcal{A}(f(x)) \in f^{-1}(f(x)) \right] \leqslant \text{negl}(n)$$