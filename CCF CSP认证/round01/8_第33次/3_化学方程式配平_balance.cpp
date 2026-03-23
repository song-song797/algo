/*
 * 化学方程式配平 (balance)
 * CCF CSP 第33次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 给出一些化学方程式，判断它们是否可以配平。
 * 通过构建齐次线性方程组，判断系数矩阵的秩是否小于未知数个数。
 * 化学式已被化简为只包含小写字母和数字的字符串。
 *
 * 输入格式：
 * 第一行正整数 n。
 * 接下来 n 行，每行先输入正整数 m，再输入 m 个化学式字符串。
 *
 * 输出格式：
 * n 行，每行 Y 或 N。
 *
 * 数据范围：
 * 物质个数和元素种数不超过 40，1<=n<=10，原子个数不超过 50。
 *
 * 样例输入：
 * 6
 * 2 o2 o3
 * 3 c1o1 c1o2 o2
 * 2 n2o4 n1o2
 * 4 cu1 h1n1o3 cu1n2o6 h2o1
 * 4 al2s3o12 n1h5o1 al1o3h3 n2h8s1o4
 * 4 c1o1 c1o2 o2 h2o1
 *
 * 样例输出：
 * Y
 * Y
 * Y
 * N
 * Y
 * Y
 */

#include <bits/stdc++.h>
using namespace std;
void solve() {
  int m;
  cin >> m;
  vector<unordered_map<string, int>> count(m);
  vector<string> strs(m);
  unordered_map<string, int> elements;
  int id = 0;
  for (int i = 0; i < m; i++) {
    cin >> strs[i];
    string s = "";
    for (int j = 0; j < strs[i].size(); j++) {
      if (strs[i][j] >= '0' && strs[i][j] <= '9') {
        string num_str = "";
        while (j < strs[i].size() && strs[i][j] >= '0' && strs[i][j] <= '9') {
          num_str += strs[i][j];
          j++;
        }
        j--;
        int num = stoi(num_str);
        if (!elements.count(s)) {
          elements[s] = id;
          id++;
        }
        count[i][s] += num;
        s = "";
      } else {
        s += strs[i][j];
      }
    }
  }
  int element_count = elements.size();
  vector<vector<double>> matrix(element_count, vector<double>(m, 0));
  for (int i = 0; i < m; i++) {
    for (auto pair : count[i]) {
      string element_name = pair.first;
      int element_num = pair.second;
      int row_index = elements[element_name];
      matrix[row_index][i] = element_num;
    }
  }
  int r = 0;
  for (int c = 0; c < m; c++) {
    int pivot_row = -1;
    for (int i = r; i < element_count; i++) {
      if (abs(matrix[i][c]) > 1e-9) {
        pivot_row = i;
        break;
      }
    }
    if (pivot_row == -1)
      continue;
    swap(matrix[r], matrix[pivot_row]);
    for (int i = r + 1; i < element_count; i++) {
      if (abs(matrix[i][c]) < 1e-9)
        continue;
      double rate = matrix[i][c] / matrix[r][c];
      for (int j = c; j < m; j++) {
        matrix[i][j] -= rate * matrix[r][j];
      }
    }
    r++;
  }
  if (r < m)
    cout << 'Y' << '\n';
  else {
    cout << 'N' << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  while (n--) {
    solve();
  }
  return 0;
}
