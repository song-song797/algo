/*
 * 梦魔 (nightmare)
 * CCF CSP 第36次认证 真题5
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 有 n 只梦魔站成一列，第 i 只梦魔有防御力 ai。
 * 如果小 C 的攻击力不严格小于 ai，他就可以击杀这只梦魔，攻击力上升 bi。
 * 小 C 会被传送到两只相邻的梦魔之间，每次可以选择攻击左边或右边最近的梦魔。
 * 对于每个降落位置，求能击杀所有梦魔的最小初始攻击力。
 * 梦魔的信息可能发生变化，每次变化后需要重新计算。
 *
 * 输入格式：
 * 第一行一个正整数 n。
 * 第二行 n 个正整数 a1,...,an（防御力）。
 * 第三行 n 个正整数 b1,...,bn（击杀收益）。
 * 第四行一个正整数 q（变动次数）。
 * 接下来 q 次变动的描述。
 *
 * 输出格式：
 * 对每次变动输出一行一个整数，表示 p1⊕p2⊕...⊕p(n-1)。
 *
 * 数据范围：
 * 1<=n<=2*10^6, 0<=q<=20, 1<=ai,bi<=10^9。
 *
 * 样例输入：
 * 6
 * 4 9 3 1 7 7
 * 4 2 1 3 1 4
 * 2
 * 2
 * 3 8 1
 * 5 4 3
 * 0
 *
 * 样例输出：
 * 9
 * 1
 */

#include <bits/stdc++.h>
using namespace std;

// 修复 1：将 attack 以及数组类型改为 long long，防止爆 int
bool check(int i, long long attack, int n, const vector<long long> &a, const vector<long long> &b) {
    int L = i;
    int R = i + 1;

    while (L >= 1 || R <= n) {
        // 修复 2：安全的短路判定。必须先判定 L 存在 (L >= 1)，再去读取 a[L]
        // 如果 L 存在，并且（右边空了 或者 左边防御力更弱/相等），就向左打
        if (L >= 1 && (R > n || a[L] <= a[R])) {
            if (attack < a[L]) return false;
            attack += b[L];
            L--;
        }
        // 否则（隐含条件是 R <= n，且必须打右边），向右打
        else {
            if (attack < a[R]) return false;
            attack += b[R];
            R++;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> original_a(n + 1, 0);
    for (int i = 1; i <= n; i++) { cin >> original_a[i]; }

    vector<long long> original_b(n + 1, 0);
    for (int i = 1; i <= n; i++) { cin >> original_b[i]; }

    int q;
    cin >> q;

    // 使用 a 和 b 作为当前战斗用的数组
    vector<long long> a = original_a;
    vector<long long> b = original_b;

    while (q--) {
        int k;
        cin >> k;

        // 用于记录本次修改的历史，方便稍后回退
        struct Change {
            int idx;
            long long old_a, old_b;
        };
        vector<Change> history;

        for (int j = 0; j < k; j++) {
            int idx;
            long long ai, bi;
            cin >> idx >> ai >> bi;
            // 存下旧值
            history.push_back({idx, a[idx], b[idx]});
            // 更新新值
            a[idx] = ai;
            b[idx] = bi;
        }

        long long xor_sum = 0;
        // 枚举所有的降落位置：1 到 n-1
        for (int i = 1; i <= n - 1; i++) {
            // 二分答案查找最小初始攻击力
            long long l = 1, r = 1e9 + 5;
            long long ans = r;

            while (l <= r) {
                long long mid = l + (r - l) / 2;
                if (check(i, mid, n, a, b)) {
                    ans = mid;   // 记录可行解
                    r = mid - 1; // 尝试更小的攻击力
                } else {
                    l = mid + 1; // 攻击力不够，必须增大
                }
            }

            // 计算异或和
            if (i == 1) xor_sum = ans;
            else xor_sum ^= ans;
        }

        cout << xor_sum << '\n';

        // 修复 3：每次变动是独立的！计算完毕后必须回退对初始局面的修改
        for (auto h : history) {
            a[h.idx] = h.old_a;
            b[h.idx] = h.old_b;
        }
    }
    return 0;
}