/*
 * 移动 (move)
 * CCF CSP 第36次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 整个实验场地被划分为 n×n 个方格，从 (1,1) 到 (n,n) 进行编号。
 * 机器人只能在这些方格间移动，不能走出场地范围。
 * 假设机器人当前位于 (x,y)，那么接下来可以向前后左右任意方向移动一格：
 * 向前移动 f：(x,y)→(x,y+1)
 * 向后移动 b：(x,y)→(x,y−1)
 * 向左移动 l：(x,y)→(x−1,y)
 * 向右移动 r：(x,y)→(x+1,y)
 * 特别地，如果移动的目标位置不在场地范围内，则机器人位置保持不变。
 * 试处理 k 个查询：每个查询包含一个起始位置和一个移动指令序列，输出最终位置。
 *
 * 输入格式：
 * 第一行包含两个正整数 n 和 k。
 * 接下来 k 行：每行包含两个正整数 x、y 和一个由 fblr 组成的字符串。
 *
 * 输出格式：
 * 每个查询输出一行：包含两个正整数 x 和 y，表示最终位置。
 *
 * 数据范围：
 * n、k 和每个指令序列的长度均大于 0 且不超过 100。
 *
 * 样例输入：
 * 3 2
 * 1 1 ffrrbbll
 * 3 3 frbl
 *
 * 样例输出：
 * 1 0
 * 2 2
 */

#include <iostream>
using namespace std;
/* int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  int dx[128] = {0};
  int dy[128] = {0};
  dy['f'] = 1;
  dy['b'] = -1;
  dx['l'] = -1;
  dx['r'] = 1;
  while (k--) {
    int x, y;
    cin >> x >> y;
    string s;
    cin >> s;
    for (const char &c : s) {
      int nx = x + dx[c];
      int ny = y + dy[c];
      if (nx <= 0 || nx > n || ny <= 0 || ny > n)
        continue;
      x = nx;
      y = ny;
    }
    cout << x << ' ' << y << '\n';
  }
  return 0;
} */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    while (k--) {
        int x, y;
        string s;
        cin >> x >> y >> s;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'f') {
                if (y + 1 > n)
                    continue;
                y = y + 1;
            }
            if (s[i] == 'b') {
                if (y - 1 <= 0)
                    continue;
                y = y - 1;
            }
            if (s[i] == 'l') {
                if (x - 1 <= 0)
                    continue;
                x = x - 1;
            }
            if (s[i] == 'r') {
                if (x + 1 > n)
                    continue;
                x = x + 1;
            }
        }
        cout << x << ' ' << y << '\n';
    }
}
