/*
 * 期末预测之安全指数 (safety)
 * CCF CSP 第21次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <iostream>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int res = 0;
  for (int i = 0; i < n; i++) {
    int w, score;
    cin >> w >> score;
    res += w * score;
  }

  cout << max(0, res) << '\n';

  return 0;
}
