/*
 * 梦境巡查 (patrol)
 * CCF CSP 第36次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 梦境中的西西艾弗岛由 n+1 个区域组成。梦境巡查员顿顿每天都会从梦之源出发，
 * 顺次巡查 1,2,...,n 号区域，最后从 n 号区域返回梦之源。
 * 从第 i 号区域前往下一区域需要消耗 ai 单位能量；
 * 顺利到达第 i 号区域后可以汲取 bi 单位能量作为补给。
 * 现在考虑有且仅有一个区域发生意外（bi 变为 0），
 * 求每个区域发生意外时，为顺利完成巡查需要携带的最少初始能量 w(i)。
 *
 * 输入格式：
 * 第一行包含一个整数 n。
 * 第二行包含 n+1 个整数 a0,a1,...,an。
 * 第三行包含 n 个整数 b1,b2,...,bn。
 *
 * 输出格式：
 * 输出一行，包含 n 个整数 w(1),w(2),...,w(n)。
 *
 * 数据范围：
 * 0<n<=10^5 且 0<=ai,bi<=1000。
 *
 * 样例输入1：
 * 3
 * 5 5 5 5
 * 0 100 0
 *
 * 样例输出1：
 * 10 20 10
 *
 * 样例输入2：
 * 3
 * 9 4 6 2
 * 9 4 6
 *
 * 样例输出2：
 * 15 10 9
 */

#include <iostream>
#include <vector>
using namespace std;
/* int a[100005];
int b[100005];
int prefixA[100005];
int prefixB[100005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  int w = 0;
  cin >> a[0];
  prefixA[0] = a[0];
  for (int i = 0; i < n; i++) {
    cin >> a[i + 1];
    prefixA[i + 1] = prefixA[i] + a[i + 1];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i + 1];
    prefixB[i + 1] = prefixB[i] + b[i + 1];
    w = max(w, prefixA[i] - prefixB[i]);
  }
  w = max(w, prefixA[n] - prefixB[n]);
  vector<int> dp(n + 1, 0);
  for (int i = n; i >= 0; i--) {
    dp[i] = max(a[i], dp[i + 1] + a[i] - b[i + 1]);
  }
  for (int i = 1; i <= n; i++) {
    int current_energy = w - prefixA[i - 1] + prefixB[i - 1];
    if (current_energy >= dp[i]) {
      cout << w << ' ';
    } else {
      cout << w + (dp[i] - current_energy) << ' ';
    }
  }
  return 0; 
}*/
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    vector<int> prefixA(n + 1, 0);
    vector<int> b(n+1, 0);
    vector<int> prefixB(n + 1, 0);
    for (int i = 0; i <= n;i++){
        cin >> a[i];
        if(i==0){
            prefixA[i] = a[i];
        }else{
            prefixA[i] = prefixA[i - 1] + a[i];
        }
    }
    int min_w = a[0];
    for (int i = 1; i <= n;i++){
        cin >> b[i];
        prefixB[i] = prefixB[i - 1] + b[i];
        min_w = max(min_w, prefixA[i] - prefixB[i]);
    }
    vector<int> dp(n + 1, 0);
    dp[n] = prefixA[n] - prefixB[n];
    for (int i = n - 1; i >= 1; i--) {
        dp[i] = max(dp[i + 1], prefixA[i] - prefixB[i]);
    }
    for (int i = 1; i <= n;i++){
        cout << max(min_w, dp[i]+b[i]) << ' ';
    }
}
