/*
 * 报数 (count)
 * CCF CSP 第18次认证 真题1
 */

#include <iostream>
using namespace std;
int res[10];
bool contain(int a) {
  while (a != 0) {
    int current = a % 10;
    a = a / 10;
    if (current == 7)
      return true;
  }
  return false;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int current_num = 1;
  int valid_count = 0;
  while (valid_count < n) {
    if (current_num % 7 == 0 || contain(current_num)) {
      res[current_num % 4]++;
    } else {
      valid_count++;
    }
    current_num++;
  }

  for (int i = 1; i < 4; i++) {
    cout << res[i] << '\n';
  }
  cout << res[0] << '\n';
  return 0;
}
