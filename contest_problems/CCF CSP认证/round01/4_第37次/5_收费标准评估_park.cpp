/*
 * 收费标准评估 (park)
 * CCF CSP 第37次认证 真题5
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * n 个景点构成一棵树，第 i 号景点收费 ai（可为负数）。
 * 初始时 1 号为根（演出景点）。
 * 基本费用 = 从根入园游览一次的最大花费（选择包含根的连通子集使权值和最大）。
 *
 * 处理 m 个操作：
 * 1 u：查询仅开放 u 子树时，从任意景点入园的最大花费（不影响后续）
 * 2 u x：将 a_u 改为 x，重新计算基本费用
 * 3 u：将根改为 u，重新计算基本费用
 * 4 a b c d：删边(a,b)加边(c,d)，重新计算基本费用
 *
 * 输入格式：
 * 第一行 n,m。
 * 第二行 n 个整数 ai。
 * 接下来 n-1 行每行两个整数 u,v 表示边。
 * 接下来 m 行每行一个操作。
 *
 * 输出格式：
 * 输出 m+1 行，初始基本费用及每次操作结果。
 *
 * 数据范围：
 * 子任务一(15分)：n,m<=3000，只有操作1,2
 * 子任务二(15分)：n,m<=10^5，只有操作1,2，深度<=100
 * 子任务三(40分)：n,m<=10^5，只有操作1,2
 * 子任务四(30分)：无特殊限制
 * 全部数据：1<=n,m<=10^5, -10^9<=ai,x<=10^9
 *
 * 样例输入：
 * 5 4
 * -5 7 9 -3 1
 * 1 2
 * 1 4
 * 2 3
 * 4 5
 * 1 1
 * 3 2
 * 2 5 7
 * 4 5 4 1 5
 *
 * 样例输出：
 * 11
 * 16
 * 16
 * 16
 * 18
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
int fa[100005];
int max_res = -1e18;
int dfs(int u, int p, const vector<vector<int>> &adj, const vector<int> &a) {
    int ans = 0;
    ans += a[u];
    for (auto v : adj[u]) {
        if (p == v) fa[v] = u;
        int res = dfs(v, fa[v], adj, a);
        if (res > 0) ans += res;
    }
    max_res = max(max_res, ans);
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) { cin >> a[i]; }
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = dfs(1, 0, adj, a);
    cout << ans << '\n';
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int u;
            cin >> u;
            max_res = -1e18;
            dfs(u, fa[u], adj, a);
            cout << max_res << '\n';
        }
        if (op == 2) {
            int u, x;
            cin >> u >> x;
            a[u] = x;
            max_res = -1e18;
            int ans = dfs(1, 0, adj, a);
            cout << ans << '\n';
        }
    }
    return 0;
}
