/*
 * 彩色路径 (colorpath)
 * CCF CSP 第32次认证 真题5
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * N 个节点 M 条有向边的图，每个节点有颜色标签 C[i]。
 * 找一条从 0 到 N-1 的简单路径，要求：
 * - 路径上每个节点颜色不同（彩色路径）；
 * - 节点数 <= L；
 * - 最大化路径长度（边的总长度）。
 *
 * 输入格式：
 * 第一行四个正整数 N、M、L、K。
 * 第二行 N 个整数（颜色标签）。
 * 第三行 M 个整数（边的起点）。
 * 第四行 M 个整数（边的终点）。
 * 第五行 M 个整数（边的长度）。
 *
 * 输出格式：
 * 一个数，最大路径长度。
 *
 * 数据范围：
 * 2<=N<=100, 1<=M<=5000, 2<=L<=9<=K<=30, 1<=D[j]<=10^6。
 *
 * 样例输入：
 * 6 9 4 10
 * 0 2 2 3 3 9
 * 0 0 0 1 1 1 2 3 4
 * 1 2 4 3 4 5 4 5 5
 * 1 2 4 3 2 8 5 3 1
 *
 * 样例输出：
 * 9
 */

#include <bits/stdc++.h>
using namespace std;
struct edge {
    int V;
    int D;
};
bool color[105];
int dfs(int u, int L, int N, int current_nodes, int current_len, const vector<vector<edge>> &adj,
        const vector<int> &C) {
    if (u == N - 1) { return current_len; }
    if (current_nodes == L) { return 0; }
    color[C[u]] = true;
    int max_len = 0;
    for (auto eg : adj[u]) {
        if (color[C[eg.V]]) continue;
        int temp = dfs(eg.V, L, N, current_nodes + 1, current_len + eg.D, adj, C);
        max_len = max(max_len, temp);
    }
    color[C[u]] = false;
    return max_len;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, L, K;
    cin >> N >> M >> L >> K;

    vector<int> C(N);
    for (int i = 0; i < N; i++) { cin >> C[i]; }
    vector<int> U(M);
    for (int i = 0; i < M; i++) { cin >> U[i]; }
    vector<int> V(M);
    for (int i = 0; i < M; i++) { cin >> V[i]; }
    vector<int> D(M);
    for (int i = 0; i < M; i++) { cin >> D[i]; }

    vector<vector<edge>> adj(N);
    for (int i = 0; i < M; i++) {
        edge eg;
        eg.V = V[i];
        eg.D = D[i];
        adj[U[i]].push_back(eg);
    }

    int res = dfs(0, L, N, 1, 0, adj, C);
    cout << res << '\n';

    return 0;
}
