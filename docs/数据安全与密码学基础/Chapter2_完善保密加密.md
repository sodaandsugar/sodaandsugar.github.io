# Chapter 2 完善保密加密

## 1 完善保密（Perfect privacy）

!!! tip 注意
    **完善保密（Perfect privacy）** 是密码学中的重要概念，在课程中被拆分为 **香农安全** 和 **完美安全** 两个部分来讲述，但实际上这三个概念都是 **等价** 的，即：**完善保密 $=$ 香农安全 $=$ 完美安全** 。

**香农安全**指的是，$m$ 已发送时的后验概率与 $m$ 将被发送时的先验概率相同，即**敌手截获一个密文不能得到任何关于明文的信息**，其严格表述如下：

* 明文空间为 $\mathcal{M}$ 的加密方案 $(\text{Gen}, \text{Enc}, \text{Dec})$ 是完善保密加密，若对 $\mathcal{M}$ 上任意的概率分布，任何明文 $m \in \mathcal{M}$、任何密文 $c \in \mathcal{C}$ 且 $\Pr[C = c] > 0$，有
$$\Pr[M = m|C = c] = \Pr[M = m]$$

其有等价定义如下：

* 明文空间为 $\mathcal{M}$ 的加密方案 $(\text{Gen}, \text{Enc}, \text{Dec})$ 是完善保密加密，当且仅当对于任意 $\mathcal{M}$ 上的概率分布，任意一个明文 $m \in \mathcal{M}$，和任意一个密文 $c \in \mathcal{C}$，有
$$\Pr[C = c \mid M = m] = \Pr[C = c]$$

!!! abstract 证明
    **充分性** ：
    选定一个 $\mathcal{M}$ 上的分布，对于任意的 $m \in \mathcal{M}$ 和 $c \in \mathcal{C}$，有
    $$\Pr[C = c \mid M = m] = \Pr[C = c]$$

    在等式两边同时乘以 $\Pr[M = m]/\Pr[C = c]$，得：$$\frac{\Pr[C = c \mid M = m] \cdot \Pr[M = m]}{\Pr[C = c]} = \Pr[M = m]$$
    
    应用贝叶斯定理得 $\Pr[M = m \mid C = c] = \Pr[M = m]$，故该加密方案是完善保密加密方案

    **必要性**：
    假设加密方案是完善保密加密，则根据贝叶斯定理有：$$\Pr[M = m] = \Pr[M = m \mid C = c] = \frac{\Pr[C = c \mid M = m] \cdot \Pr[M = m]}{\Pr[C = c]}$$
    
    * 若 $\Pr[M = m] \neq 0$，两边同除 $\Pr[M = m]$ 可得：$\Pr[C = c \mid M = m] = \Pr[C = c]$

    * 若 $\Pr[M = m] = 0$，则 $\Pr[C = c \mid M = m] = \frac{\Pr[M = m, C = c]}{\Pr[M = m]} =0$，也满足：$\Pr[C = c \mid M = m] = \Pr[C = c]$

**完美安全**指的是**任意两个明文产生同一个密文的概率是相等的**，其严格表述如下：

* 明文空间为 $\mathcal{M}$ 的加密方案 $(\text{Gen}, \text{Enc}, \text{Dec})$ 是完善保密加密，当且仅当对于任意 $\mathcal{M}$ 上的概率分布，每个 $m_0, m_1 \in \mathcal{M}$，以及每个 $c \in \mathcal{C}$，有
$$\Pr[C = c \mid M = m_0] = \Pr[C = c \mid M = m_1]$$

!!! abstract 证明
    **必要性**：
    若 $\mathcal{M}$ 是完善保密加密，则有：
    $$\Pr[C = c \mid M = m_0] = \Pr[C = c] = \Pr[C = c \mid M = m_1]$$

    **充分性**：
    假设对任意 $\mathcal{M}$ 上的概率分布，每个 $m_0, m_1 \in \mathcal{M}$ 和每个 $c \in \mathcal{C}$，满足 $\Pr[C = c \mid M = m_0] = \Pr[C = c \mid M = m_1]$
    
    选定某个 $\mathcal{M}$ 上的分布，对任意的 $m_0 \in \mathcal{M}$ 与 $c \in \mathcal{C}$，定义 $p \stackrel{\text{def}}{=} \Pr[C = c \mid M = m_0]$
    
    则有 $\forall m$，$\Pr[C = c \mid M = m] = \Pr[C = c \mid M = m_0] = p$，于是有：

    $\Pr[C = c] = \sum\limits_{m \in \mathcal{M}} \Pr[C = c \mid M = m] \cdot \Pr[M = m] = p \cdot \sum\limits_{m \in \mathcal{M}} \Pr[M = m] = p = \Pr[C = c \mid M = m_0]$
    
    因为 $m_0$ 是任意选择的，所以对所有 $c \in \mathcal{C}$ 和 $m \in \mathcal{M}$，都有 $\Pr[C = c] = \Pr[C = c \mid M = m]$ 成立，故此加密方案是完善保密的

    上述定义又被称为 **完美不可区分性（Perfect indistinguishability）**

!!! info 窃听不可区分实验
    <br>
    
    1. 敌手 $\mathcal{A}$ 输出一对信息 $m_0, m_1 \in \mathcal{M}$

    2. $k \leftarrow \text{Gen}$，$b \leftarrow \{0,1\}$，$c \leftarrow \text{Enc}_k(m_b)$

    3. $\mathcal{A}$ 输出一个比特 $b'$ 用于猜测实验中选定的值 $b$

    4. 如果 $b' = b$，定义实验的输出为 1，否则为 0，用 $\text{PrivK}^{\text{eav}}_{\mathcal{A},\Pi} = 1$ 表示 $\mathcal{A}$ 成功

