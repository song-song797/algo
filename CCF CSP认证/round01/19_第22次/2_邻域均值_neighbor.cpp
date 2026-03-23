/*
 * 邻域均值 (neighbor)
 * CCF CSP 第22次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, l, r, t;
  cin >> n >> l >> r >> t;

  vector<vector<int>> prefix(n + 2, vector<int>(n + 2, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int A;
      cin >> A;
      prefix[i][j] =
          prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + A;
    }
  }

  int res = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int a = i + r >= n ? n : (i + r);
      int b = j + r >= n ? n : (j + r);
      int c = i - r - 1 <= 0 ? 0 : (i - r - 1);
      int d = j - r - 1 <= 0 ? 0 : (j - r - 1);
      int sum = prefix[a][b] - prefix[a][d] - prefix[c][b] + prefix[c][d];
      int num = 0;
      num += (a - c) * (b - d);
      if (sum <= t * num)
        res++;
    }
  }

  cout << res << '\n';
  return 0;
}
