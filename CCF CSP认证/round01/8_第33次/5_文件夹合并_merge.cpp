/*
 * 文件夹合并 (merge)
 * CCF CSP 第33次认证 真题5
 * 时间限制: 2.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * n 个文件夹构成树形结构，每个文件夹存储 di 字节数据。
 * 支持两种操作：
 * 1. 合并：将文件夹 xj 的所有子文件夹合并到 xj 中，删除子文件夹。
 * 2. 访问：从根文件夹开始，查询到达文件夹 zj 最少经过多少个文件夹。
 *
 * 输入格式：
 * 第一行两个整数 n,m。
 * 第二行 n-1 个整数（父文件夹编号）。
 * 第三行 n 个整数（数据存储量）。
 * 接下来 m 行操作。
 *
 * 输出格式：
 * m 行，合并操作输出子文件夹数和数据量，访问操作输出经过的文件夹数。
 *
 * 数据范围：
 * 1<=n<=5*10^5, 1<=m<=3*n, 0<=di<=10^5。
 *
 * 样例输入：
 * 4 6
 * 1 1 3
 * 100 0 200 300
 * 2 1
 * 2 4
 * 1 1
 * 2 4
 * 1 1
 * 1 1
 *
 * 样例输出：
 * 1
 * 3
 * 1 300
 * 2
 * 0 600
 * 0 600
 */

#include <bits/stdc++.h>
using namespace std;
struct Directory {
    int byte;
    vector<int> son;
};

int dfs(vector<Directory> &directorys, int idx, int z, int current) {
    if (idx == z) return current;
    int res = 0;
    for (auto sn : directorys[idx].son) {
        res = dfs(directorys, sn, z, current + 1);
        if (res != 0) return res;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Directory> directorys(n + 1);
    vector<int> f(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        cin >> f[i];
        directorys[f[i]].son.push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        int d;
        cin >> d;
        directorys[i].byte = d;
    }

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            vector<int> new_son;
            for (int sn : directorys[x].son) {
                directorys[x].byte += directorys[sn].byte;
                for (int s : directorys[sn].son) new_son.push_back(s);
            }
            directorys[x].son = new_son;
            cout << directorys[x].son.size() << ' ' << directorys[x].byte << '\n';
        }
        if (op == 2) {
            int z;
            cin >> z;
            int res = dfs(directorys, 1, z, 1);
            cout << res << '\n';
        }
    }
    return 0;
}
