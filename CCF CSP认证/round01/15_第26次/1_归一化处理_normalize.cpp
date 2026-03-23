/*
 * 归一化处理 (normalize)
 * CCF CSP 第26次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  cout << fixed << setprecision(16);
  vector<int> a(n + 1, 0);
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum += a[i];
  }
  double avg = double(sum) / n;
  double nD = 0;
  for (int i = 1; i <= n; i++) {
    nD += (a[i] - avg) * (a[i] - avg);
  }
  double D = nD / n;
  double S_D = sqrt(D);
  for (int i = 1; i <= n; i++) {
    cout << (a[i] - avg) / S_D << '\n';
  }
  return 0;
}
