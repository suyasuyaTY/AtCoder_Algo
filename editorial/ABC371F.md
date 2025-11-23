# ポイント：座標変換を使える形に落とし込む

## 1. $X_i'$ の導入
元の座標$X_i$は、**狭義単調増加**制約があり、区間代入ができず扱いづらい。そこで、
$$X_i' = X_i - i$$
という変換を行うことにより**広義単調増加**に制約を緩和できる。
隣り合う要素が同じとき、その区間では高橋君が隣り合っていることを表している。

## 2. 操作の言い換え
問題文の「$T$番目の高橋君を$G$に移動させる」という操作は、座標変換後には次のように言い換えられる。

> 操作対象：$T$番目の要素$X_T'$
> 目標値：$Y = G - T$

この時、**広義単調増加**を崩さないために周囲を巻き込みながら更新する必要がある。

### 右に動かす場合 $X_T' < Y$
$T$番目の高橋君より右側にいて、$X_i' \le Y$ となっている人を$X_i' = Y$となるように押し出す。

移動コストは
$$
\sum_{l \le i \le r} |X_i' - Y| = Y(r - l + 1) - \sum_{l \le i \le r} X_i'
$$
となる。

### 左に動かす場合 $Y < X_T'$
$T$番目の高橋君より左側にいて、$Y \le X_i'$ となっている人を$X_i' = Y$となるように押し出す。

移動コストは
$$
\sum_{l \le i \le r} |X_i' - Y| = \sum_{l \le i \le r} X_i' - Y(r - l + 1)
$$
となる。

## 3. 遅延セグメントに乗せる
### 遅延セグメント木に乗せる情報
```cpp
struct S {
  int length;           // 区間の長さ
  ll sum;               // 区間内の総和
  ll min_val, max_val;  // 区間内の最小値・最大値
};

using F = optional<ll>;
```
### 区間更新処理
```cpp
S op(S l, S r) {
  return {
      l.length + r.length,
      l.sum + r.sum,
      min(l.min_val, r.min_val),
      max(l.max_val, r.max_val)};
}

S e() {
  return {0, 0, LINF, -LINF};
}

S mapping(F f, S x) {
  // f に値が入っている（=代入操作がある）場合
  if (f.has_value()) {
    ll val = f.value();
    return {
        x.length,        // 長さは変わらない
        val * x.length,  // 和は 値×長さ になる
        val,             // 最小値も val になる
        val              // 最大値も val になる
    };
  }
  // 操作がない場合はそのまま返す
  return x;
}

F composition(F f, F g) {
  // 今回は「代入」なので、新しい操作 f があれば、古い操作 g を完全に上書きする
  if (f.has_value()) {
    return f;
  }
  // 新しい操作がなければ、古い操作 g をそのまま残す
  return g;
}

F id() {
  return nullopt;
}
```

### セグメント木上の二分探索 (max_right / min_left)

#### ケース1：右に動かす$(X_T' < G)$場合
目的：右側に向かって「$G$未満の$X_i'$となる$i$」がどこまで続いてるか求める
- 使う関数：`max_right(T, g)`
- 判定条件：`v.max < G`
```cpp
const auto r = segment_tree.max_right(T, [G](const auto& v){ return v.max_val < G; });
```
#### ケース2：左に動かす$(G < X_T')$場合
目的：右側に向かって「$G$より大きい$X_i'$となる$i$」がどこまで続いてるか求める
- 使う関数：`min_left(T, g)`
- 判定条件：`v.min > g`
```cpp
const auto l = segment_tree.min_left(T, [G](const auto& v){ return v.min_val > G; });
```

