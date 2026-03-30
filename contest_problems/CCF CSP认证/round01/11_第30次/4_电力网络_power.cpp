/*
 * 电力网络 (power)
 * CCF CSP 第30次认证 真题4
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * N 座城镇需要建造变电站和输电线路。
 * 每座城镇有 K 个变电站候选地址，造价不同。
 * 输电线路造价随两端候选地址变化。
 * 求电网的最低总造价。
 *
 * 输入格式：
 * 第一行三个正整数 N、M、K。
 * 接下来 N 行变电站造价，M 行输电线路信息。
 *
 * 输出格式：
 * 一个整数，最低总造价。
 *
 * 数据范围：
 * N<=10^4, K<=10, 造价不超过 1000。
 *
 * 样例输入：
 * 2 1 2
 * 1 2
 * 3 4
 * 0 1 1 2 3 4
 *
 * 样例输出：
 * 5
 */

#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int u;
    int v;
    vector<vector<int>> T;
};
bool visited[10000];
vector<int> path;
vector<vector<int>> price;
vector<Edge> edges;
int min_price = INT_MAX;
void dfs(int u, int N, int K) {
    if (u == N) {
        int sum = 0;
        fill(visited, visited + 10000, false);
        for (size_t i = 0; i < edges.size(); i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            if (!visited[u]) {
                visited[u] = true;
                sum += price[u][path[u]];
            }
            if (!visited[v]) {
                visited[v] = true;
                sum += price[v][path[v]];
            }
            sum += edges[i].T[path[u]][path[v]];
        }
        min_price = min(min_price, sum);
        return;
    }
    for (int i = 0; i < K; i++) {
        path.push_back(i);
        dfs(u + 1, N, K);
        path.pop_back();
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;
    price.resize(N, vector<int>(K, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) { cin >> price[i][j]; }
    }
    edges.resize(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v;
        edges[i].T.resize(K, vector<int>(K));
        for (int k = 0; k < K; k++) {
            for (int j = 0; j < K; j++) { cin >> edges[i].T[k][j]; }
        }
    }
    dfs(0, N, K);
    cout << min_price << '\n';

    return 0;
}
