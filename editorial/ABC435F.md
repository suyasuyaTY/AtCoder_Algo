## 高いところから順に降りていく解法
現在猫がいる場所が $k$ で移動できる範囲が $[L,R)$ とする。
次に猫がいる場所は $[L, k), [k+1, R)$ のどちらかである。この時、次の事実が存在する。
> $[L, R)$ に猫が移動するならば、最適な移動場所は $[L, R)$ の塔の最大の高さの場所。
> 
> 最大の高さの塔に移動しない場合
> + 最大の高さの塔に邪魔されて移動できない
> + 最大の高さの塔に移動してからでもその塔に移動できるため、最適にならない。

そのため、適切に`dfs`をすることで求めることができる。

```cpp
int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  int N;
  cin >> N;

  vector<int> P(N), P_inv(N);
  for (int i = 0; i < N; i++) {
    cin >> P[i];
    P[i]--;
    P_inv[P[i]] = i;
  }

  segtree<int, [](int x, int y) { return max(x, y); }, []() { return 0; }> P_max(P);

  int s = P_inv[N - 1];
  vector<ll> dp(N, 0);

  auto dfs = [&](auto self, int l, int r, int v) -> void {
    if (l >= r) return;
    int nv = P_inv[P_max.prod(l, r)];
    dp[nv] = dp[v] + abs(v - nv);

    self(self, l, nv, nv);
    self(self, nv + 1, r, nv);
  };

  dfs(dfs, 0, s, s);
  dfs(dfs, s + 1, N, s);

  cout << *max_element(dp.begin(), dp.end()) << endl;
}
```