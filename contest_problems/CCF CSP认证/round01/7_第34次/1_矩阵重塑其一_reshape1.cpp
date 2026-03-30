/*
 * 矩阵重塑（其一） (reshape1)
 * CCF CSP 第34次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 给定 n×m 的矩阵 M 和目标形状 p、q，将 M 重塑为 p×q 的矩阵 M'。
 * 重塑操作：先按行优先线性化原矩阵，再按行优先填充新矩阵。
 *
 * 输入格式：
 * 第一行四个正整数 n、m、p、q。
 * 接下来 n 行每行 m 个整数。
 *
 * 输出格式：
 * p 行每行 q 个整数。
 *
 * 数据范围：
 * n*m=p*q<=10^4，元素绝对值不超过 1000。
 *
 * 样例输入：
 * 2 3 3 2
 * 1 2 3
 * 4 5 6
 *
 * 样例输出：
 * 1 2
 * 3 4
 * 5 6
 */

#include <iostream>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, p, q;
  cin >> n >> m >> p >> q;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int k;
      cin >> k;
      if ((i * m + j + 1) % q == 0) {
        cout << k << '\n';
      } else {
        cout << k << ' ';
      }
    }
  }
  return 0;
}
