/*
 * 何以包邮？ (shipping)
 * CCF CSP 第27次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <algorithm>
#include <climits>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
bool dp[300005] = {false};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, x;
  cin >> n >> x;
  vector<int> a(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  int sum = accumulate(a.begin(), a.end(), 0);
  dp[0] = true;
  for (int i = 1; i <= n; i++) {
    for (int j = sum; j >= a[i]; j--) {
      dp[j] = dp[j] || dp[j - a[i]];
    }
  }
  for (int i = x; i <= sum; i++) {
    if (dp[i]) {
      cout << i << '\n';
      break;
    }
  }

  return 0;
}
