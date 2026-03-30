/*
 * 坐标变换（其二） (coord2)
 * CCF CSP 第31次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 两种操作：拉伸 k 倍、旋转 θ 弧度。
 * 设定 n 个操作序列后，处理 m 个查询：
 * 坐标 (x,y) 经过操作 ti,...,tj 后的新坐标。
 *
 * 输入格式：
 * 第一行两个正整数 n 和 m。
 * 接下来 n 行操作，m 行查询。
 *
 * 输出格式：
 * m 行，每行两个实数。
 *
 * 数据范围：
 * n,m<=10^5，坐标绝对值不超过 10^6，拉伸系数 k∈[0.5,2]。
 * 绝对误差不大于 0.1。
 *
 * 样例输入：
 * 10 5
 * 2 0.59
 * 2 4.956
 * 1 0.997
 * 1 1.364
 * 1 1.242
 * 1 0.82
 * 2 2.824
 * 1 0.716
 * 2 0.178
 * 2 4.094
 * 1 6 -953188 -946637
 * 1 9 969538 848081
 * 4 7 -114758 522223
 * 1 9 -535079 601597
 * 8 8 159430 -511187
 *
 * 样例输出：
 * -1858706.758 -83259.993
 * -1261428.46 201113.678
 * -75099.123 -738950.159
 * -119179.897 -789457.532
 * 114151.88 -366009.892
 */

#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(3);
  int n, m;
  cin >> n >> m;
  vector<pair<int, double>> change(n + 1);
  vector<double> sum_k(n + 1, 1);
  vector<double> sum_theta(n + 1, 0);
  for (int i = 1; i <= n; i++) {
	  cin >> change[i].first >> change[i].second;
	  if (change[i].first == 1) {
		  sum_k[i] = sum_k[i - 1] * change[i].second;
		  sum_theta[i] = sum_theta[i - 1];
	  }
	  else {
		  sum_k[i] = sum_k[i - 1];
		  sum_theta[i] = sum_theta[i-1]+change[i].second;
	  }
  }
  for (int k = 1; k <= m; k++) {
	  int i, j;
	  double x, y;
	  cin >> i >> j >> x >> y;
	  x = x * (sum_k[j]/sum_k[i - 1]);
	  y = y * (sum_k[j]/sum_k[i - 1]);
	  double rem_x = x;
	  double rem_y = y;
	  x = rem_x * cos(sum_theta[j] - sum_theta[i - 1]) - rem_y * sin(sum_theta[j] - sum_theta[i - 1]);
	  y = rem_x * sin(sum_theta[j] - sum_theta[i - 1]) + rem_y * cos(sum_theta[j] - sum_theta[i - 1]);
	  cout << x << ' ' << y << '\n';
  }
  return 0;
}
