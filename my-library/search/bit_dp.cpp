const int INF = 100000000;  // 十分大きな値

/* 入力 */
int N;
int dist[21][21];

/* メモ再帰 */
int dp[(1 << 20) + 1][21];  // dpテーブルは余裕をもったサイズにする
int rec(int bit, int v) {
  // すでに探索済みだったらリターン
  if (dp[bit][v] != -1)
    return dp[bit][v];

  // 初期値
  if (bit == (1 << v)) {
    return dp[bit][v] = 0;
  }

  // 答えを格納する変数
  int res = INF;

  // bit の v を除いたもの
  int prev_bit = bit & ~(1 << v);

  // v の手前のノードとして u を全探索
  for (int u = 0; u < N; ++u) {
    if (!(prev_bit & (1 << u)))
      continue;  // u が prev_bit になかったらダメ

    // 再帰的に探索
    if (res > rec(prev_bit, u) + dist[u][v]) {
      res = rec(prev_bit, u) + dist[u][v];
    }
  }

  return dp[bit][v] = res;  // メモしながらリターン
}