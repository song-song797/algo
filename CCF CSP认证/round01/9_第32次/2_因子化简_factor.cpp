/*
 * 因子化简 (factor)
 * CCF CSP 第32次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 正整数 n 可以唯一表示为若干素因子相乘。
 * 设定阈值 k，指数小于 k 的素因子项从 n 中除去，剩余项乘积即简化后的值。
 *
 * 输入格式：
 * 第一行正整数 q。
 * 接下来 q 行每行两个正整数 n 和 k。
 *
 * 输出格式：
 * q 行，每行一个正整数。
 *
 * 数据范围：
 * 1<n<=10^10, 1<k,q<=10。
 *
 * 样例输入：
 * 3
 * 2155895064 3
 * 2 2
 * 10000000000 10
 *
 * 样例输出：
 * 2238728
 * 1
 * 10000000000
 */

#include <cmath>
#include <iostream>

using namespace std;
long long fast_pow(long long a, long long b) {
  long long result = 1;
  while (b > 0) {
    if (b & 1) {
      result *= a;
    }
    a *= a;
    b >>= 1;
  }
  return result;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  while (q--) {
    long long n;
    int k;
    cin >> n >> k;
    int counts[100005] = {0};
    long long temp = n;
    for (int i = 2; i <= sqrt(temp); i++) {
      while (temp % i == 0) {
        temp = temp / i;
        counts[i]++;
      }
    }
    long long result = 1;
    for (int i = 2; i <= sqrt(n); i++) {
      if (counts[i] >= k) {
        result = result * fast_pow(i, counts[i]);
      }
    }
    cout << result << '\n';
  }
  return 0;
}
