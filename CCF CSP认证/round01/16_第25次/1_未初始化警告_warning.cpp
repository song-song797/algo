/*
 * 未初始化警告 (warning)
 * CCF CSP 第25次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;

  vector<bool> visited(n + 1, false);
  visited[0] = true;
  int ans = 0;
  for (int i = 0; i < k; i++) {
    int x, y;
    cin >> x >> y;

    if (!visited[y])
      ans++;
    visited[x] = true;
  }

  cout << ans << '\n';
  return 0;
}
