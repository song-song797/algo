/*
 * 计算资源调度器 (scheduler)
 * CCF CSP 第25次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
struct Node {
  int zone_id;
  int task_count = 0;
  unordered_set<int> apps;
};

vector<int> filter_nodes(int a, int na, int pa, int paa, vector<Node> &nodes,
                         unordered_map<int, unordered_set<int>> &app_zones) {
  int n = nodes.size() - 1;
  vector<int> res;
  for (int i = 1; i <= n; i++) {
    if (na != 0 && nodes[i].zone_id != na)
      continue;
    if (pa != 0 && (app_zones[nodes[i].zone_id].empty() ||
                    !app_zones[nodes[i].zone_id].count(pa)))
      continue;
    if (paa != 0 && nodes[i].apps.count(paa))
      continue;
    res.push_back(i);
  }
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  unordered_map<int, unordered_set<int>> app_zones;
  vector<Node> nodes(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> nodes[i].zone_id;
  }

  int g;
  cin >> g;
  for (int i = 0; i < g; i++) {
    int f, a, na, pa, paa, paar;
    cin >> f >> a >> na >> pa >> paa >> paar;
    for (int j = 0; j < f; j++) {
      vector<int> res = filter_nodes(a, na, pa, paa, nodes, app_zones);
      if (res.empty() && paar == 1) {
        cout << 0 << ' ';
        continue;
      }
      if (res.empty() && paar == 0) {
        res = filter_nodes(a, na, pa, 0, nodes, app_zones);
      }
      if (res.empty()) {
        cout << 0 << ' ';
        continue;
      } else {
        int ans = *min_element(
            res.begin(), res.end(), [&](const int &A, const int &B) {
              if (nodes[A].task_count != nodes[B].task_count) {
                return nodes[A].task_count < nodes[B].task_count;
              }
              return A < B;
            });
        cout << ans << ' ';
        nodes[ans].task_count++;
        nodes[ans].apps.insert(a);
        app_zones[nodes[ans].zone_id].insert(a);
      }
    }
    cout << '\n';
  }
  return 0;
}
