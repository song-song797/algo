/*
 * 缓存模拟 (cache)
 * CCF CSP 第36次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 模拟 n-路组相联缓存的工作过程。
 * 缓存采用 LRU（最近最少使用）替换策略。
 * 给定一系列内存读写指令，输出处理器对内存的实际读写操作序列。
 *
 * 输入格式：
 * 第一行三个整数 n,N,q，分别表示组相联路数、组数和指令数量。
 * 接下来 q 行，每行两个整数 o 和 a（o=0读/1写，a为内存块编号）。
 *
 * 输出格式：
 * 若干行，每行两个整数 o' 和 a'，表示实际对内存的读写操作。
 *
 * 数据范围：
 * 1<=n,N,n*N<=65536，n,N 为 2 的幂次；1<=q<=10^5，0<=a<2^30。
 *
 * 样例输入：
 * 4 8 8
 * 0 0
 * 0 1
 * 1 2
 * 0 1
 * 1 0
 * 0 32
 * 1 33
 * 0 34
 *
 * 样例输出：
 * 0 0s
 * 0 1
 * 0 2
 * 0 32
 * 1 2
 * 0 33
 * 0 34
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, N, q;
    cin >> n >> N >> q;
    vector<list<int>> vl(N);
    vector<unordered_map<int, list<int>::iterator>> ids(N);
    unordered_map<int, bool> is_changed;
    while (q--) {
        int o, a;
        cin >> o >> a;
        int group = a / n % N;
        if (o == 0) {
            if (!ids[group].count(a)) {
                if (ids[group].size() < n) {
                    vl[group].push_front(a);
                    ids[group][a] = vl[group].begin();
                    is_changed[a] = false;
                    cout << 0 << ' ' << a << '\n';
                } else {
                    if (is_changed[vl[group].back()]) {
                        cout << 1 << ' ' << vl[group].back() << '\n';
                    }
                    ids[group].erase(vl[group].back());
                    vl[group].pop_back();
                    vl[group].push_front(a);
                    ids[group][a] = vl[group].begin();
                    is_changed[a] = false;
                    cout << 0 << ' ' << a << '\n';
                }
            } else {
                vl[group].splice(vl[group].begin(), vl[group], ids[group][a]);
                ids[group][a] = vl[group].begin();
            }
        }
        if (o == 1) {
            if (!ids[group].count(a)) {
                if (ids[group].size() < n) {
                    vl[group].push_front(a);
                    ids[group][a] = vl[group].begin();
                    is_changed[a] = false;
                    cout << 0 << ' ' << a << '\n';
                } else {
                    if (is_changed[vl[group].back()]) {
                        cout << 1 << ' ' << vl[group].back() << '\n';
                    }
                    ids[group].erase(vl[group].back());
                    vl[group].pop_back();
                    vl[group].push_front(a);
                    ids[group][a] = vl[group].begin();
                    is_changed[a] = false;
                    cout << 0 << ' ' << a << '\n';
                }
            } else {
                vl[group].splice(vl[group].begin(), vl[group], ids[group][a]);
                ids[group][a] = vl[group].begin();
            }
            is_changed[a] = true;
        }
    }
    return 0;
}
