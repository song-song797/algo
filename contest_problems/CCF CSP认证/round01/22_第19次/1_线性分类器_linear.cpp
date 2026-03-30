/*
 * 线性分类器 (linear)
 * CCF CSP 第19次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> points(n + 1, vector<int>(2, 0));
  vector<char> type(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> points[i][0] >> points[i][1];
    cin >> type[i];
  }

  while (m--) {
    long long theta0, theta1, theta2;
    cin >> theta0 >> theta1 >> theta2;
    int a = 0;
    int b = 0;
    bool valid = true;
    for (int i = 1; i <= n; i++) {
      long long value = theta0 + theta1 * points[i][0] + theta2 * points[i][1];
      if (type[i] == 'A' && value > 0 && a == 0) {
        a = 1;
      }
      if (type[i] == 'A' && value < 0 && a == 0) {
        a = -1;
      }
      if (type[i] == 'B' && value > 0 && b == 0) {
        b = 1;
      }
      if (type[i] == 'B' && value < 0 && b == 0) {
        b = -1;
      }
      if (type[i] == 'A' && value > 0 && a == -1) {
        valid = false;
        break;
      }
      if (type[i] == 'A' && value < 0 && a == 1) {
        valid = false;
        break;
      }
      if (type[i] == 'B' && value > 0 && b == -1) {
        valid = false;
        break;
      }
      if (type[i] == 'B' && value < 0 && b == 1) {
        valid = false;
        break;
      }
    }
    if (a == b || valid == false) {
      cout << "No" << '\n';
    } else {
      cout << "Yes" << '\n';
    }
  }
  return 0;
}
