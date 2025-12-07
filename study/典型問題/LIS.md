# LIS

## 二分探索で求める最長増加部分列

```cpp
vector<int> LIS(const vector<int> &A) {
  vector<int> dp(A.size(), INF);

  for (const int x : A) {
    auto it = lower_bound(dp.begin(), dp.end(), x); 
    *it = x;
  }

  return dp;
}
```

## セグメント木で求める最長増加部分列
`A`は座標圧縮をしておく。
- `dp[i][j]`：`A`の$i$番目までの要素を考えて最後の用いた要素の値が$j$であるLISの長さ
- $j = A_i$：$dp[i][j] = \max_{0 \le k <j} dp[i-1][k] + 1$
- $j \neq A_i$：$dp[i][j] = dp[i-1][j]$

そのため、in-placeで更新できる。

```cpp
vector<int> LIS(const vector<int> &A) {
  segtree<int, [](int x, int y) { return max(x, y); }, []() { return 0; }> dp(vector<int>(A.size() + 1, -INF));
  dp.set(0, 0);

  for (const int x : A) {
    dp.set(x, dp.prod(0, x) + 1);
  }

  vector<int> res(A.size() + 1);
  for (int i = 0; i < ssize(res); i++) {
    res[i] = dp.get(i);
  }

  return res;
}
```