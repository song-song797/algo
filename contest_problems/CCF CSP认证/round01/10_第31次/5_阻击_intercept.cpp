#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 防爆 int 神器
#define int long long

// 核心改变：Edge 里不再存具体的 weight，而是存输入时的编号 id
struct Edge {
    int v;
    int id;
};

const int MAXN = 100005;
vector<vector<Edge>> adj;

// 全局大数组，专门按照出厂编号记录道路属性
int W[MAXN];
int B[MAXN];

int ans = 0;

int dfs(int u, int father) {
    int max_single_length = 0;
    for (auto edge : adj[u]) {
        int v = edge.v;
        int id = edge.id;

        if (v == father) continue;

        // 1. 根据 id 实时去查全局数组，算出当前的综合损失
        int weight = B[id] - W[id];

        // 2. 递归获取子树单边最大值
        int child_val = dfs(v, u);

        // 3. 负权剪断
        int val = max(0LL, child_val + weight);

        // 4. 挑战全局最优 (拼接)
        ans = max(ans, max_single_length + val);

        // 5. 更新当前节点的最长单边 (留给父节点)
        max_single_length = max(max_single_length, val);
    }
    return max_single_length;
}

signed main() {
    // 优化输入输出流，防止大数据读写超时
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);

    // 读入 n-1 条边，编号从 1 到 n-1
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w, b;
        cin >> u >> v >> w >> b;
        W[i] = w; // 记录第 i 条边的收益
        B[i] = b; // 记录第 i 条边的损失

        // 建图时只存终点和编号 id
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    // 初始状态的答案
    ans = 0;
    dfs(1, 0);
    cout << ans << '\n';

    // 处理 M 次阴阳龙事件
    while (m--) {
        int x, y;
        cin >> x >> y;

        // O(1) 瞬间修改！不需要去图里翻找这条边
        W[x] = y;

        // 重新跑一遍图，记得清空历史答案
        ans = 0;
        dfs(1, 0);
        cout << ans << '\n';
    }

    return 0;
}