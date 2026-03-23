/*
 * 缓存模拟 (cache)
 * CCF CSP 第36次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 模拟 n-路组相联缓存的工作过程。
 * 缓存采用 LRU（最近最少使用）替换策略。
 * 给定一系列内存读写指令，输出处理器对内存的实际读写操作序列。
 *
 * 输入格式：
 * 第一行三个整数 n,N,q，分别表示组相联路数、组数和指令数量。
 * 接下来 q 行，每行两个整数 o 和 a（o=0读/1写，a为内存块编号）。
 *
 * 输出格式：
 * 若干行，每行两个整数 o' 和 a'，表示实际对内存的读写操作。
 *
 * 数据范围：
 * 1<=n,N,n*N<=65536，n,N 为 2 的幂次；1<=q<=10^5，0<=a<2^30。
 *
 * 样例输入：
 * 4 8 8
 * 0 0
 * 0 1
 * 1 2
 * 0 1
 * 1 0
 * 0 32
 * 1 33
 * 0 34
 *
 * 样例输出：
 * 0 0
 * 0 1
 * 0 2
 * 0 32
 * 1 2
 * 0 33
 * 0 34
 */

#include <bits/stdc++.h>
using namespace std;
struct Node {
  int key;
  bool is_modified = false;
  Node(int key) { this->key = key; }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, N, q;
  cin >> n >> N >> q;

  vector<unordered_map<int, list<Node>::iterator>> lru(N);
  vector<list<Node>> cache_set(N);
  while (q--) {
    int o, a;
    cin >> o >> a;
    int act = (a / n) % N;
    if (o == 0) {
      Node A(a);
      if (!lru[act].count(a)) {
        cache_set[act].push_front(A);
        if (cache_set[act].size() > n) {
          if (cache_set[act].back().is_modified) {
            cout << 1 << " " << cache_set[act].back().key << "\n";
          }
          lru[act].erase(cache_set[act].back().key);
          cache_set[act].pop_back();
        }
        lru[act][a] = cache_set[act].begin();
        cout << 0 << " " << a << "\n";
      } else {
        cache_set[act].splice(cache_set[act].begin(), cache_set[act],
                              lru[act][a]);
      }
    }
    if (o == 1) {
      Node A(a);
      A.is_modified = true;
      if (!lru[act].count(a)) {
        if (cache_set[act].size() == n) {
          if (cache_set[act].back().is_modified) {
            cout << 1 << " " << cache_set[act].back().key << "\n";
          }
          lru[act].erase(cache_set[act].back().key);
          cache_set[act].pop_back();
        }
        cache_set[act].push_front(A);
        lru[act][a] = cache_set[act].begin();
        cout << 0 << " " << a << "\n";
      } else {
        cache_set[act].splice(cache_set[act].begin(), cache_set[act],
                              lru[act][a]);
        cache_set[act].begin()->is_modified = true;
      }
    }
  }
  return 0;
}
