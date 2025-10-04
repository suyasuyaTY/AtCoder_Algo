#include <bits/stdc++.h>

#include <atcoder/all>

using namespace std;
using namespace atcoder;

// 短縮表記
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using uint = unsigned;
using pcc = pair<char, char>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<ld, ld>;
using tuplis = array<ll, 3>;
template <class T>
using pq = priority_queue<T, vector<T>, greater<T>>;

// 定数
const ll LINF = 0x1fffffffffffffff;
const int INF = 0x3fffffff;
const ll dx[] = {0, 1, 0, -1, 1, -1, 1, -1};
const ll dy[] = {1, 0, -1, 0, 1, 1, -1, -1};

template <typename T> bool chmin(T &a, T b) { return (a > b ? (a = b, true) : false); }
template <typename T> bool chmax(T &a, T b) { return (a < b ? (a = b, true) : false); }

// 入出力
void Yes(bool i = true) { cout << (i ? "Yes\n" : "No\n"); }
void No() { cout << "No\n"; }
void flushf() { cout << flush; }
void line_break() { cout << '\n'; }

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
}