根据窃听不可区分实验，给出完善保密加密的另一种定义，即：

* 明文空间为 $\mathcal{M}$ 的加密方案 $(\text{Gen}, \text{Enc}, \text{Dec})$ 为完善保密加密，当对于所有敌手都满足
$$\Pr[\text{PrivK}^{\text{eav}}_{\mathcal{A},\Pi} = 1] = \frac{1}{2}$$

以上定义又被称为 **敌手不可区分性（Adversarial indistinguishability）**。

!!! warning 注意
    本章中敌手 $\mathcal{A}$ 的计算能力是没有限制的。

## 2 一次一密（One-Time Pad）
令 $a \oplus b$ 表示把二进制串 $a$ 和二进制串 $b$ 按比特位异或，则一次一密方案定义如下：
1. 令整数 $l > 0$，设明文空间 $\mathcal{M}$，密钥空间 $\mathcal{K}$ 和密文空间 $\mathcal{C}$ 都等于 $\{0, 1\}^l$，即均为长度为 $l$ 的二进制比特串的集合
2. 密钥产生算法 $\text{Gen}$ 从 $\mathcal{K} = \{0, 1\}^l$ 中依据均匀分布选择一个二进制比特串（$2^l$个串空间中任何一个被选中的概率都为$2^{-l}$）
3. $c := k \oplus m$，$m := k \oplus c$

在讨论一次一密的安全性前，我们注意到每个 $k$ 和 $m$ 都满足 $\text{Dec}_k(\text{Enc}_k(m)) = k \oplus (k \oplus m) = m$，所以一次一密是一个正确的加密方案。

进一步，我们可以得到：

* **一次一密是完善保密加密。**

!!! abstract 证明
    选定明文空间 $\mathcal{M}$ 上的分布，选定任意一个 $m \in \mathcal{M}, c \in \mathcal{C}$，一次一密有：
    $$\begin{align*}
    \Pr[C = c \mid M = m] &= \Pr[M \oplus K = c \mid M = m] \\
    &= \Pr[m \oplus K = c] = \Pr[K = m \oplus c] = \frac{1}{2^l}
    \end{align*}$$
    
    所以对于任意 $\mathcal{M}$ 上的概率分布，每个 $m_0, m_1 \in \mathcal{M}$ 和每个 $c \in \mathcal{C}$，满足
    $$\Pr[C = c \mid M = m_0] = \frac{1}{2^l} = \Pr[C = c \mid M = m_1]$$

然而，一次一密也有很多缺陷，最突出的是需要密钥和明文有一样的长度，这在实践中问题较大且通常是不可能的，且其应用也受到限制。

并且，密钥只用一次的时候才是安全的。特别地，如果明文信息 $m$ 、 $m'$ 用同样一个密钥 $k$ 进行加密，敌手则可以得到 $c \oplus c' = (m \oplus k) \oplus (m' \oplus k) = m \oplus m'$，此时就不是完善保密加密了。

长密钥的问题并非一次一密专有，而是所有完善保密加密的内在问题。

* 设 $(\text{Gen}, \text{Enc}, \text{Dec})$ 是明文空间为 $\mathcal{M}$ 的一个完善保密加密方案，$\mathcal{K}$ 的密钥空间由 $\text{Gen}$ 决定，则 $|\mathcal{K}| \geq |\mathcal{M}|$

!!! abstract 证明
    下面运用反证法，证明如果 $|\mathcal{K}| < |\mathcal{M}|$，则这个加密方案不是完善保密加密：
    
    假设 $|\mathcal{K}| < |\mathcal{M}|$，考虑 $\mathcal{M}$ 为均匀分布且设密文 $c \in \mathcal{C}$ 有非零概率，$\mathcal{M}(c)$ 是所有密文 $c$ 解密而得可能明文的集合，也就是
    $$\mathcal{M}(c) \stackrel{\text{def}}{=} \{\hat{m} \mid \hat{m} = \text{Dec}_{\hat{k}}(c), \text{for some }\hat{k} \in \mathcal{K}\}$$
    
    显然有 $|\mathcal{M}(c)| \leq |\mathcal{K}|$，因为对于每个明文消息 $\hat{m} \in \mathcal{M}(c)$，至少可以确定一个密钥 $\hat{k} \in \mathcal{K}$ 使得 $\hat{m} = \text{Dec}_{\hat{k}}(c)$
    
    由于假设 $|\mathcal{K}| < |\mathcal{M}|$，则 $\exist m'$ 使得 $m' \in \mathcal{M}$ 但 $m' \notin \mathcal{M}(c)$，则有：$$\Pr[M = m' \mid C = c] = 0 \neq \Pr[M = m']$$
    
    所以这个方案不是完善保密加密。

## 3 香农定理（Shannon’s Theorem）

* 设加密方案 $(\text{Gen}, \text{Enc}, \text{Dec})$ 的明文空间为 $\mathcal{M}$，且 $|\mathcal{K}| = |\mathcal{M}| = |\mathcal{C}|$，则当且仅当下列条件成立时，此方案是完善保密加密：
  1. 由 $\text{Gen}$ 产生的任意密钥 $k \in \mathcal{K}$ 的概率都是 $1/|\mathcal{K}|$
  2. 对任意明文 $m \in \mathcal{M}$ 和任意密文 $c \in \mathcal{C}$，只存在唯一的密钥 $k \in \mathcal{K}$ 使得 $\text{Enc}_k(m)$ 输出 $c$