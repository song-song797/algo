/*
 * 货物调度 (dispatch)
 * CCF CSP 第34次认证 真题4
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 共有 n 间仓库，m 件货物。为获得至少 v 的现金，需选取一些货物卖出。
 * 每件货物存放在某个仓库中，价值为 ai。
 * 调用仓库需付基本费 bj 和计件费 k*cj。
 * 求满足目标前提下的最小花费。
 *
 * 输入格式：
 * 第一行三个正整数 n、m、v。
 * 接下来 n 行仓库信息（bj, cj），m 行货物信息（ai, ti）。
 *
 * 输出格式：
 * 一个整数，表示最小花费。
 *
 * 数据范围：
 * 0<n,m<=1000, 0<bj,cj<=20, 0<ai<=1000, 0<v<=10^6。
 *
 * 样例输入：
 * 2 3 15
 * 2 1
 * 3 2
 * 10 0
 * 20 1
 * 15 0
 *
 * 样例输出：
 * 4
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Store {
    int b;
    int c;
};
struct Item {
    int a;
    int t;
};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, v;
    cin >> n >> m >> v;

    vector<Store> stores(n);
    for (int i = 0; i < n; i++) { cin >> stores[i].b >> stores[i].c; }
    vector<Item> items(m);
    for (int i = 0; i < m; i++) { cin >> items[i].a >> items[i].t; }

    if (m > 15) return 0;
    int res = 1e9;
    for (int i = 0; i <= (1 << m) - 1; i++) {
        int value = 0;
        int cost = 0;
        bool visited[1005] = {false};
        for (int k = 0; k < m; k++) {
            if ((i >> k) & 1) {
                value += items[k].a;
                cost += stores[items[k].t].c;
                if (!visited[items[k].t]) { cost += stores[items[k].t].b; }
                visited[items[k].t] = true;
            }
        }
        if (value - cost >= v) { res = min(res, cost); }
    }
    cout << res << '\n';
    return 0;
}
