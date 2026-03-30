/*
 * 坐标变换（其一） (coord1)
 * CCF CSP 第31次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 包含 n 个平移操作的序列 T，每个操作将 (x,y) 平移至 (x+dxi,y+dyi)。
 * 给定 m 个初始坐标，计算依次进行 T 中 n 个操作后的最终坐标。
 *
 * 输入格式：
 * 第一行两个正整数 n 和 m。
 * 接下来 n 行操作，m 行坐标。
 *
 * 输出格式：
 * m 行，每行两个整数。
 *
 * 数据范围：
 * n,m<=100，所有数据绝对值不超过 10^5。
 *
 * 样例输入：
 * 3 2
 * 10 10
 * 0 0
 * 10 -20
 * 1 -1
 * 0 0
 *
 * 样例输出：
 * 21 -11
 * 20 -10
 */

#include <iostream>
#include <vector>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> change(n, vector<int>(2, 0));
  for (int i = 0; i < n; i++) {
    cin >> change[i][0] >> change[i][1];
  }
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    for (int j = 0; j < n; j++) {
      x = x + change[j][0];
      y = y + change[j][1];
    }
    cout << x << ' ' << y << '\n';
  }
  return 0;
}
