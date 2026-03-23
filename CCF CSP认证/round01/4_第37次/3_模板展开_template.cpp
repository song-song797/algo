/*
 * 模板展开 (template)
 * CCF CSP 第37次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 实现一种模板语言，支持变量和代换。数据类型为字符串（由[a-z0-9]组成）。
 *
 * 表达式由空格分隔的操作数组成：
 * - 以$开头的操作数是变量，剩余部分为变量名
 * - 否则为字符串常量
 * 表达式的值 = 将变量替换为其值后拼接所有操作数
 *
 * 三种语句：
 * 1 <var> <expr>：直接赋值，求表达式的值并赋给变量
 * 2 <var>
 * <expr>：间接赋值，不立即求值，每次用到该变量时重新求值（惰性/动态绑定） 3
 * <var>：输出变量值的长度 mod 1000000007
 *
 * 所有变量初始值为空字符串。保证不存在循环依赖。
 *
 * 输入格式：
 * 第一行整数 n 表示语句数量。
 * 接下来 n 行，每行一个语句。
 *
 * 输出格式：
 * 对每个输出语句，输出一行变量值长度 mod 1000000007。
 *
 * 样例输入1：
 * 6
 * 1 a hello
 * 1 b world
 * 2 c $a $b
 * 3 c
 * 1 a hi
 * 3 c
 *
 * 样例输出1：
 * 10
 * 7
 *
 * 样例输入2：
 * 5
 * 1 var value
 * 3 var
 * 3 val
 * 1 var $var $val $var
 * 3 var
 *
 * 样例输出2：
 * 5
 * 0
 * 10
 */

#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007;
unordered_map<string, long long> val;
unordered_map<string, vector<string>> expr;
unordered_map<string, long long> memo;
long long dfs(const string &s) {
  if (memo.count(s)) {
    return memo[s];
  }
  if (val.count(s)) {
    return memo[s] = val[s];
  }
  long long res = 0;
  for (auto e : expr[s]) {
    if (e[0] == '$') {
      string temp = e.substr(1);
      res = (res + dfs(temp)) % MOD;
    } else {
      res = (res + e.size()) % MOD;
    }
  }
  return memo[s] = res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  cin.get();

  while (n--) {
    memo.clear();
    string line;
    getline(cin, line);
    stringstream ss(line);
    int op;
    string cur;
    ss >> op >> cur;
    if (op == 1) {
      expr.erase(cur);
      long long new_len = 0;
      string part;
      while (ss >> part) {
        if (part[0] == '$') {
          new_len = (new_len + dfs(part.substr(1))) % MOD;
        } else {
          new_len = (new_len + (long long)part.size()) % MOD;
        }
      }
      val[cur] = new_len;
    }
    if (op == 2) {
      val.erase(cur);
      string part;
      expr[cur].clear();
      while (ss >> part) {
        expr[cur].push_back(part);
      }
    }
    if (op == 3) {
      cout << dfs(cur) << '\n';
    }
  }
  return 0;
}
