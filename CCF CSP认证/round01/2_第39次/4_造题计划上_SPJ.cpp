/*
 * 造题计划（上）(SPJ)
 * CCF CSP 第39次认证 真题4
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 给定一棵n个结点的树，编号为i的点有权值ai，a1~an构成0到n-1的排列。
 * 依次检验m条限制，每条限制给定两个结点x和y，
 * 求出从x到y的简单路径上所有点的权值构成集合的mex值。
 * mex(S)表示最小的没有在S中出现过的自然数。
 *
 * 输入格式：
 * 第一行两个正整数n, m。
 * 第二行n个正整数a1~an，表示每个结点的权值。
 * 接下来n-1行每行两个整数，表示树上的一条边。
 * 接下来m行每行两个整数xi, yi，表示一条限制。
 *
 * 输出格式：
 * m行，每行一个正整数，表示对应限制的mex值。
 *
 * 样例输入：
 * 7 3
 * 1 0 2 6 3 4 5
 * 1 2
 * 2 5
 * 2 6
 * 1 3
 * 3 7
 * 1 4
 * 5 3
 * 6 3
 * 7 4
 *
 * 样例输出：
 * 4
 * 3
 * 0
 *
 * 数据范围（捆绑测试）：
 * 子任务一（20分）：n, m ≤ 1000
 * 子任务二（20分）：保证给定的树是一条链
 * 子任务三（30分）：n, m ≤ 5×10^4
 * 子任务四（30分）：无特殊限制
 * 对于所有数据：1 ≤ n, m ≤ 2×10^5
 */

#include <bits/stdc++.h>
using namespace std;
bool visited[1005]={false};
int dfs(int u,int v,const vector<vector<int>>& adj,const vector<int>& a){
  visited[a[u]] = true;
  if(u==v){
      for (int i = 0; i < 1005;i++){
         if(!visited[i]){
             visited[a[u]] = false;
             return i;
         }
      }
  }

  for(auto ad:adj[u]){
    if(visited[a[ad]])
        continue;
    int res=dfs(ad, v, adj,a);
    if(res!=-1){
        visited[a[u]] = false;
        return res;
    }
        
  }
  visited[a[u]] = false;
  return -1;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1, 0);
  for (int i = 1; i <= n;i++){
      cin >> a[i];
  }
  vector<vector<int>> adj(n + 1);
  for(int i=0;i<n-1;i++){
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
  }
  for (int i = 0; i < m;i++){
      int x, y;
      cin >> x >> y;
      int mex = dfs(x, y, adj, a);
      cout << mex << '\n';
  }
      return 0; 
}
