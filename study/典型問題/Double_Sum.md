## `[L, R]`の和に関する問題

### 累積和
1. $f$ を展開して、 $l, r$ それぞれの式に分離する
$$
\begin{aligned}
    \sum_{1 \le l \le r \le N} f \left( \sum_{l \le k \le r} A_k \right) &= \sum_{1 \le l \le r \le N} f( S_{r} - S_{l-1}) \\
    &= \sum_{0 \le l < r \le N} f( S_{r} - S_{l}) \\
    &= \sum_{r = 0}^{N} \sum_{l = 0}^{r - 1} f( S_{r} - S_{l}) \\
\end{aligned}
$$

2. $T_r = \sum_{l = 1}^{r} f\left( \sum_{k = l}^{r} A_k \right)$ を `dp` で求める
$$
\begin{aligned}
    \sum_{1 \le l \le r \le N} f \left( \sum_{l \le k \le r} A_k \right) &= \sum_{r = 1}^{N} T_{r} \\
\end{aligned}
$$