/*
 * 数组推导 (array)
 * CCF CSP 第23次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> B(n + 1, 0);
  int sum_max = 0;
  int sum_min = 0;

  for (int i = 1; i <= n; i++) {
    cin >> B[i];
    sum_max += B[i];
    if (B[i] != B[i - 1])
      sum_min += B[i];
  }

  cout << sum_max << '\n';
  cout << sum_min << '\n';

  return 0;
}
