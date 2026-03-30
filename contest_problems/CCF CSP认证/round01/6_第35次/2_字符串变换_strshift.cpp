/*
 * 字符串变换 (strshift)
 * CCF CSP 第35次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 定义一个字符替换函数 f(ch)，可以扩展为字符串变换函数 F(s)。
 * 给定初始字符串 s，处理 m 个查询：每个查询包含正整数 k，
 * 询问对初始字符串 s 变换 k 次后的结果。
 *
 * 输入格式：
 * 第一行 #s# 形式的初始字符串。
 * 第二行正整数 n，接下来 n 行 #xy# 形式的字符对。
 * 第 n+3 行正整数 m，下一行 m 个正整数。
 *
 * 输出格式：
 * m 行，每行 #s# 形式的变换结果。
 *
 * 数据范围：
 * 0<n<=63, 0<m<=10^3, 0<k<=10^9，字符串不超过100个字符。
 *
 * 样例输入：
 * #Hello World#
 * 6
 * #HH#
 * #e #
 * # r#
 * #re#
 * #oa#
 * #ao#
 * 3
 * 1 2 3
 *
 * 样例输出：
 * #H llarWaeld#
 * #HrlloeWo ld#
 * #Hella Warld#
 */

#include<bits/stdc++.h>
using namespace std;
/* string history[1000];
char arr[256];
void multiply(char A[256], char B[256], char C[256]) {
  char temp[256];
  for (int i = 0; i < 256; i++) {
    temp[i] = B[A[i]];
  }
  for (int i = 0; i < 256; i++) {
    C[i] = temp[i];
  }
}
void solve(int k, char original_rule[256], const string &s) {
  char ans[256];
  char base[256];
  for (int i = 0; i < 256; i++) {
    ans[i] = i;
    base[i] = arr[i];
  }
  while (k > 0) {
    if (k % 2 == 1) {
      multiply(ans, base, ans);
    }
    multiply(base, base, base);
    k = k / 2;
  }
  for (const char &c : s) {
    cout << ans[c];
  }
  cout << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  getline(cin, s);
  for (int i = 0; i < 256; i++) {
    arr[i] = (char)i;
  }
  int n;
  cin >> n;
  cin.ignore();
  for (int i = 0; i < n; i++) {
    string current;
    getline(cin, current);
    arr[current[1]] = current[2];
  }
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int k;
    cin >> k;
    solve(k, arr, s);
  }
} */

