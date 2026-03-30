/*
 * 词频统计 (wordfreq)
 * CCF CSP 第33次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * n 篇文章中共出现 m 个不同单词（编号 1 到 m），
 * 对每个单词统计：出现在多少篇文章中？总共出现几次？
 *
 * 输入格式：
 * 第一行两个正整数 n 和 m。
 * 接下来 n 行，每行先输入长度 li，再输入 li 个整数。
 *
 * 输出格式：
 * m 行，每行两个整数 xi 和 yi。
 *
 * 数据范围：
 * 0<n,m<=100，1<=li<=100。
 *
 * 样例输入：
 * 4 3
 * 5 1 2 3 2 1
 * 1 1
 * 3 2 2 2
 * 2 3 2
 *
 * 样例输出：
 * 2 3
 * 3 6
 * 2 2
 */

#include <iostream>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int arr[105] = {0};
  int last_seen[105];
  fill(last_seen,last_seen+105,-1);
  int nums[105]={0};
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    int len;
    cin >> len;
    for (int j = 0; j < len; j++) {
      int current;
      cin >> current;
      arr[current]++;
      if(last_seen[current]!=i){
        nums[current]++;
      }
      last_seen[current]=i;
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << nums[i] << ' ' << arr[i] << '\n';
  }
  return 0;
}
