/*
 * 序列查询 (query)
 * CCF CSP 第24次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, N;
  cin >> n >> N;

  vector<int> A(n + 1, 0);
  long long sum = 0;
  int count = 0;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    sum +=(long long) (A[i] - A[i - 1]) * count;
    count++;
  }
  sum += (long long)(N - A[n]) * count;

  cout << sum << '\n';

  return 0;
}
