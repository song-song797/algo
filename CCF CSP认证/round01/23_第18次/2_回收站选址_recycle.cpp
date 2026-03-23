/*
 * 回收站选址 (recycle)
 * CCF CSP 第18次认证 真题2
 */

#include <bits/stdc++.h>
using namespace std;
int res[10];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  set<pair<int, int>> points;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    points.insert({x, y});
  }

  for (auto [x, y] : points) {
    int count = 0;
    if (!points.count({x - 1, y}) || !points.count({x, y - 1}) ||
        !points.count({x + 1, y}) || !points.count({x, y + 1}))
      continue;
    if (points.count({x - 1, y - 1}))
      count++;
    if (points.count({x + 1, y - 1}))
      count++;
    if (points.count({x - 1, y + 1}))
      count++;
    if (points.count({x + 1, y + 1}))
      count++;
    res[count]++;
  }

  for (int i = 0; i < 5; i++) {
    cout << res[i] << '\n';
  }
  return 0;
}
