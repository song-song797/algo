/*
 * 阴阳龙 (dragon)
 * CCF CSP 第31次认证 真题4
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * n×m 的网格上有 p 名员工。阴阳龙在某位置以强度 t 现身时，
 * 会找到八个方向上最近的员工距离 k，然后将距离为 k 的员工
 * 以阴阳龙位置为中心逆时针旋转 t 倍的八分之一圆周。
 * 求 q 次现身后所有员工的最终位置。
 *
 * 输入格式：
 * 第一行四个正整数 n,m,p,q。
 * 接下来 p 行员工位置，q 行现身事件。
 *
 * 输出格式：
 * 一个整数（所有员工位置的异或和）。
 *
 * 数据范围：
 * 1<=n,m<=10^9, 1<=p,q<=10^5, 1<=ti<=7。
 *
 * 样例输入：
 * 3 3 9 1
 * 1 1
 * 1 2
 * 1 3
 * 2 1
 * 2 2
 * 2 3
 * 3 1
 * 3 2
 * 3 3
 * 2 2 1
 *
 * 样例输出：
 * 20
 */

#include <bits/stdc++.h>
using namespace std;

struct Employee {
    int x;
    int y;
};

int dirX[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int dirY[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p, q;
    cin >> n >> m >> p >> q;

    vector<Employee> employees(p + 1);
    for (int i = 1; i <= p; i++) { cin >> employees[i].x >> employees[i].y; }

    while (q--) {
        int u, v, t;
        cin >> u >> v >> t;
        int limit = min({u - 1, n - u, v - 1, m - v});
        int k = INT_MAX;

        for (int i = 1; i <= p; i++) {
            if (employees[i].x == u && employees[i].y == v) continue;
            if (employees[i].x != u && employees[i].y != v && (abs(employees[i].x - u) != abs(employees[i].y - v)))
                continue;

            int dist = 0;
            if (employees[i].x == u) {
                dist = abs(employees[i].y - v);
            } else {
                dist = abs(employees[i].x - u);
            }

            if (dist > 0 && dist <= limit) { k = min(k, dist); }
        }

        if (k == INT_MAX) { k = 0; }

        if (k > 0) {
            for (int i = 1; i <= p; i++) {
                long long dx = employees[i].x - u;
                long long dy = employees[i].y - v;

                if (employees[i].x == u && employees[i].y == v) continue;
                if (employees[i].x != u && employees[i].y != v && (abs(dx) != abs(dy))) continue;

                int dist = (employees[i].x == u) ? abs(dy) : abs(dx);

                if (dist == k) {
                    int current_dir = -1;
                    for (int d = 0; d < 8; d++) {
                        if (dirX[d] * k == dx && dirY[d] * k == dy) {
                            current_dir = d;
                            break;
                        }
                    }
                    if (current_dir != -1) {
                        int new_dir = (current_dir + t) % 8;
                        employees[i].x = u + k * dirX[new_dir];
                        employees[i].y = v + k * dirY[new_dir];
                    }
                }
            }
        }
    }

    long long ans = 0;
    for (long long i = 1; i <= p; i++) { ans ^= (i * employees[i].x + employees[i].y); }

    cout << ans << "\n";
    return 0;
}
