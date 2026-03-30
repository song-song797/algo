/*
 * 梯度求解 (gradient)
 * CCF CSP 第31次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 给定函数 f(x1,...,xn) 的逆波兰式表示，仅由常数、自变量和加减乘组成。
 * 求 f 对 xi 在给定点处的偏导数，结果对 10^9+7 取模。
 *
 * 输入格式：
 * 第一行两个正整数 n、m。
 * 第二行逆波兰式。
 * 接下来 m 行，每行 n+1 个整数。
 *
 * 输出格式：
 * m 行，每行一个整数。
 *
 * 数据范围：
 * n<=100, m<=100, 常数和坐标在 [-10^5, 10^5] 之间。
 *
 * 样例输入：
 * 2 2
 * x1 x1 x1 * x2 + *
 * 1 2 3
 * 2 3 4
 *
 * 样例输出：
 * 15
 * 3
 */

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    cin >> ws;
    vector<string> f;
    string line;
    getline(cin, line);
    stringstream ss(line);
    string str;
    while(ss>>str){
        f.push_back(str);
    } 
    return 0;
}
