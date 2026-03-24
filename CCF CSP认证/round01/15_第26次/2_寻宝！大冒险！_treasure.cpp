/*
 * 寻宝！大冒险！ (treasure)
 * CCF CSP 第26次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, l, s;
  cin >> n >> l >> s;
  vector<pair<int, int>> positions(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    positions[i] = {x, y};
  }
  vector<vector<int>> S(s + 1, vector<int>(s + 1, 0));
  int count1 = 0;
  for (int i = s; i >= 0; i--) {
    for (int j = 0; j <= s; j++) {
      cin >> S[i][j];
      if (S[i][j] == 1)
        count1++;
    }
  }
  int count = 0;
  for (int i = 0; i < n; i++) {
    bool valid = true;
    int temp = count1;
    if (positions[i].first + s > l || positions[i].second + s > l)
      continue;
    for (int j = 0; j < n; j++) {
      int cx = positions[j].first - positions[i].first;
      int cy = positions[j].second - positions[i].second;
      if (cx < 0 || cx > s || cy < 0 || cy > s)
        continue;
      if (S[cx][cy] != 1) {
        valid = false;
        break;
      }
      temp--;
    }
    if (valid && temp == 0)
      count++;
  }
  cout << count << '\n';
  return 0;
}
