/*
 * 模板展开 (template)
 * CCF CSP 第37次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 实现一种模板语言，支持变量和代换。数据类型为字符串（由[a-z0-9]组成）。
 *
 * 表达式由空格分隔的操作数组成：
 * - 以$开头的操作数是变量，剩余部分为变量名
 * - 否则为字符串常量
 * 表达式的值 = 将变量替换为其值后拼接所有操作数
 *
 * 三种语句：
 * 1 <var> <expr>：直接赋值，求表达式的值并赋给变量
 * 2 <var>
 * <expr>：间接赋值，不立即求值，每次用到该变量时重新求值（惰性/动态绑定） 3
 * <var>：输出变量值的长度 mod 1000000007
 *
 * 所有变量初始值为空字符串。保证不存在循环依赖。
 *
 * 输入格式：
 * 第一行整数 n 表示语句数量。
 * 接下来 n 行，每行一个语句。
 *
 * 输出格式：
 * 对每个输出语句，输出一行变量值长度 mod 1000000007。
 *
 * 样例输入1：
 * 6
 * 1 a hello
 * 1 b world
 * 2 c $a $b
 * 3 c
 * 1 a hi
 * 3 c
 *
 * 样例输出1：
 * 10
 * 7
 *
 * 样例输入2：
 * 5
 * 1 var value
 * 3 var
 * 3 val
 * 1 var $var $val $var
 * 3 var
 *
 * 样例输出2：
 * 5
 * 0
 * 10
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1000000007;

unordered_map<string, vector<string>> mp;
unordered_map<string, int> mi;
unordered_map<string, int> type_map;

int getValue(string s) {
    if (s[0] != '$') {
        return s.size() % MOD;
    }
    string var = s.substr(1);
    if (type_map.find(var) == type_map.end()) {
        return 0;
    }
    if (type_map[var] == 1) {
        return mi[var];
    } else {
        int res = 0;
        for (auto str : mp[var]) {
            res = (res + getValue(str)) % MOD;
        }
        return res;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cin.get();

    while (n--) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        int op;
        ss >> op;
        string variable;
        ss >> variable;

        if (op == 1) {
            type_map[variable] = 1;
            int len = 0;
            string s;
            while (ss >> s) {
                len = (len + getValue(s)) % MOD;
            }
            mi[variable] = len;
        } else if (op == 2) {
            type_map[variable] = 2;
            mp[variable].clear();
            string s;
            while (ss >> s) {
                mp[variable].push_back(s);
            }
        } else if (op == 3) {
            string s = "$" + variable;
            cout << getValue(s) << '\n';
        }
    }
    return 0;
}
