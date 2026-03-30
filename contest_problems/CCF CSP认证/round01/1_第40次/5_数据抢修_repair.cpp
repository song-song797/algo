/*
 * 数据抢修 (repair)
 * CCF CSP 第40次认证 真题5
 * 时间限制: 3.0秒  内存限制: 1024 MiB
 *
 * 题目描述：
 * CrazyFry有n个数据包，每个数据包初始包含一些元素(可能为空)，
 * 每个元素有一个权值。数据包编号1~n，默认为激活状态。
 * 同一个数据包允许出现权值相同的元素(可重集)。
 *
 * 小C设定了一个稳定值W。一个数据包是稳定的当且仅当
 * 其中任意两个元素的权值x,y均满足 x XOR y >= W。
 * 显然，只有一个元素的数据包一定是稳定的。
 *
 * 将一个数据包划分为若干子数据包，使得每个元素恰好出现在一个子数据包中，
 * 且每个子数据包都是稳定的，称这样的划分方式是稳定的。
 * 一个稳定的划分方式所划分出的子数据包数量的最小值为该数据包的维修代价。
 * CrazyFry的维修代价为目前所有处于激活状态的数据包的维修代价的总和。
 *
 * 操作：
 * 1 u x: 在编号为u的数据包中添加一个权值为x的元素(u处于激活状态)。
 * 2 u v: 将v的数据包合并到u中(u!=v，均激活)，之后v离线，不再出现。
 * 3:     查询当前CrazyFry的维修代价。
 *
 * 输入格式：
 * 第一行正整数n和正整数W。
 * 接下来n行，第i行首先一个非负整数mi(初始元素个数)，然后mi个权值。
 * 下一行正整数q(操作个数)。
 * 接下来q行，每行先读入op，然后根据op类型读入对应参数。
 *
 * 输出格式：
 * 对于每个op=3，输出一行一个整数表示维修代价。
 *
 * 样例1输入：
 * 3 16
 * 1 21
 * 1 16
 * 1 29
 * 5
 * 3
 * 2 2 1
 * 3
 * 2 3 2
 * 3
 *
 * 样例1输出：
 * 3
 * 3
 * 3
 *
 * 数据范围：
 * 全部数据: 1<=n,q,sum(mi)<=5*10^5, 权值∈[0,10^9], W>0
 * 子任务一(20分): n,q,sum(mi)<=10, 权值∈[0,10^3]
 * 子任务二(15分): n,q,sum(mi)<=100, 权值∈[0,10^3]
 * 子任务三(15分): n,q,sum(mi)<=10^3, 权值∈[0,10^6]
 * 子任务四(20分): n,q,sum(mi)<=10^5, 权值∈[0,10^6]
 * 子任务五(30分): 无特殊限制
 */

#include <bits/stdc++.h>
using namespace std;
int min_ans = 1e9;
void dfs(int u, int max_color, int m, vector<vector<int>>& color,int W,vector<int>& val) {
    if (max_color >= min_ans) return;
    if(u==m) {
      if (max_color < min_ans) {
            min_ans = max_color; // 刷新历史最佳记录！
        }
      return;
    }

    for (int c = 1; c <= max_color + 1;c++){
        bool valid = false;
       for(auto co:color[c]){
        if((val[u]^val[co])<W){
            valid = true;
            break;
        }
      }
      if(!valid){
          color[c].push_back(u);
          dfs(u + 1, max(max_color, c), m, color, W, val);
          color[c].pop_back();
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    cin >> n >> W;
    vector<vector<int>> package(n);
    vector<vector<int>> color(15);
    for (int i = 0; i < n;i++){
        int m;
        cin >> m;
        for (int j = 0; j < m;j++){
            int weight;
            cin >> weight;
            package[i].push_back(weight);
        }
    }
    vector<bool> state(n, true);
    int q;
    cin >> q;
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int u, x;
            cin >> u >> x;
            u--;
            package[u].push_back(x);;
        }
        if(op==2){
            int u, v;
            cin >> u >> v;
            u--, v--;
            for (int i = 0; i < package[v].size();i++){
                package[u].push_back(package[v][i]);
            }
            state[v] = false;
        }
        if(op==3){
            int res = 0;
            for (int i = 0; i < n; i++) {
              min_ans = 1e9;
              if (state[i] == false) {
                  continue;
               }
               for(int j = 1; j < 15; j++) color[j].clear();
               dfs(0, 0, package[i].size(), color, W, package[i]);
               res += min_ans;
            }
            cout << res << '\n';
        }
    }
    return 0; 
}
