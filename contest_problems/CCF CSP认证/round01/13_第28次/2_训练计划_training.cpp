/*
 * 训练计划 (training)
 * CCF CSP 第28次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> p(m + 1, 0);
  vector<int> t(m + 1, 0);
  for (int i = 1; i <= m; i++) {
    cin >> p[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> t[i];
  }
  vector<int> earlist(m + 1, 0);
  earlist[0] = 1;
  bool valid = true;
  for (int i = 1; i <= m; i++) {
    earlist[i] = earlist[p[i]] + t[p[i]];
  }
  for (int i = 1; i <= m; i++) {
    if (earlist[i] + t[i] - 1 > n)
      valid = false;
    cout << earlist[i] << ' ';
  }
  cout << '\n';
  if (valid == false)
    return 0;
  vector<int> latest(m + 1);
  for (int i = 1; i <= m; i++) {
    latest[i] = n - t[i] + 1;
  }
  latest[0] = n;
  for (int i = m; i >= 1; i--) {
    latest[p[i]] = min(latest[p[i]], latest[i] - t[p[i]]);
  }
  for (int i = 1; i <= m; i++) {
    cout << latest[i] << ' ';
  }

  return 0;
}
