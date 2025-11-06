# Chapter 1 概论

## 1 对称密钥加密的基本设置

### 1. 1 加密语法
  * **密钥产生算法 $\text{Gen}$**：概率算法，能够根据方案定义的某种分布选择并输出一个密钥 $k$
  * **加密算法 $\text{Enc}_k(m)$**：输入密钥 $k$ 和明文 $m$，输出密文 $c$
  * **解密算法 $\text{Dec}_k(c)$**：输入为密钥 $k$ 和密文$c$，输出明文 $m$
  * **密钥空间 $\mathcal{K}$**：$\text{Gen}$ 输出的所有可能的密钥
  * **明文（或消息）空间 $\mathcal{M}$**：所有合法消息（即被加密算法支持的消息）的集合

!!! tip "注意"
    集合 $\mathcal{K}$ 和 $\mathcal{M}$ 共同定义了所有可能密文的集合 $\mathcal{C}$，一个加密方案可通过明确 $\text{Gen, Enc, Dec}$ 三个算法和明文空间 $\mathcal{M}$ 来完全定义。

<img src="/cryptography/images/image1-1.png" style="display: block; width: 60%; margin: 0 auto;" />

* 对任意加密方案的基本要求是，对于任意通过 $\text{Gen}$ 输出的密钥 $k$，每个明文消息 $m \in \mathcal{M}$，满足：
$$
\text{Dec}_k(\text{Enc}_k(m)) = m
$$

!!! info "加密方案的正确性"
    $$
    \forall m \in M,\ {\Pr}\ [Dec(Enc(sk,m))=m]=1
    $$

### 1. 2 Kerckhoffs 原则
* **加密方案本身不必保密，唯一需要保密的是通信双方共享的秘密密钥**
* **提倡安全性不能建立在对算法的保密上，更提倡要公开这些算法**

!!! info "接受 Kerckhoffs 原则的三个主要理由"
    1. 与维护算法的保密性相比，通信各方更容易维护短小密钥的保密性
    2. 万一密钥暴露，参与方将可以非常容易地改变密钥而非替换算法
    3. 万一有多对人员需要加密他们的通信，对所有参与方而言，使用同样的算法和不同的密钥，与使用不同的程序相比要容易得多

### 1. 3 攻击场景
1. **唯密文攻击（Ciphertext-only attack）**：最基本的攻击方式，敌手只能观察到密文（或者多个密文），并且试图确定相应的明文（或者多个明文）
2. **已知明文攻击（Known-plaintext attack）**：敌手学习一个或者多个使用相同密钥加密的明文/密文对，目标是确定其他密文对应的明文
3. **选择明文攻击（Chosen-plaintext attack）**：敌手能够选择明文并得到相应密文，并且试图确定其他密文对应的明文
4. **选择密文攻击（Chosen-ciphertext attack）**：敌手可以选择密文并得到相应的明文，目的是确定其他密文的明文

## 2 古典加密术及其密钥分析
对于 **移位加密（shift ciper）**，密文字符 $c_i = (m_i + k) \bmod 26$，明文字符 $m_i = (c_i - k) \bmod 26$，**凯撒加密（Caesar’s cipher, k=3）** 和 **ROT-13（k=13）** 可以视为移位加密的特例。

由于密钥数量只有 26 个，使用 **蛮力攻击（brute-force attack）** 或 **穷举攻击（exhaustive-search attack）** 很容易就能破解，故无安全性。

!!! tip "密钥空间充分性原则（sufficient key-space principle）"
    任何安全的加密方案必须拥有一个能够抵御穷举搜索的密钥空间。

考虑**单字母替换加密（mono-alphabetic substitution cipher）**，其密钥空间的规模变为 $26! \approx 2^{88}$，但是由于每个字符的映射是固定的，且英语中单个字母的概率分布是已知的，故依然可以快速攻破。

<img src="/cryptography/images/image1-2.png" style="display: block; width: 90%; margin: 0 auto;" />
<br>

!!! abstract "攻击方法"
    用 $0,\cdots,25$ 表示英文字母，令$p_i$（$0 < i \leqslant 25$）表示在普通英文文本中第 $i$ 个字母的概率，对已知的值 $p_i$ 容易计算 
    $$
    \sum_{i=0}^{25} p_i^2 \approx 0.065
    $$

    对于给定密文，令 $q_i$ 表示第 $i$ 个字符在密文中的概率，如果密钥是 $k$，那么期望对于每个 $i$，$q_{i+k} \approx p_i$
    
    对应地，对每个$j \in \{0,\cdots,25\}$计算
    $$
    I_j \stackrel{\text{def}}{=} \sum_{i=0}^{25} p_i \cdot q_{i+j}
    $$

    期望发现 $I_k \approx 0.065$，，故 **密钥恢复攻击（key-recovery attack）** 非常容易自动进行：**对于所有 $j$ 计算 $I_j$，并输出所有 $I_k$ 接近 $0.065$ 的 $k$**

**弗吉尼亚加密（Vigenere ciper）**又称**多字母移位加密（poly-alphabetic shift cipher）**，依次运用多个移位加密，破解这种加密方法看似困难，但可以使用 Kasiski 方法进行破解，在 CTF101 中有相应例题，这里不过多赘述。

<img src="/cryptography/images/image1-3.png" style="display: block; width: 50%; margin: 0 auto;" />

## 3 现代密码学的基本原则

1. **Formal Definitions**：解决任何密码学问题的第一步是公式化的表述严格且精确的安全定义
2. **Precise Assumptions**：当密码学构造方案的安全性依赖于某个未被证明的假设时，这种假设必须精确地陈述，而且，所假设的要尽可能地少
3. **Proofs of Security (Reduction)**：密码学构造方案应当伴随有严格的安全证明，跟随符合原则 1 的安全定义，以及与原则 2 陈述的假设有关（如果假设是需要的）