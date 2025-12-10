# ABC212-G

## 1. 剰余の性質を覚えているか

### 1.1. 原始根
$r_e \equiv 1 \pmod {P}$ を満たす最初の正整数 $e$ が $P-1$ であるとき、 $r$ を法 $P$ に対する原始根という。
次の3つの性質を使う
1. $r^1, r^2, \dots, r^{P-1} \pmod {P}$ が相異なる
2. $r^{P-1} \equiv 1 \pmod {P}$
3. 素数 $P$ に対して、原始根が必ず存在する。

### 1.2 原始根を用いて問題の言いかえ
$x = 0, y = 0$ の時は、原始根で表されない。条件を満たすのは $(x,y) = (0,0)$ のみ。
以下では、 $1 \le x, y \le P - 1$ とする。

原始根 $r$ と $1 \le a, b \le P - 1$ に対して、 $x \equiv r^{a}, y \equiv r^{b} \pmod {P}$ を一対一対応させる。

$$
\begin{aligned}
    & x^{n} \equiv y \pmod {P} \\
    &\Leftrightarrow r^{an} \equiv r^{b} \pmod {P} \\
    &\Leftrightarrow an \equiv b \pmod {P-1} \\
\end{aligned}
$$

よって、 $an \equiv b \pmod {P-1}$ を満たすような正整数 $n$ が存在する $(a,b)$ の組の個数を求めることに帰着された。

## 2. 主客転倒

### 2.1. 愚直解
$$
an \equiv b \pmod {M}
$$
満たすような正整数 $n$ が存在する $(a,b)$ の組の個数を求める。
ある整数 $k$ を使って、
$$
\begin{aligned}
    an - b = -Mk \Leftrightarrow an + Mk = b
\end{aligned}
$$
と書くことができる。
これが、整数解を持つための必要十分条件は、 $gcd(a,M) | b$ である。

[拡張ユークリッドの互除法](https://qiita.com/drken/items/b97ff231e43bce50199a)

$b$ の範囲は $1 \le b \le M$ なので、 $a$ を固定したときに条件を満たす $b$ の個数は、 $\frac{M}{gcd(a,M)}$ と書ける。

そのため、
$$
\sum_{a = 1}^{P-1} = \frac{P-1}{gcd(a,P-1)}
$$
で求めることができる。

### 2.2. 高速化

高速化のために、 $g = gcd(a, P-1)$ ごとにまとめて考えると、次の式で求められる。

$$
\sum_{g} = \frac{P-1}{g} \times f(g)
$$

ここで、 $f(g)$ は $1 \le a \le P-1$ かつ $g = gcd(a, P-1)$ を満たす $a$ の数である。約数包除を使って求めることができる。

```cpp
vector<ll> enum_divisors(ll N) {
  vector<ll> res;
  for (ll i = 1; i * i <= N; ++i) {
    if (N % i == 0) {
      res.push_back(i);
      if (N / i != i) res.push_back(N / i);
    }
  }
  sort(res.begin(), res.end());
  return res;
}

using mint = modint998244353;

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  ll P;
  cin >> P;

  vector<ll> div = enum_divisors(P - 1);

  int N = ssize(div);
  mint ans = 1;
  vector<mint> dp(ssize(div));

  for (int i = N - 1; i >= 0; i--) {
    dp[i] += (P - 1) / div[i];
    ans += (P - 1) * inv_mod(div[i], 998244353) * dp[i];
    for (int k = 0; k < i; k++) {
      if (div[i] % div[k] == 0) {
        dp[k] -= dp[i];
      }
    }
  }

  cout << ans.val() << endl;
}
```