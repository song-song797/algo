/*
 * 通讯延迟 (delay)
 * CCF CSP 第35次认证 真题4
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 给定二维平面上 n 个节点和 m 个通讯基站。
 * 第 i 个基站覆盖以 (xi,yi) 为中心、2ri 为边长的正方形区域，
 * 区域内所有节点可以以 ti 单位时间的延迟进行通讯。
 * 求节点 1 到 n 的最短通讯延迟。
 *
 * 输入格式：
 * 第一行两个正整数 n、m。
 * 接下来 n 行每行两个整数（节点坐标）。
 * 接下来 m 行每行四个整数（基站坐标、半径、延迟）。
 *
 * 输出格式：
 * 输出最短通讯延迟；如果无法通讯，输出 Nan。
 *
 * 数据范围：
 * n,m<=5000, 0<=xi,yi,ri<=10^9, 1<=ti<=10^5。
 *
 * 样例输入：
 * 5 5
 * 0 0
 * 2 4
 * 4 0
 * 5 3
 * 5 5
 * 1 2 2 5
 * 3 5 2 6
 * 2 0 2 1
 * 4 2 2 3
 * 5 4 1 2
 *
 * 样例输出：
 * 6
 */

#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int graph[105][105];
struct Node {
    int x;
    int y;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(&graph[0][0], &graph[0][0] + 105 * 105, 1e9);

    int n, m;
    cin >> n >> m;

    vector<Node> nodes(n + 1);
    for (int i = 1; i <= n; i++) { cin >> nodes[i].x >> nodes[i].y; }
    for (int i = 1; i <= m; i++) {
        int x, y, r, t;
        cin >> x >> y >> r >> t;
        vector<int> neighbors;
        for (int j = 1; j <= n; j++) {
            if (nodes[j].x >= x - r && nodes[j].x <= x + r && nodes[j].y >= y - r && nodes[j].y <= y + r) {
                neighbors.push_back(j);
            }
        }
        for (int k = 0; k < (int)neighbors.size() - 1; k++) {
            for (int l = k + 1; l < neighbors.size(); l++) {
                graph[neighbors[k]][neighbors[l]] = min(graph[neighbors[k]][neighbors[l]], t);
                graph[neighbors[l]][neighbors[k]] = graph[neighbors[k]][neighbors[l]];
            }
        }
    }
    vector<int> dist(n + 1, INF);
    dist[1] = 0;
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++) {
        int u = 0;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < dist[u]) { u = j; }
        }
        visited[u] = true;
        for (int v = 1; v <= n; v++) {
            if (visited[v] == true) continue;
            dist[v] = min(dist[v], dist[u] + graph[u][v]);
        }
    }
    if (dist[n] == INF) {
        cout << "Nan\n";
    } else {
        cout << dist[n] << '\n';
    }
    return 0;
}
