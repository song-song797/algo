/*
 * 期末预测之最佳阈值 (threshold)
 * CCF CSP 第21次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<pair<int, int>> p(n + 1, {-1, -1});
  int count0 = 0;
  int count1 = 0;
  for (int i = 1; i <= n; i++) {
    cin >> p[i].first >> p[i].second;
    if (p[i].second == 0)
      count0++;
    else
      count1++;
  }
  sort(p.begin(), p.end());

  int max_val = 0;
  int res = -1;
  for (int i = n; i >= 1; i--) {
    if ((p[i].second == 1)) {
      count0++;
      count1--;
    } else {
      count1++;
      count0--;
    }
    if (p[i].first != p[i - 1].first && count0 > max_val) {
      res = p[i].first;
      max_val = count0;
    }
  }

  cout << res << '\n';
  return 0;
}
