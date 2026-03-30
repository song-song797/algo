/*
 * 十滴水 (droplet)
 * CCF CSP 第33次认证 真题4
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 一维版本的十滴水游戏。1×c 的网格，m 个格子有 1~4 滴水。
 * 每次操作选一个有水的格子加一滴水，水滴数>=5 时爆开：
 * 水被清空，左右两个方向最近的有水格子各加一滴水。
 * 多个格子>=5 时最靠左的先爆开。
 * 求每次操作后有多少格子有水。
 *
 * 输入格式：
 * 第一行三个整数 c,m,n。
 * 接下来 m 行 (x,w) 表示第 x 格有 w 滴水。
 * 接下来 n 行每行一个整数 p（操作的格子）。
 *
 * 输出格式：
 * n 行，每行一个整数。
 *
 * 数据范围：
 * 1<=c<=10^9, 1<=m<=min(c,3*10^5), 1<=n<=4m, 1<=w<=4。
 *
 * 样例输入：
 * 5 5 2
 * 1 2
 * 2 4
 * 3 4
 * 4 4
 * 5 2
 * 3
 * 1
 *
 * 样例输出：
 * 2
 * 1
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, m, n;
    cin >> c >> m >> n;
    if (c > 3000) return 0;
    vector<int> grid(c + 5, 0);
    for (int i = 1; i <= m; i++) {
        int x, w;
        cin >> x >> w;
        grid[x] = w;
    }
    while (n--) {
        int p;
        cin >> p;
        grid[p]++;
        while (1) {
            bool valid = false;
            for (int i = 1; i <= c; i++) {
                if (grid[i] >= 5) {
                    valid = true;
                    grid[i] = 0;
                    int l = i - 1;
                    while (l > 0 && grid[l] == 0) { l--; }
                    if (l != 0) grid[l]++;
                    int r = i + 1;
                    while (r <= c && grid[r] == 0) { r++; }
                    if (r <= c) grid[r]++;
                    break;
                }
            }
            if (!valid) break;
        }
        int count = 0;
        for (int i = 1; i <= c; i++) {
            if (grid[i] != 0) count++;
        }
        cout << count << '\n';
    }
    return 0;
}
