/*
 * 宝藏 (treasure)
 * CCF CSP 第32次认证 真题4
 * 时间限制: 5.0秒  内存限制: 1024 MiB
 *
 * 题目描述：
 * n 条指令操作双端队列，队列元素为 2×2 矩阵。
 * 指令类型：1.将矩阵插入队头；2.将矩阵插入队尾；3.删除最晚插入的矩阵。
 * m 个事件：1.更新某条指令；2.查询执行[l,r]条指令后队列中矩阵从头到尾的乘积(mod
 * 998244353)。
 *
 * 输入格式：
 * 第一行两个正整数 n,m。
 * 接下来 n 行指令，m 行事件。
 *
 * 输出格式：
 * 每个查询事件输出一行四个整数（2×2矩阵元素）。
 *
 * 数据范围：
 * 1<=n,m<=10^5, 矩阵元素 [0, 998244353)。
 *
 * 样例输入：
 * 3 4
 * 1 2 3 9 3
 * 2 6 9 4 2
 * 2 2 8 2 1
 * 2 2 3
 * 1 2 1 3 1 0 1
 * 1 3 3
 * 2 1 3
 *
 * 样例输出：
 * 30 57 12 34
 * 2 3 9 3
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
const long long MOD = 998244353;
struct Operation {
    int v;
    int matrix[3][3] = {0};
};
struct Matrix {
    long long m[3][3]; // 考虑到乘法和加法可能溢出，用 long long 更安全
};
Matrix simulate(int l, int r, const vector<Operation> &operations, deque<Operation> &dq) {
    dq.clear();
    vector<Operation> history;
    for (int i = l; i <= r; i++) {
        if (operations[i].v == 1) { history.push_back(operations[i]); }
        if (operations[i].v == 2) { history.push_back(operations[i]); }
        if (!history.empty() && operations[i].v == 3) { history.pop_back(); }
    }
    for (int i = 0; i < history.size(); i++) {
        if (history[i].v == 1) { dq.push_front(history[i]); }
        if (history[i].v == 2) { dq.push_back(history[i]); }
    }
    int res[3][3] = {0};
    for (int i = 0; i < 3; i++) { res[i][i] = 1; }
    if (!dq.empty()) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) { res[i][j] = dq.front().matrix[i][j]; }
        }
        dq.pop_front();
    }
    while (!dq.empty()) {
        int current[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) { current[i][j] = dq.front().matrix[i][j]; }
        }
        dq.pop_front();
        int temp[3][3] = {0};
        temp[1][1] = ((res[1][1] * current[1][1]) % MOD + (res[1][2] * current[2][1]) % MOD) % MOD;
        temp[1][2] = ((res[1][1] * current[1][2]) % MOD + (res[1][2] * current[2][2]) % MOD) % MOD;
        temp[2][1] = ((res[2][1] * current[1][1]) % MOD + (res[2][2] * current[2][1]) % MOD) % MOD;
        temp[2][2] = ((res[2][1] * current[1][2]) % MOD + (res[2][2] * current[2][2]) % MOD) % MOD;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) { res[i][j] = temp[i][j]; }
        }
    }
    Matrix matrix;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) { matrix.m[i][j] = res[i][j]; }
    }
    return matrix;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    deque<Operation> dq;

    vector<Operation> operations(n + 1);
    bool valid = false;
    for (int i = 1; i <= n; i++) {
        cin >> operations[i].v;
        if (operations[i].v == 1) {
            valid = false;
            cin >> operations[i].matrix[1][1] >> operations[i].matrix[1][2] >> operations[i].matrix[2][1] >>
                operations[i].matrix[2][2];
        }
        if (operations[i].v == 2) {
            valid = true;
            vector<vector<int>> B(3, vector<int>(3, 0));
            cin >> operations[i].matrix[1][1] >> operations[i].matrix[1][2] >> operations[i].matrix[2][1] >>
                operations[i].matrix[2][2];
        }
    }

    for (int i = 0; i < m; i++) {
        int v;
        cin >> v;
        if (v == 1) {
            int i;
            cin >> i;
            Operation opt;
            cin >> opt.v;
            if (opt.v != 3) { cin >> opt.matrix[1][1] >> opt.matrix[1][2] >> opt.matrix[2][1] >> opt.matrix[2][2]; }
            operations[i] = opt;
        }
        if (v == 2) {
            int l, r;
            cin >> l >> r;
            Matrix matrix = simulate(l, r, operations, dq);
            for (int i = 1; i <= 2; i++) {
                for (int j = 1; j <= 2; j++) { cout << matrix.m[i][j] << ' '; }
            }
            cout << '\n';
        }
    }
    return 0;
}
