/*
 * 跳房子 (hopscotch)
 * CCF CSP 第36次认证 真题4
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 地面上有一字排开的 n 个格子，每个格子上都写着一个数字 ai（满足 ai<i 且
 * an=0）。 小 C 从第一个格子出发，在第 i 个格子上最多能往前跳 ki 格。 跳到第 i
 * 个格子后需要后退 ai 格。 求最少跳多少次才能到达第 n 个格子。
 *
 * 输入格式：
 * 第一行一个正整数 n。
 * 第二行 n 个非负整数 a1,...,an。
 * 第三行 n 个非负整数 k1,...,kn。
 *
 * 输出格式：
 * 输出一行一个整数，不能到达则输出 -1。
 *
 * 数据范围：
 * 1<=n<=10^5, 0<=ai<i, 1<=ki<=10^9。
 *
 * 样例输入1：
 * 10
 * 0 1 1 1 1 3 1 0 3 0
 * 2 4 5 4 1 4 1 3 5 3
 *
 * 样例输出1：
 * 4
 *
 * 样例输入2：
 * 5
 * 0 1 2 3 0
 * 3 4 4 10 15
 *
 * 样例输出2：
 * -1
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) { cin >> a[i]; }
    vector<int> k(n + 1, 0);
    for (int i = 1; i <= n; i++) { cin >> k[i]; }
    vector<int> dist(n + 1, -1);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    bool valid = false;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int x = 1; x <= min(n - u, k[u]); x++) {
            int v = u + x - a[u + x];
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            if (v == n) {
                valid = true;
                break;
            }
            q.push(v);
        }
        if (valid) break;
    }
    cout << dist[n] << '\n';
    return 0;
}
