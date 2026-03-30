/*
 * 造题计划（下）(Author)
 * CCF CSP 第39次认证 真题5
 * 时间限制: 5.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 小C和小F需要在n天时间内造出若干道题目。
 * 小C在上午造题，小F在下午验题。一个题需要先被造完才能验。
 * 小C一天最多出一个题，小F一天最多验一个题。
 * 在第i天，小C造一个题需要精力值ai，小F验一个题需要精力值bi。
 * 总精力值不可以大于m。求最多能造出多少题目。
 *
 * 输入格式：
 * 第一行两个正整数n, m，表示天数和最大总精力值。
 * 第二行n个正整数a1~an，表示每天小C造题的精力。
 * 第三行n个正整数b1~bn，表示每天小F验题的精力。
 *
 * 输出格式：
 * 一行一个正整数，表示最多能造出的题目数量。
 *
 * 样例输入：
 * 5 12
 * 3 5 7 2 9
 * 4 2 8 3 7
 *
 * 样例输出：
 * 2
 *
 * 数据范围（捆绑测试）：
 * 子任务一（20分）：n ≤ 100
 * 子任务二（30分）：n ≤ 3000
 * 子任务三（20分）：n ≤ 10^5
 * 子任务四（30分）：无特殊限制
 * 对于所有数据：1 ≤ n ≤ 5×10^5, 1 ≤ ai, bi ≤ 10^9, 1 ≤ m ≤ 10^18
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;
    cin >> n >> m;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> b(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    long long INF = 1e18;
    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(n + 1, vector<long long>(n + 1, 1e18)));
    dp[0][0][0] = 0;
    // 1. 三层循环，注意 j 和 k 都要从 0 开始
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {     // 优化：第 i 天最多造 i 题
            for (int k = 0; k <= j; k++) { // 优化兼顾条件：验题数 k 不超过造题数 j
                // 动作1：都不做 (昨天也是 j 和 k)
                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k]);

                // 动作2：只造题 (前提是 j>0，昨天是 j-1 和 k)
                if (j > 0) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - 1][k] + a[i]);
                }

                // 动作3：只验题 (前提是 k>0，昨天是 j 和 k-1)
                if (k > 0) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k - 1] + b[i]);
                }

                // 动作4：又造又验 (前提是 j>0 且 k>0，昨天是 j-1 和 k-1)
                if (j > 0 && k > 0) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - 1][k - 1] + a[i] + b[i]);
                }
            }
        }
    }
    int ans = 0;
    for (int j = 0; j <= n; j++) {
        for (int k = 0; k <= j; k++) {
            if (dp[n][j][k] <= m) {
                ans = max(ans, k);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
