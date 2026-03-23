/*
 * 如此编码 (encode)
 * CCF CSP 第27次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <iostream>
#include <vector>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  int a;
  for (int i = 1; i <= n; i++) {
    cin >> a;
    cout << m % a << ' ';
    m = m / a;
  }

  return 0;
}
