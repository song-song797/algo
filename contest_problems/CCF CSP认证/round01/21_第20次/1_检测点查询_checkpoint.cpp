/*
 * 检测点查询 (checkpoint)
 * CCF CSP 第20次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, x, y;
  cin >> n >> x >> y;

  vector<tuple<int, int, int>> positions(n);
  for (int i = 0; i < n; i++) {
    cin >> get<0>(positions[i]) >> get<1>(positions[i]);
    get<2>(positions[i]) = i + 1;
  }

  sort(positions.begin(), positions.end(),
       [&](const tuple<int, int, int> &A, const tuple<int, int, int> &B) {
         int distance1 = (get<0>(A) - x) * (get<0>(A) - x) +
                         (get<1>(A) - y) * (get<1>(A) - y);
         int distance2 = (get<0>(B) - x) * (get<0>(B) - x) +
                         (get<1>(B) - y) * (get<1>(B) - y);
         if (distance1 != distance2)
           return distance1 < distance2;
         return get<2>(A) < get<2>(B);
       });
  for (int i = 0; i < 3; i++) {
    cout << get<2>(positions[i]) << '\n';
  }
  return 0;
}
