/*
 * 树上搜索 (treesearch)
 * CCF CSP 第32次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * n 个类别构成树形结构，每个类别有权重 wi。
 * 使用二分策略确定名词的类别：
 * 1. 对每个类别统计其及后代权重之和与其余类别权重之和的差值绝对值 wδ；
 * 2. 选 wδ 最小的类别询问（多个则选编号最小的）；
 * 3. 根据回答保留或排除该类别及后代；
 * 4. 重复直到只剩一个类别。
 *
 * 输入格式：
 * 第一行两个正整数 n 和 m。
 * 第二行 n 个正整数（权重）。
 * 第三行 n-1 个正整数（父类别编号）。
 * 接下来 m 行每行一个正整数（待测试的类别编号）。
 *
 * 输出格式：
 * m 行，每行若干个正整数（提问的类别编号序列）。
 *
 * 数据范围：
 * n<=2000, m<=100, wi<=10^7。
 *
 * 样例输入：
 * 5 2
 * 10 50 10 10 20
 * 1 1 3 3
 * 5
 * 3
 *
 * 样例输出：
 * 2 5
 * 2 5 3 4
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m; // n表示全部类别的数量,m表示需要测试的类别的数量
  cin >> n >> m;

  vector<int> w(n + 1, 0);
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
  }
  vector<int> child[2005];
  for (int i = 2; i <= n; i++) {
    int fr;
    cin >> fr;
    child[fr].push_back(i);
  }

  while (m--) {
    int test;
    cin >> test;
    vector<int> res;
    vector<long long> weights(n + 1, 0);
    bool valid[2005];
    fill(valid, valid + 2005, true);
    while (count(valid + 1, valid + n + 1, true) > 1) {
      auto get_sum = [&](auto &self, int i) -> long long {
        long long res = 0;
        if (valid[i])
          res = w[i];
        for (auto c : child[i]) {
          res += self(self, c);
        }
        return weights[i] = res;
      };
      get_sum(get_sum, 1);
      long long sum = 0;
      for (int i = 1; i <= n; i++) {
        if (valid[i])
          sum += w[i];
      }
      auto find_best = [&]() -> int {
        long long min_val = INT64_MAX;
        int min_idx = 0;
        for (int i = 1; i <= n; i++) {
          if (!valid[i])
            continue;
          if (min_val > abs(sum - 2 * weights[i])) {
            min_val = abs(sum - 2 * weights[i]);
            min_idx = i;
          }
        }
        return min_idx;
      };
      int min_idx = find_best();
      res.push_back(min_idx);

      auto is_son = [&](auto &self, int min_idx) -> bool {
        bool res = false;
        if (min_idx == test)
          return true;
        for (auto c : child[min_idx]) {
          res = res || self(self, c);
          if (res)
            break;
        }
        return res;
      };
      bool v = is_son(is_son, min_idx);
      auto invalidate = [&](auto &self, int i) -> void {
        valid[i] = false;
        for (auto c : child[i]) {
          self(self, c);
        }
      };
      auto validate = [&](auto &self, int i) -> void {
        valid[i] = true;
        for (auto c : child[i]) {
          self(self, c);
        }
      };
      if (!v) {
        invalidate(invalidate, min_idx);
      } else {
        bool in_subtree[2005] = {false};
        auto validate1 = [&](auto &self, int i) -> void {
          in_subtree[i] = true;
          for (auto c : child[i]) {
            self(self, c);
          }
        };
        validate1(validate1, min_idx);
        for (int i = 1; i <= n; i++) {
          valid[i] = valid[i] && in_subtree[i];
        }
      }
    }
    for (auto r : res) {
      cout << r << ' ';
    }
    cout << '\n';
  }
  return 0;
}
