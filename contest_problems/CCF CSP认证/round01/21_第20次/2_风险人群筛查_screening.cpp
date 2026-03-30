/*
 * 风险人群筛查 (screening)
 * CCF CSP 第20次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k, t, xl, yd, xr, yu;
  cin >> n >> k >> t >> xl >> yd >> xr >> yu;

  int passer = 0;
  int count = 0;
  for (int i = 1; i <= n; i++) {
    bool valid = false;
    bool stayed = false;
    int current = 0;
    for (int j = 1; j <= t; j++) {
      int x, y;
      cin >> x >> y;
      if (x >= xl && x <= xr && y <= yu && y >= yd) {
        valid = true;
        current++;
        if (current >= k && stayed == false) {
          count++;
          stayed = true;
        }
      } else {
        current = 0;
      }
    }
    if (valid) {
      passer++;
    }
  }
  cout << passer << '\n';
  cout << count << '\n';

  return 0;
}
