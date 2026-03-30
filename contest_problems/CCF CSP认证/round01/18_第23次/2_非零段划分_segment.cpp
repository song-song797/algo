/*
 * 非零段划分 (segment)
 * CCF CSP 第23次认证 真题2
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> A;
  A.push_back(0); // 头部垫上 0，方便边界处理

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    // 关键修复 1：相邻相同的元素直接压缩，消除“平原”带来的干扰
    if (A.back() != x) {
      A.push_back(x);
    }
  }
  A.push_back(0); // 尾部垫上 0，方便边界处理

  int m = A.size();
  vector<pair<int, int>> B;
  int res = 0;

  // 计算初始状态下的非零段个数
  for (int i = 1; i < m - 1; i++) {
    if (A[i] > 0 && A[i - 1] == 0) {
      res++;
    }
    B.push_back({A[i], i});
  }

  // 关键修复 2：初始最大值应为未作任何修改（p=1）时的非零段个数
  int max_val = res;

  // 按数值从小到大排序
  sort(B.begin(), B.end());

  for (int i = 0; i < B.size(); i++) {
    if (B[i].first == 0)
      continue; // 0 本身就是水位线底，无需处理

    int idx = B[i].second;

    // 因为已经去重，相邻元素绝不相等，只存在严格大于或严格小于的情况
    if (A[idx - 1] > B[i].first && A[idx + 1] > B[i].first) {
      res++; // 当前点是“波谷”，被淹没后一段变两段
    } else if (A[idx - 1] < B[i].first && A[idx + 1] < B[i].first) {
      res--; // 当前点是“波峰”，被淹没后该岛屿消失
    }

    // 关键修复
    // 3：只有当遍历到最后一个元素，或者下一个元素的值与当前不同时，才结算
    // max_val
    if (i == B.size() - 1 || B[i].first != B[i + 1].first) {
      max_val = max(max_val, res);
    }
  }

  cout << max_val << '\n';
  return 0;
}