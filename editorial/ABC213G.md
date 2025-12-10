# ABC213-G

## 1. 準備：部分集合の列挙

$i$ の立っているビットの本数が $k$ 本の時、条件を満たす $j$ は $2^{k}$ 個あるので、 $(i,j)$ の組は
$$
\sum_{k = 0}^{N} \binom{N}{k} 2^{k} = (1 + 2)^{N} = 3^{N}
$$
$3^{N}$ 個ある。

```cpp
for (int i = 0; i < (1 << N); i++) {
  for (int j = i; j >= 0; j--) {
    j &= i;
    // (i, j) は条件を満たす
  }
}
```

[部分集合の列挙-コード](https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361#7-%E4%B8%8E%E3%81%88%E3%82%89%E3%82%8C%E3%81%9F%E9%83%A8%E5%88%86%E9%9B%86%E5%90%88%E3%81%AE%E9%83%A8%E5%88%86%E9%9B%86%E5%90%88%E3%82%92%E5%88%97%E6%8C%99)
[部分集合の列挙-理解](https://ark4rk.hatenablog.com/entry/2018/03/07/230257)

## 2. 数え上げる対象を言い換える

$1$ と $k$ が連結という条件が複雑なので、対象を言い換える必要がある。

$G$ の頂点集合を $V \coloneqq \{1,2,\dots, N\}$ と表し、 $S \subseteq V$ を満たす $S$ に対して、 $f(S), g(S)$ を定める。

+ $f(S) \coloneqq S \subseteq V$ を頂点集合とする $G$ の連結部分グラフ
+ $g(S) \coloneqq S \subseteq V$ を頂点集合とする $G$ の部分グラフ

このように定めると、 $1$ と $k$ が連結である $G$ の部分グラフの個数を $C(k)$ と置くと、

$$
C(k) = \sum_{\{1,k\} \subseteq S \subseteq V } f(S) g(V \setminus S)
$$

すべての $S \subseteq V$ に対して、 $f(S), g(S)$ を事前計算することで、 $O(N 2^{N})$ で $C(2), C(3), \dots, C(N)$ を計算できる。

## 3. $g(S)$ の計算

$S$ に含まれている頂点間に張られている辺の本数を $e$ 本としたとき、部分グラフの個数は $2^e$ 個ある。

愚直に書いても、すべての $S \subseteq V$ に対して $g(S)$ を $O(M2^N)$ で計算することができる。

```cpp
vector<mint> g(1 << N);
for (int i = 0; i < (1 << N); i++) {
    int k = 0;
    for (const auto &[u, v] : Edge) {
        if (((i >> u) & 1) && ((i >> v) & 1)) {
            k += 1;
        }
    }
    g[i] = mint(2).pow(k);
}
```

## 4. $f(S)$ の計算

$S = \phi$ の時は自明に $f(S) = 1$ なので、 $S \neq \phi$ を考える。

$f(S)$ を $g(S)$ を用いて表すと、 $f(S) = g(S) - (\text{頂点集合が} S \text{である非連結なグラフの個数})$ と表される。
ある頂点 $v \in S$ を取り出し、 $v$ と連結な頂点集合を $T$ とすることで被りなく求めることができる

$$
f(S) = g(S) - \sum_{v \in T \subsetneq S} f(T) g(S \setminus T)
$$

と表されるので、部分集合の列挙のアルゴリズムを用いて $f(S)$ を $O(3^N)$ で求めることができる。

```cpp
vector<mint> f(1 << N);
    for (int i = 0; i < (1 << N); i++) {
    f[i] = g[i];
    int v = -1;
    for (int j = 0; j < N; j++) {
        if ((i >> j) & 1) {
            v = j;
            break;
        }
    }
    if (v == -1) continue;
    for (int j = i - 1; j >= 0; j--) {
        j &= i;
        if ((j >> v) & 1)
            f[i] -= f[j] * g[i ^ j];
    }
}
```
