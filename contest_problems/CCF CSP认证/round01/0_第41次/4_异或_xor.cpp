/*
 * 异或 (xor)
 * CCF CSP 第41次认证 真题4
 * 时间限制: 6.0秒  内存限制: 1024 MiB
 *
 * 题目描述：
 * 定义k进制下的异或运算⊕k：对于非负整数a, b，a ⊕k b为k进制下的不进位加法。
 * 即若a = Σ(ai · k^i), b = Σ(bi · k^i)，其中ai, bi是小于k的非负整数，
 * 则a ⊕k b = Σ(((ai + bi) mod k) · k^i)。
 *
 * 定义函数f：
 * f(0) = 0
 * f(n) = n ⊕k f(n - 1) (n > 0)
 *
 * 给定一个非负整数序列a1, a2, ···, an和全局给定的奇数k，进行m次操作：
 * 操作一：给出三个参数l, r, v，表示将下标在区间[l, r]内的ai修改为ai ⊕k v。
 * 操作二：给出两个参数l, r，表示查询f(al) ⊕k f(al+1) ⊕k ··· ⊕k f(ar)。
 *
 * 输入格式：
 * 第一行给出三个正整数n, m, k。
 * 接下来一行给出n个非负整数，表示序列a。
 * 接下来m行每行给出三个或者四个非负整数，表示m次操作。
 * 每行第一个数字为操作的类型t：
 *   如果t为1，则该操作为操作一，接下来给出三个非负整数l, r, v作为该操作的参数。
 *   如果t为2，则该操作为操作二，接下来给出两个正整数l, r作为该操作的参数。
 *
 * 输出格式：
 * 对于每个操作二，输出单独的一行，包含一个非负整数，为该操作的答案。
 *
 * 样例输入：
 * 5 4 11
 * 13 17 14 19 15
 * 1 1 3 9
 * 2 1 2
 * 1 3 5 6
 * 2 4 5
 *
 * 样例输出：
 * 76
 * 50
 *
 * 样例解释：
 * 第一个操作结束后，序列a为：[11, 15, 12, 19, 15]。
 * 第二个操作的答案为f(a1) ⊕11 f(a2) = 11 ⊕11 65 = 76。
 * 第三个操作结束后，序列a为：[17, 21, 18, 14, 21]。
 * 第四个操作的答案为f(a4) ⊕11 f(a5) = 50 ⊕11 0 = 50。
 *
 * 数据范围：
 * 1 ≤ n ≤ 5 × 10^5, 1 ≤ m ≤ 10^4, 11 ≤ k ≤ 10^9且k为奇数
 * 1 ≤ l ≤ r ≤ n，对于任意时刻保证ai非负
 * 所有操作一中保证参数v非负，记所有时刻序列中的元素ai和所有操作一中的参数v的最大值为R
 * R ≤ 10^12
 *
 * 子任务：
 * 子任务一（20分）：n, m ≤ 10^3且R ≤ 10^6
 * 子任务二（30分）：n, m ≤ 10^3
 * 子任务三（20分）：ai和操作一的参数v均是k的倍数
 * 子任务四（30分）：无特殊限制
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
signed caculate(int a, int b, int k) {
    int base = 1;
    int sum = 0;
    while (a > 0 || b > 0) {
        int temp_a = a % k;
        int temp_b = b % k;
        sum += ((temp_a + temp_b) % k) * base;
        a = a / k;
        b = b / k;
        base = base * k;
    }
    return sum;
}
signed mul(int v, int m, int k) {
    int base = k;
    int sum = 0;
    while (v > 0) {
        int temp = v % k;
        sum += (temp * m) % k * base;
        v = v / k;
        base = base * k;
    }
    return sum;
}
signed get_f(int x, int k) {
    if (x == 0)
        return 0;
    int low = ((x % k) * (x % k + 1) / 2) % k;
    int high = mul(x / k, (x % k) + 1, k);
    return low + high;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            for (int i = l; i <= r; i++) {
                a[i] = caculate(a[i], v, k);
            }
        }
        if (t == 2) {
            int l, r;
            cin >> l >> r;
            int res = 0;
            for (int i = l; i <= r; i++) {
                res = caculate(res, get_f(a[i], k), k);
            }
            cout << res << '\n';
        }
    }
    return 0;
}