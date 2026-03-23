/*
 * 机器人饲养指南 (feed)
 * CCF CSP 第37次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 机器人一天最多可以吃 m 个苹果。
 * 一天内通过吃苹果获得的快乐值为 A0,A1,...,Am；
 * 如果某一天投喂 i 个苹果，则获得快乐值 Ai（A0=0）。
 * 现在有 n 个苹果，求投喂全部 n 个苹果能获得的最大快乐值。
 *
 * 输入格式：
 * 第一行包含两个整数 n 和 m，分别表示苹果总数和每天最大投喂量。
 * 第二行依次包含 m 个整数 A1,A2,...,Am。
 *
 * 输出格式：
 * 输出一个整数，表示投喂全部 n 个苹果能获得的最大收益。
 *
 * 数据范围：
 * 40% 的数据：n<=50 且 m=5
 * 另有 40% 的数据：n=60 且 m=6
 * 全部数据：0<n<=10^4, 0<m<=100 且 0<=Ai<=10^5
 *
 * 样例输入1：
 * 10 5
 * 1 3 5 3 1
 *
 * 样例输出1：
 * 16
 *
 * 样例输入2：
 * 4 3
 * 1 60 100
 *
 * 样例输出2：
 * 120
 */

#include <bits/stdc++.h>
using namespace std;
/* int A[105];
int dp[10005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> A[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m && j <= i; j++) {
      dp[i] = max(dp[i], dp[i - j] + A[j]);
    }
  }
  cout << dp[n] << '\n';
  return 0;
} */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> A(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        cin >> A[i];
    }
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 0 && j >= i - m; j--) {
            dp[i] = max(dp[i], dp[j] + A[i - j]);
        }
    }
    cout << dp[n] << '\n';
}