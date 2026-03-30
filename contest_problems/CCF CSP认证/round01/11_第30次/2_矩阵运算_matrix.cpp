/*
 * 矩阵运算 (matrix)
 * CCF CSP 第30次认证 真题2
 * 时间限制: 5.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 计算 (W·(Q×K^T))×V，其中 Q、K、V 是 n×d 矩阵，W 是大小为 n 的向量。
 * 点乘即对应位相乘：将 (Q×K^T) 第 i 行的每个元素都与 W(i) 相乘。
 *
 * 输入格式：
 * 第一行两个正整数 n 和 d。
 * 接下来依次输入 Q、K、V 各 n 行 d 列，最后一行输入向量 W。
 *
 * 输出格式：
 * n 行每行 d 个整数。
 *
 * 数据范围：
 * n<=10^4, d<=20, 元素绝对值不超过 1000。
 *
 * 样例输入：
 * 3 2
 * 1 2
 * 3 4
 * 5 6
 * 10 10
 * -20 -20
 * 30 30
 * 6 5
 * 4 3
 * 2 1
 * 4 0 -5
 *
 * 样例输出：
 * 480 240
 * 0 0
 * -2200 -1100
 */

#include <iostream>
#include <vector>
#define int long long
using namespace std;
vector<vector<int>> multiply_matrix(const vector<vector<int>> &A,
                                    const vector<vector<int>> &B) {
  int n = A.size();
  int d = A[0].size();
  int m = B[0].size();
  vector<vector<int>> res(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) {
      for (int k = 0; k < m; k++) {
        res[i][k] += A[i][j] * B[j][k];
      }
    }
  }
  return res;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, d;
  cin >> n >> d;
  vector<vector<int>> Q(n, vector<int>(d, 0));
  vector<vector<int>> K_T(d, vector<int>(n, 0));
  vector<vector<int>> V(n, vector<int>(d, 0));
  vector<int> W(n, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) {
      cin >> Q[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) {
      cin >> K_T[j][i];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) {
      cin >> V[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    cin >> W[i];
  }
  vector<vector<int>> temp(n, vector<int>(n, 0));
  temp = multiply_matrix(Q, K_T);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      temp[i][j] *= W[i];
    }
  }
  vector<vector<int>> ans(n, vector<int>(d, 0));
  ans = multiply_matrix(temp, V);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) {
      cout << ans[i][j] << ' ';
    }
    cout << '\n';
  }
  return 0;
}
