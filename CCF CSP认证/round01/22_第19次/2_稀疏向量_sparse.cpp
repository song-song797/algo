/*
 * 稀疏向量 (sparse)
 * CCF CSP 第19次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, a, b;
  cin >> n >> a >> b;

  vector<pair<int, int>> u(a + 1);
  vector<pair<int, int>> v(b + 1);
  long long res = 0;
  for (int i = 1; i <= a; i++) {
    cin >> u[i].first >> u[i].second;
  }
  for (int i = 1; i <= b; i++) {
    cin >> v[i].first >> v[i].second;
  }

  int i = 1;
  int j = 1;
  while (i <= a && j <= b) {
    if (u[i].first < v[j].first) {
      i++;
    } else if (u[i].first > v[j].first) {
      j++;
    } else {
      res += (long long)u[i].second * v[j].second;
      i++;
      j++;
    }
  }
  cout << res << '\n';
  return 0;
}
