/*
 * 机器人复健指南 (robot)
 * CCF CSP 第38次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 实验场地被划分为 n×n 个方格，从 (1,1) 到 (n,n) 编号。
 * 机器人当前位于 (x,y)，可以向周围八个方向跳跃移动（目标方格须在场地范围内）。
 * 若机器人只能跳动不超过 k 步，场地内有多少方格（包括起始位置）可以抵达？
 *
 * 输入格式：
 * 第一行包含空格分隔的两个正整数 n 和 k，分别表示场地大小和跳动步数。
 * 第二行包含空格分隔的两个正整数 x 和 y，表示机器人的起始位置。
 *
 * 输出格式：
 * 输出一个整数，表示 k 步内可以抵达的方格总数。
 *
 * 数据范围：
 * 80% 的测试数据满足：k≤3
 * 全部的测试数据满足：n、k 均大于 0 且不超过 100
 *
 * 样例输入1：
 * 4 1
 * 1 1
 *
 * 样例输出1：
 * 3
 *
 * 样例输入2：
 * 4 2
 * 1 1
 *
 * 样例输出2：
 * 8
 */

#include <cstring>
#include <iostream>
#include <queue>
const int dx[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
const int dy[8] = {2, 2, 1, -1, -2, -2, -1, 1};
bool visited[105][105];
using namespace std;
/* int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k, x, y;
  cin >> n >> k;
  cin >> x >> y;
  int dist[105][105];
  memset(dist, -1, sizeof(dist));
  dist[x][y] = 0;
  const int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
  const int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};
  queue<pair<int, int>> q;
  q.push({x, y});
  int count = 1;
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    if (dist[x][y] == k)
      break;
    for (int i = 0; i < 8; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx <= 0 || nx > n || ny <= 0 || ny > n)
        continue;
      if (dist[nx][ny] != -1)
        continue;
      count++;
      dist[nx][ny] = dist[x][y] + 1;
      q.push({nx, ny});
    }
  }
  cout << count << '\n';
  return 0;
}
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    int x, y;
    cin >> x >> y;
    queue<pair<int, int>> q;
    q.push({x, y});

    int count = 1;
    visited[x][y] = true;
    while (!q.empty()&&k>0) {
        int sz = q.size();
        while (sz--) {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx <= 0 || nx > n || ny <= 0 || ny > n)
                    continue;
                if (visited[nx][ny])
                    continue;
                visited[nx][ny] = true;
                count++;
                q.push({nx, ny});
            }
        }
        k--;
    }
    cout << count << '\n';
}