/*
 * 序列查询新解 (query2)
 * CCF CSP 第24次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */
#define debug(x) cout << 'x' << '=' << x << '\n';
#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, N;
  cin >> n >> N;

  vector<int> A(n + 1, 0);
  int r = N / (n + 1);
  long long error_sum = 0;

  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }

  long long L = 0;
  int i = 1;
  int j = 1;
  while (L < N) {
    int R1 = i > n ? N - 1 : (A[i] - 1);
    int R2 = r * j - 1 >= N ? (N - 1) : (r * j - 1);
    int R = min(R1, R2);
    error_sum += (abs(i - j) * (R - L + 1));
    L = R + 1;
    if (R == R1) {
      i++;
    };
    if (R == R2) {
      j++;
    }
  }

  cout << error_sum << '\n';
  return 0;
}
