/*
 * 出行计划 (travel)
 * CCF CSP 第25次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int diff[200005];
int prefix[200005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> t(n + 1, 0);
  vector<int> c(n + 1, 0);

  for (int i = 1; i <= n; i++) {
    cin >> t[i] >> c[i];
    int left = max(1, t[i] - c[i] - k + 1);
    int right = max(0, t[i] - k);
    diff[left]++;
    diff[right + 1]--;
  }
  for (int i = 1; i <= 200005; i++) {
    prefix[i] = prefix[i - 1] + diff[i];
  }

  for (int i = 0; i < m; i++) {
    int q;
    cin >> q;

    cout << prefix[q] << '\n';
  }
  return 0;
}
