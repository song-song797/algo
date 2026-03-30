/*
 * 垦田计划 (reclaim)
 * CCF CSP 第29次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;

static bool check_limit(const vector<pair<int, int>>& area, int limit, long long budget) {
  long long total = 0;
  for (const auto& [day, cost] : area) {
    if (day > limit) {
      total += 1LL * (day - limit) * cost;
      if (total > budget) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  long long m;
  cin >> n >> m >> k;
  vector<pair<int, int>> area(n);
  for (int i = 0; i < n; i++) {
    cin >> area[i].first >> area[i].second;
  }
  int left = k;
  int right = (int)1e9 + 1;
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (check_limit(area, mid, m)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  cout << left << '\n';
  return 0;
}
