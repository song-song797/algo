/*
 * 现值计算 (present)
 * CCF CSP 第28次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  double i;
  cin >> n >> i;
  cout << fixed << setprecision(3);
  double res = 0;
  for (int k = 0; k <= n; k++) {
    int x;
    cin >> x;
    res += x * pow(1 + i, -k);
  }
  cout << res << '\n';
  return 0;
}
