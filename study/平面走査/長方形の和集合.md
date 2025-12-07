---
title: 長方形の和集合
description: 遅延セグメント木と座標圧縮を使うことで効率的に計算する
---

> 整数の組 $(l_i, r_i, d_i, u_i)$ が $N$個与えられる。
> $\{(x,y): l_i \le x \le r, d_i \le y \le u_i \}$ で表される長方形の和集合の面積を求めよ。

座標系が小さければ2次元imos法で解くことができるが、制約が $H \le 2 \times 10^{5}, W \le 2 \times 10^{5}$ になると間に合わない。

:::info
$x$ 軸に沿って長方形が存在する区間を見ていくことで、全ての平面を走査する。 
:::

<details>
  <summary>

  $H \le 2 \times 10^{5}, W \le 2 \times 10^{9}$
  
  </summary>

```cpp
using S = pii;  // (最小値、最小値の数)
using F = int;  // 区間加算
S op(S x, S y) {
  if (x.first == y.first) return pii(x.first, x.second + y.second);
  return min(x, y);
}
S mapping(F f, S x) {
  return pii(x.first + f, x.second);
}
F composition(F f, F g) {
  return f + g;
}
S e() { return pii(INF, 0); }
F id() { return 0; }

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  int N, H, W;
  cin >> N >> H >> W;
  vector<array<int, 4>> query;
  for (int i = 0; i < N; i++) {
    int l, r, d, u;
    cin >> l >> d >> r >> u;

    query.push_back({l, d, u, 1});
    query.push_back({r, d, u, -1});
  }

  ranges::sort(query);

  atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(vector<S>(H + 1, {0, 1}));
  ll ans = 0;
  int prev_x = 0;
  size_t idx = 0;
  while (idx < query.size()) {
    int current_x = query[idx][0];

    if (current_x > prev_x) {
      S ret = seg.all_prod();
      ll positive_count = (H + 1) - (ret.first == 0 ? ret.second : 0);

      ans += positive_count * (ll)(current_x - prev_x);
    }

    while (idx < query.size() && query[idx][0] == current_x) {
      auto [_, d, u, type] = query[idx++];
      seg.apply(d, u, type);
    }

    prev_x = current_x;
  }
}
```

</details>

<details>
  <summary>

  $H \le 2 \times 10^{9}, W \le 2 \times 10^{9}$
  
  </summary>

```cpp
class rectangle_union {
 private:
  using S = pll;  // S: {区間の最小値, その最小値を持つ区間の合計長}
  using F = int;  // 区間に加算する値
  static S op(S x, S y) {
    if (x.first == y.first) return {x.first, x.second + y.second};
    return min(x, y);
  }
  static S mapping(F f, S x) {
    return {x.first + f, x.second};
  }
  static F composition(F f, F g) {
    return f + g;
  }
  static S e() { return {LINF, 0}; }
  static F id() { return 0; }

  using SegTree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
  vector<array<int, 4>> query;
  vector<int> Y;  // 座標圧縮用

 public:
  rectangle_union() {}

  /**
   * @brief 長方形を追加します。
   * @param l 左端のx座標
   * @param d 下端のy座標
   * @param r 右端のx座標
   * @param u 上端のy座標
   */
  void add_rectangle(int l, int r, int d, int u) {
    // 面積が0の長方形は無視
    if (l >= r || d >= u) return;
    query.push_back({l, d, u, 1});
    query.push_back({r, d, u, -1});
    Y.push_back(d);
    Y.push_back(u);
  }

  ll solve() {
    // Y座標の座標圧縮
    ranges::sort(Y);
    Y.erase(unique(Y.begin(), Y.end()), Y.end());

    // 区間が0個なら面積は0
    if (Y.size() < 2) {
      return 0;
    }

    // セグメント木の初期化
    int M = Y.size();
    vector<S> v(M - 1);
    for (int i = 0; i < M - 1; i++) {
      v[i] = {0, (ll)Y[i + 1] - Y[i]};
    }
    SegTree seg(v);

    // イベントのソート
    ranges::sort(query);

    // 平面走査
    ll ans = 0;
    int prev_x = query[0][0];  // 最初のイベントx座標
    size_t idx = 0;

    // 考慮するY軸の全長
    ll total_Y_length = (ll)Y.back() - Y.front();

    while (idx < query.size()) {
      int current_x = query[idx][0];

      // 面積の加算
      if (current_x > prev_x) {
        S ret = seg.all_prod();
        ll positive_length = total_Y_length - (ret.first == 0 ? ret.second : 0);
        ans += positive_length * (ll)(current_x - prev_x);
      }

      // セグメント木の更新 (同じx座標のイベントを全て処理)
      while (idx < query.size() && query[idx][0] == current_x) {
        auto [_, d_orig, u_orig, type] = query[idx++];

        // Y座標を圧縮後のインデックスに変換
        int d_idx = lower_bound(Y.begin(), Y.end(), d_orig) - Y.begin();
        int u_idx = lower_bound(Y.begin(), Y.end(), u_orig) - Y.begin();

        // 区間 [d_idx, u_idx) に type (+1 or -1) を適用
        if (d_idx < u_idx) {
          seg.apply(d_idx, u_idx, type);
        }
      }

      prev_x = current_x;
    }

    return ans;
  }
};
```

</details>