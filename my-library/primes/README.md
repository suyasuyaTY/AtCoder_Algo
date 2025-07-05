# 素数に関する関数

## 区間[L,R]をすべて素因数分解する処理を行う区間篩（range_factorize.cpp）
[解説](https://atcoder.jp/contests/abc227/editorial/2909)
素数の数は少なく、大きくなる速度も速いので計算量はかなり少ない
- 計算量:$O(M \log \log M), M = \max(R - L, \sqrt{R})$

## エラトステネスの篩（prime_enumerate.cpp）
- 計算量:$O(N \log \log N)$