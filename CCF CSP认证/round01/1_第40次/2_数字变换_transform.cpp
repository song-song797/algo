/*
 * 数字变换 (transform)
 * CCF CSP 第40次认证 真题2
 * 时间限制: 1.5秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 小C设计了一种变换F，若输入[0,2^9)中的整数，则输出也是[0,2^9)中的整数。
 * 记XOR为按位异或运算。
 *
 * 若x,k均为[0,2^3)内的整数，定义 f(x,k) = ((x^2 + k^2) mod 2^3) XOR k。
 *
 * 若x为[0,2^9)内的整数，k为[0,2^3)内的整数。将x的二进制表示高位补零为9位。
 * g(x,k)将这9个二进制位分为高三位a、中三位b、低三位c三组并分别变换：
 *   g(x,k) 的结果为: 高三位=b, 中三位=c XOR f(b,k), 低三位=a XOR f(c,k)
 *
 * 记f0为F变换的输入值，fi = g(f(i-1), ki), i∈{1,2,...,m}，则fm为F变换的输出值。
 * 长为m的序列k是一个给定的参数序列，每个数字都是[0,2^3)之间的整数。
 *
 * 现在小C有n个经过F变换后得到的值a1,a2,...,an，求它们对应的输入。
 *
 * 输入格式：
 * 第一行两个正整数n,m。
 * 第二行有m个非负整数k1,k2,...,km。
 * 第三行有n个非负整数a1,a2,...,an。
 *
 * 输出格式：
 * 输出一行n个非负整数，表示a1,...,an对应的输入。
 *
 * 样例输入：
 * 1 2
 * 3 5
 * 504
 *
 * 样例输出：
 * 101
 *
 * 数据范围：
 * 80%: 1<=n<=100, 1<=m<=20
 * 100%: 1<=n<=5*10^5, 1<=m<=10^3, 0<=ki<2^3, 0<=ai<2^9
 *       且只有唯一的输入能够得到这些输出。
 */

#include <bits/stdc++.h>

using namespace std;
/*#define mod (1 << 3)
int caculate_f(int x, int k);
int caculate_g(int x, int k) {
  int c = x & 7;
  int b = (x >> 3) & 7;
  int a = (x >> 6) & 7;
  int c1 = b ^ caculate_f(a, k);
  int b1 = a;
  int a1 = c ^ caculate_f(c1, k);
  return a1 << 6 | b1 << 3 | c1;
}
int caculate_f(int x, int k) { return ((x * x + k * k) % mod) ^ k; }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> k(m + 1);
  for (int i = 1; i <= m; i++) {
    cin >> k[i];
  }
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<int> memo(513);
  for (int i = 0; i <= 512; i++) {
    memo[i] = i;
  }
  for (int i = 0; i < 512; i++) {
    for (int j = 1; j <= m; j++) {
      memo[i] = caculate_g(memo[i], k[m - j + 1]);
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << memo[a[i]] << ' ';
  }
}*/
#define MOD 8
int calculate_f(int x, int k) {
    return ((x * x + k * k) % MOD) ^ k;
}
int calculate_g(int f, int k) {
    int c1 = f & 7;
    int b1 = (f >> 3) & 7;
    int a1 = (f >> 6) & 7;
    int b = a1;
    int c = b1 ^ calculate_f(b, k);
    int a = c1 ^ calculate_f(c, k);
    return c + (b << 3) + (a << 6);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> k(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        cin >> k[i];
    }
    vector<int> a(n + 1, 0);
    vector<int> ans(512);
    iota(ans.begin(), ans.end(), 0);
    for (int i = 0; i < 512; i++) {
        for (int j = m; j >= 1; j--) {
            ans[i] = calculate_g(ans[i], k[j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cout << ans[a[i]] << ' ';
    }
}