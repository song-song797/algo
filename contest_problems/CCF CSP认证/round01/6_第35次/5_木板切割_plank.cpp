/*
 * 木板切割 (plank)
 * CCF CSP 第35次认证 真题5
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 一块长度为 n 的木板被平均分成 n 段，第 i 段被染为颜色 ci。
 * 进行 k 次切割操作，每次从 xi 号木板中切下编号在 [li,ri] 之间的段，
 * 作为新的木板。
 * 每次切割后输出切下的木板包含多少种不同颜色和多少个颜色段。
 *
 * 输入格式：
 * 第一行三个正整数 n,m,k。
 * 第二行 n 个正整数颜色。
 * 接下来 k 行每行三个整数 xi,li,ri。
 *
 * 输出格式：
 * k 行，每行两个整数：不同颜色数和颜色段数。
 *
 * 数据范围：
 * 1<=n,m,k<=10^5, 1<=ci<=m, 1<=li<=ri<=n, 1<=xi<=i。
 *
 * 样例输入：
 * 6 3 5
 * 1 2 2 3 1 2
 * 1 3 4
 * 1 5 5
 * 1 4 5
 * 1 1 6
 * 2 4 4
 *
 * 样例输出：
 * 2 2
 * 1 1
 * 0 0
 * 2 2
 * 1 1
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> c(n + 1, 0);
    for (int i = 1; i <= n; i++) { cin >> c[i]; }
    vector<vector<int>> board(k + 2);
    for (int i = 1; i <= n; i++) { board[1].push_back(i); }
    int p = k;
    while (k--) {
        int x, l, r;
        cin >> x >> l >> r;
        int current = p - k + 1;
        vector<int> remain_board;
        for (auto it = board[x].begin(); it < board[x].end(); it++) {
            if (*it >= l && *it <= r) {
                board[current].push_back(*it);
            } else {
                remain_board.push_back(*it);
            }
        }
        board[x] = remain_board;
        unordered_set<int> color;
        int count = 0;
        if (!board[current].empty()) count = 1;
        for (int i = 0; i < board[current].size(); i++) {
            color.insert(c[board[current][i]]);
            if (i >= 1 && c[board[current][i]] != c[board[current][i - 1]]) { count++; }
        }
        cout << color.size() << ' ' << count << '\n';
    }
    return 0;
}
