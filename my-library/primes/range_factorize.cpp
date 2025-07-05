#include "primes.hpp"
#include <bits/stdc++.h>

using namespace std;

vector<int> range_factorize(long long L, long long R) {
  vector<int> vis(R - L + 1);  // vis[i]: L + iを表す
  for (int p : prime_enumerate(sqrt(R) + 100)) {
    // [L,R]に含まれるpの倍数を探索
    for (long long x = ((L + p - 1) / p) * p; x <= R; x += p) {
      // ここを問題に合わせて処理を変える
    }
  }
}