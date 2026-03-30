/*
 * 灰度直方图 (histogram)
 * CCF CSP 第22次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int res[260];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, l;
  cin >> n >> m >> l;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int A;
      cin >> A;
      res[A]++;
    }
  }

  for (int i = 0; i < l; i++) {
    cout << res[i] << ' ';
  }

  return 0;
}
