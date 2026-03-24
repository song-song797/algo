/*
 * 哥德尔机 (godel)
 * CCF CSP 第34次认证 真题5
 * 时间限制: 5.0秒  内存限制: 1024 MiB
 *
 * 题目描述：
 * 神经网络维护一个二维矩阵 V，初始权重为 0。
 * n 轮学习操作，每轮给出 x1,x2,y1,y2,v，对范围内的 (x,y)，
 * 将 V(x,y) 修改为 v+ReLU(V(x,y)-v)。
 * m 次推理操作，每次查询子矩阵范围内最大的权重。
 *
 * 输入格式：
 * 第一行两个整数 n,m。
 * 接下来 n 行每行五个整数（学习操作）。
 * 接下来 m 行每行四个整数（推理操作）。
 *
 * 输出格式：
 * m 行，每行一个整数（查询结果）。
 *
 * 数据范围：
 * 1<=n,m<=5*10^5, 1<=x1<=x2<=n, 1<=y1<=y2<=n, 1<=v<=n。
 *
 * 样例输入：
 * 5 5
 * 1 3 2 3 3
 * 4 5 2 5 1
 * 3 5 1 2 1
 * 2 5 3 4 4
 * 1 4 3 4 2
 * 1 5 2 5
 * 1 5 2 5
 * 1 5 1 5
 * 1 4 1 5
 * 2 5 1 3
 *
 * 样例输出：
 * 4
 * 4
 * 4
 * 4
 * 4
 */

#include <bits/stdc++.h>
using namespace std;
int matrix[10005][10005] = {0};
int parent[10005][10005];
struct Operation {
    int x1, x2, y1, y2, v;
    bool operator<(const Operation &other) const { return v > other.v; }
};
int find(int row, int y) {
    if (y == parent[row][y]) return y;
    return parent[row][y] = find(row, parent[row][y]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) { parent[i][j] = j; }
    }
    vector<Operation> operations(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> operations[i].x1 >> operations[i].x2 >> operations[i].y1 >> operations[i].y2 >> operations[i].v;
    }
    sort(operations.begin() + 1, operations.end());

    for (int i = 1; i <= n; i++) {
        int x1 = operations[i].x1;
        int x2 = operations[i].x2;
        int y1 = operations[i].y1;
        int y2 = operations[i].y2;
        int v = operations[i].v;
        for (int row = x1; row <= x2; row++) {
            int curr = find(row, y1);
            while (curr <= y2) {
                matrix[row][curr] = v;
                parent[row][curr] = find(row, curr + 1);
                curr = parent[row][curr];
            }
        }
    }

    while (m--) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        int ans = 0;
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) { ans = max(matrix[i][j], ans); }
        }
        cout << ans << '\n';
    }

    return 0;
}
