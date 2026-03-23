/*
 * C形阵 (square)
 * CCF CSP 第40次认证 真题4
 * 时间限制: 3.0秒  内存限制: 1024 MiB
 *
 * 题目描述：
 * C形阵的数(A,B,C,D,E,F,G)满足如下性质：
 * 1. A,B,C,D,E,F,G都是正整数
 * 2. B/A = B/C  (即 A = C... 不对，原题是 B^A = B^C 的意思？)
 *    原题条件: B^A = B^C (B的A次方等于B的C次方... 不, 原题是分数)
 *    实际条件：
 *    - B/A = B/C  =>  A = C? 不对...
 *    原文: B^A = B^C (上标形式，即 B的A次幂 = B的C次幂)
 *    等等，原文是 "B_A = B_C" 下标形式？
 *    原文PDF格式: B上面A = B上面C，即 B^A = B^C
 *    以及 E_F = G_F，即 E^F = G^F (实际为上标，幂次关系)
 *    结合样例验证：B=2时 A和C可以不等(如A=1,C=4或A=4,C=1)
 *    所以实际条件是: A^B = C^B (A的B次方 = C的B次方... 不对)
 *    根据原文排版: 上标关系 => B^A = B^C, E^F = G^F
 *    但B=2,A=1,C=4时 2^1=2 != 2^4=16 不成立
 *    所以应该是下标/分数: A/B = C/B => A=C? 也不对
 *    根据样例: A=1,B=2,C=4 => 条件是 B^A = B^C 不成立
 *    应该是原文PDF的上下标: 即 A^B = C^B 也不对 1^2=1, 4^2=16
 *    根据4)约束 A*B*C=1*2*4=8, C*D*E=4*1*2=8 可行
 *    所以条件2应该是: B/A = B/C 解读为 (B choose A) 或者比值?
 *    ===> 结合排版，实际条件为:
 *    条件2: A^(1/B) = C^(1/B), 即 A = C... 与样例矛盾
 *    最合理解读(结合样例):
 *      条件2: B^A = B^C  -- 不成立
 *      条件2: A^B = C^B  -- 不成立
 *    实际PDF原文为上标: B的上标是A，右边B的上标是C
 *    这表示 B^A = B^C，但这要求A=C(当B>1时)或B=1
 *    但样例中B=2,A=1,C=4存在，所以应该不是这个意思
 *    推测为分数形式: A/B = B/C => B^2 = A*C
 *    验证: B=2,A=1,C=4 => 4=4 ✓
 *    同理条件3: E/F = F/G => F^2 = E*G
 *    验证: E=2,F=2,G=2 => 4=4 ✓
 *    E=1,F=2,G=4 => 4=4 ✓
 *
 *   ★ 最终条件:
 *   2. B^2 = A * C  (等比关系)
 *   3. F^2 = E * G  (等比关系)
 *   4. A*B*C = C*D*E = E*F*G
 *
 * C形阵的大小为B，价值为D。
 *
 * 若{A,B,C,D,E,F,G}中恰有6个互不相同的元素(|集合|=6)，
 * 则称该C形阵为完美的C形阵。
 *
 * 给定op和n:
 *   op=0: 求所有大小不超过n的C形阵价值总和
 *   op=1: 求所有大小不超过n的完美的C形阵价值总和
 * 答案对998244353取模。
 *
 * 输入格式：
 * 一行两个整数op,n。
 *
 * 输出格式：
 * 一个正整数，表示价值总和。
 *
 * 样例1输入: 0 2    样例1输出: 25
 * 样例2输入: 1 4    样例2输出: 64
 *
 * 数据范围：
 * 子任务一(30分): n<=10
 * 子任务二(20分): op=0, n<=10^5
 * 子任务三(30分): n<=10^5
 * 子任务四(10分): op=0
 * 子任务五(10分): 无特殊限制
 * 全部数据: op∈{0,1}, 1<=n<=10^7
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int op, n;
    cin >> op >> n;
    if(op==0){
        int res = 0;
        for (int B = 1; B <= n;B++){
            for (int C = 1; C <= B * B;C++){
                if((B*B)%C!=0)
                      continue;
                for (int E = 1; E <= B * B;E++){
                  if((B*B*B)%(C*E)!=0)
                      continue;
                  if((B*B)%E!=0)
                      continue;
                  res = (res+(B * B * B) / (C * E))%998244353;
              }
            }
        }
        cout << res << '\n';
    }else{
      int res = 0;
        for (int B = 1; B <= n;B++){
            for (int C = 1; C <= B * B;C++){
                if((B*B)%C!=0)
                      continue;
                for (int E = 1; E <= B * B;E++){
                  if((B*B*B)%(C*E)!=0)
                      continue;
                  if((B*B)%E!=0)
                      continue;
                  int A = (B * B) / C;
                  int D = (B * B * B) / (C * E);
                  int G = (B * B) / E;
                  set<int> st = {A, B, C, D, E, G};
                  if(st.size()==6)
                      res = (res + D) % 998244353;
              }
            }
        }
        cout << res << '\n';
    }
    return 0; 
}
