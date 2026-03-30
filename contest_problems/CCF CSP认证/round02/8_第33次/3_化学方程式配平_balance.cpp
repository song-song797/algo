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
    unordered_map<string, vector<double>> mp;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        string current_element = "";
        string current_num = "";
        for (int j = 0; j < s.size();) {
            while (j < s.size() && !(s[j] >= '0' && s[j] <= '9')) {
                current_element += s[j];
                j++;
            }
            while (j < s.size() && s[j] >= '0' && s[j] <= '9') {
                current_num += s[j];
                j++;
            }
            if (!mp.count(current_element))
                mp[current_element].assign(m, 0);
            mp[current_element][i] = stod(current_num);
            current_element = "";
            current_num = "";
        }
    }
    int element_num = mp.size();
    vector<vector<double>> matrix;
    for (auto A : mp) {
        matrix.push_back(A.second);
    }
    int row = 0;
    int col = 0;
    while (row < element_num && col < m) {
        bool valid = false;
        for (int i = row; i < element_num; i++) {
            if (abs(matrix[i][col]) > 1e-6)
                valid = true;
        }
        if (!valid) {
            col++;
            continue;
        } else {
            if (abs(matrix[row][col]) < 1e-6) {
                bool is_find = false;
                for (int i = row + 1; i < element_num; i++) {
                    if (abs(matrix[i][col]) > 1e-6) {
                        swap(matrix[row], matrix[i]);
                        is_find = true;
                        break;
                    }
                }
                if (!is_find) {
                    col++;
                    continue;
                }
            }
            for (int i = row + 1; i < element_num; i++) {
                if (abs(matrix[i][col]) < 1e-6) {
                    continue;
                }
                double mul = matrix[i][col] / matrix[row][col];
                for (int j = col; j < m; j++) {
                    matrix[i][j] -= matrix[row][j] * mul;
                }
            }
        }
        row++;
        col++;
    }

    int rank = row;
    if (rank < m) {
        cout << "Y" << '\n';
    } else {
        cout << "N" << '\n';
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
