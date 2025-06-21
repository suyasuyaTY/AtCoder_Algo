#include <vector>

// ローリングハッシュが衝突した場合の回避手法
// 1. ローリングハッシュを複数本用意する
// 2. ハッシュで衝突を検知した後、実際に部分文字列同士で比較する

template <unsigned mod> struct RollingHash {
  vector<unsigned> hashed, power;

  // a と b を乗算し、その結果を mod で割った余りを求める関数
  inline unsigned mul(unsigned a, unsigned b) const {
    return (unsigned long long)a * b % mod;
  }

  // hashed[i](s[0,..i-1]のハッシュ関数)を求める関数
  RollingHash(const string &s, unsigned base = 10007) {
    int sz = (int)s.size();
    hashed.assign(sz + 1, 0);
    power.assign(sz + 1, 0);
    power[0] = 1;
    for (int i = 0; i < sz; i++) {
      power[i + 1] = mul(power[i], base);
      hashed[i + 1] = mul(hashed[i], base) + s[i];
      if (hashed[i + 1] >= mod)
        hashed[i + 1] -= mod;
    }
  }

  // sの[l, r)の文字列のハッシュ関数
  unsigned get(int l, int r) const {
    unsigned ret = hashed[r] + mod - mul(hashed[l], power[r - l]);
    if (ret >= mod)
      ret -= mod;
    return ret;
  }

  // h1とh2のハッシュ関数を繋げる
  unsigned connect(unsigned h1, int h2, int h2len) const {
    unsigned ret = mul(h1, power[h2len]) + h2;
    if (ret >= mod)
      ret -= mod;
    return ret;
  }

  // s1の[l1,r1), s2の[l2,r2)で最長接頭語を求める
  int LCP(const RollingHash<mod> &b, int l1, int r1, int l2, int r2) {
    int len = min(r1 - l1, r2 - l2);
    int low = -1, high = len + 1;
    while (high - low > 1) {
      int mid = (low + high) / 2;
      if (get(l1, l1 + mid) == b.get(l2, l2 + mid))
        low = mid;
      else
        high = mid;
    }
    return (low);
  }
};