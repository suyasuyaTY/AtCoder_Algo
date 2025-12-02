## 1. WAになっていた原因
- 安全な場所の遷移： $[R_i, R_i + B) \rightarrow [L_{i+1} - B, L_{i+1})$
- 危険な場所の遷移： $[L_i - B, L_i) \rightarrow [R_i, R_i + B)$

というこの2つの遷移に関する関数を作成していた。
しかし、安全な場所の遷移の際に情報が消えてしまう場合があるためうまくいかない
- 例： $R_i = 2, L_{i+1} = 4, B = 20$ の時 $[2, 22) \rightarrow [-16, 4)$

## 2. 修正が難しいという話

- 安全な場所の遷移： $[R_i, R_i + B) \rightarrow [L_{i+1} - B, L_{i+1} + B)$
- 危険な場所の遷移： $[L_i - B, L_i + B) \rightarrow [R_i, R_i + B)$
- 安全な遷移の際に、危険な場所を踏んでまた安全な場所に行くというのを防ぐのが難しい

## 3. 公式解説の実装
- $S_i(1 \le i \le M + 1)$：安全地帯の開始地点
- $T_i(1 \le i \le M + 1)$：安全地帯の終了地点
- $I_i = (S_i, \dots, T_i)$：安全地帯の区間
- $X_i$：$I_i$の先頭B項
- $Y_i$：$I_i$の末尾B項
- $X_i, Y_i$の長さの合計は$O(MB)$なので、`set`で持つことができる

### 3.1 危険地帯を渡るときの判定
$X_1, \dots, X_i$, $Y_1, \dots, Y_i$ にたどり着けるかどうかの判定が終了しているときに、$X_{i+1}$を求める。

1. $X_1, \dots, X_i$, $Y_1, \dots, Y_i$ からの遷移：1回の遷移でたどり着く必要がある。
2. $X_{i+1}$ からの遷移：こちらも確認する
```cpp
set<ll> walk_dangerous(const set<ll> &ok, ll L, ll R) {
  set<ll> X;
  for (ll x = L; x <= R; x++) {
    for (int dx = A; dx <= B; dx++) {
      if (ok.contains(x - dx) || X.contains(x - dx)) {
        X.insert(x);
        break;
      }
    }
  }
  return X;
}
```

## 3.2 安全地帯を渡るときの判定
$X_1, \dots, X_i$, $Y_1, \dots, Y_{i-1}$ にたどり着けるかどうかの判定が終了しているときに、$Y_i$を求める。

1. $X_i$ からの遷移：$kA$ が $Y_i$ の最初の項より大きくなる場所を求め、$[kA, kB] \cap Y_i$ を調べる
2. $X_1, \dots, X_{i-1}$, $Y_1, \dots, Y_{i-1}$ からの遷移：1回の遷移でたどり着く必要がある。複数回でたどり着くものは 1. で考慮できている
   - $(k-1)B$ が $Y_i$と交わる可能性があるのでここで、ついでに調べておく

```cpp
set<ll> walk_safe(const set<ll> &ok, const set<ll> &X, ll L, ll R) {
  set<ll> Y;
  for (const ll x : X) {
    ll k = (L - x + A - 1) / A;
    for (ll nx = x + k * A; nx <= min(x + k * B, R); nx++) {
      Y.insert(nx);
    }
  }

  for (ll x = L; x <= R; x++) {
    for (int dx = A; dx <= B; dx++) {
      if (ok.contains(x - dx) || Y.contains(x - dx)) {
        Y.insert(x);
      }
    }
  }

  return Y;
}
```

### 全体のコード
```cpp
ll N, M, A, B;

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  cin >> N >> M >> A >> B;
  vector<pll> seg(M + 1);
  seg[0].first = 1;
  seg[M].second = N;
  for (int i = 0; i < M; i++) {
    cin >> seg[i].second >> seg[i + 1].first;
    seg[i].second--;
    seg[i + 1].first++;
  }

  set<ll> ok, X;
  X.insert(1);
  for (int i = 0; i <= M; i++) {
    const auto &[S0, T0] = seg[i];
    set<ll> Y = walk_safe(ok, X, max(S0, T0 - B + 1), T0);
    ok.merge(X);
    ok.merge(Y);
    if (i < M) {
      const auto &[S1, T1] = seg[i + 1];
      X = walk_dangerous(ok, S1, min(S1 + B - 1, T1));
    }
  }

  Yes(ok.contains(N));
}
```
