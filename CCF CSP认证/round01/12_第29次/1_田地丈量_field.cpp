/*
 * 田地丈量 (field)
 * CCF CSP 第29次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <iostream>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, a, b;
  cin >> n >> a >> b;
  int res = 0;
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int nx, ny;
    if (x2 <= 0 || x1 >= a || y2 <= 0 || y1 >= b)
      continue;
    if (x1 <= 0 && x2 > 0 && x2 <= a) {
      nx = x2;
    } else if (x1 > 0 && x2 <= a) {
      nx = x2 - x1;
    } else if (x1 > 0 && x1 <= a && x2 > a) {
      nx = a - x1;
    } else if (x1 <= 0 && x2 > a) {
      nx = a;
    }
    if (y1 <= 0 && y2 > 0 && y2 <= b) {
      ny = y2;
    } else if (y1 > 0 && y2 <= b) {
      ny = y2 - y1;
    } else if (y1 > 0 && y1 <= b && y2 > b) {
      ny = b - y1;
    } else if (y1 <= 0 && y2 > b) {
      ny = b;
    }
    res += nx * ny;
  }
  cout << res << '\n';
  return 0;
}
