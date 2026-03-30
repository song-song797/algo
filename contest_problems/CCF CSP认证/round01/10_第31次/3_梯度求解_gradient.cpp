/*
 * 梯度求解 (gradient)
 * CCF CSP 第31次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 给定函数 f(x1,...,xn) 的逆波兰式表示，仅由常数、自变量和加减乘组成。
 * 求 f 对 xi 在给定点处的偏导数，结果对 10^9+7 取模。
 *
 * 输入格式：
 * 第一行两个正整数 n、m。
 * 第二行逆波兰式。
 * 接下来 m 行，每行 n+1 个整数。
 *
 * 输出格式：
 * m 行，每行一个整数。
 *
 * 数据范围：
 * n<=100, m<=100, 常数和坐标在 [-10^5, 10^5] 之间。
 *
 * 样例输入：
 * 2 2
 * x1 x1 x1 * x2 + *
 * 1 2 3
 * 2 3 4
 *
 * 样例输出：
 * 15
 * 3
 */

#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
struct Data {
  long long val;
  long long der;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  cin.get();

  string s;
  getline(cin, s);

  vector<int> x_val(n + 1);
  while (m--) {
    int idx;
    cin >> idx;
    for (int i = 1; i <= n; i++) {
      cin >> x_val[i];
    }
    stack<Data> stk;
    stringstream ss(s);
    string current;
    while (ss >> current) {
      if (current[0] == 'x') {
        string temp = current.substr(1);
        long long curr_idx = stoi(temp);
        if (idx == stoi(temp)) {
          Data d1;
          d1.val = x_val[idx];
          d1.der = 1;
          stk.push(d1);
        } else {
          Data d2;
          d2.val = x_val[curr_idx];
          d2.der = 0;
          stk.push(d2);
        }
      } else if (current[0] == '+') {
        Data d1 = stk.top();
        stk.pop();
        Data d2 = stk.top();
        stk.pop();
        Data d3;
        d3.val = ((d1.val + d2.val) % MOD + MOD) % MOD;
        d3.der = ((d1.der + d2.der) % MOD + MOD) % MOD;
        stk.push(d3);
      } else if (current[0] == '-' && current.size() == 1) {
        Data d1 = stk.top();
        stk.pop();
        Data d2 = stk.top();
        stk.pop();
        Data d3;
        d3.val = ((d2.val - d1.val) % MOD + MOD) % MOD;
        d3.der = ((d2.der - d1.der) % MOD + MOD) % MOD;
        stk.push(d3);
      } else if (current[0] == '*') {
        Data d1 = stk.top();
        stk.pop();
        Data d2 = stk.top();
        stk.pop();
        Data d3;
        d3.val = ((d2.val * d1.val) % MOD + MOD) % MOD;
        d3.der = ((d1.der * d2.val + d1.val * d2.der) % MOD + MOD) % MOD;
        stk.push(d3);
      } else {
        Data d2;
        d2.val = stoi(current);
        d2.der = 0;
        stk.push(d2);
      }
    }
    Data d = stk.top();
    cout << d.der << '\n';
  }
  return 0;
}
