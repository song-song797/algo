/*
 * 仓库规划 (warehouse)
 * CCF CSP 第32次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * n 个仓库各有一个 m 维向量位置编码。
 * 仓库 j 可以成为仓库 i 的上级，当且仅当 j 的编码每一维均大于 i 的对应元素。
 * 如果有多个满足条件的仓库，选编号最小的；没有则该仓库是物流中心。
 *
 * 输入格式：
 * 第一行两个正整数 n 和 m。
 * 接下来 n 行每行 m 个整数。
 *
 * 输出格式：
 * n 行，每行一个整数（上级编号或 0）。
 *
 * 数据范围：
 * 0<m<=10, 0<n<=1000, 元素绝对值不大于 10^6。
 *
 * 样例输入：
 * 4 2
 * 0 0
 * -1 -1
 * 1 2
 * 0 -1
 *
 * 样例输出：
 * 3
 * 1
 * 0
 * 3
 */

#include <iostream>
#include <vector>
using namespace std;
bool compare(vector<int> &A, vector<int> &B, int m) {
  for (int i = 1; i <= m; i++) {
    if (A[i] >= B[i])
      return false;
  }
  return true;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> house(n + 1, vector<int>(m + 1, 0));
  vector<int> result(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> house[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j)
        continue;
      if (!compare(house[i], house[j], m)) {
        continue;
      }
      if (result[i] == 0) {
        result[i] = j;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << result[i] << '\n';
  }
  return 0;
}
