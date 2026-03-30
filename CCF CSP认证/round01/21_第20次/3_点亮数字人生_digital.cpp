/*
 * 点亮数字人生 (digital)
 * CCF CSP 第20次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
struct logic_gate {
    string logic;
    vector<pair<char, int>> IO;
};
vector<logic_gate> gates;
int calculate(string logic, const vector<int> &vals) {
    if (logic == "NOT") {
        return !vals[0];
    } else if (logic == "AND") {
        int res = 1;
        for (int i = 0; i < vals.size(); i++) {
            res = res & vals[i];
        }
        return res;
    } else if (logic == "OR") {
        int res = 0;
        for (int i = 0; i < vals.size(); i++) {
            res = res | vals[i];
        }
        return res;
    } else if (logic == "XOR") {
        int res = 0;
        for (int i = 0; i < vals.size(); i++) {
            res = res ^ vals[i];
        }
        return res;
    } else if (logic == "NAND") {
        int res = 1;
        for (int i = 0; i < vals.size(); i++) {
            res = res & vals[i];
        }
        return !res;
    } else if (logic == "NOR") {
        int res = 0;
        for (int i = 0; i < vals.size(); i++) {
            res = res | vals[i];
        }
        return !res;
    }
    return 0;
}
int memo[10005];
bool has_loop = false;
int dfs(int x, const vector<int> &input) {
    if (has_loop)
        return 0;
    if (memo[x] == 0 || memo[x] == 1) {
        return memo[x];
    }
    if (memo[x] == 2) {
        has_loop = true;
        return 0;
    }
    memo[x] = 2;
    vector<int> vals;
    for (int i = 0; i < gates[x].IO.size(); i++) {
        if (gates[x].IO[i].first == 'I') {
            vals.push_back(input[gates[x].IO[i].second]);
        } else {
            vals.push_back(dfs(gates[x].IO[i].second, input));
        }
    }
    int res = 0;
    res = calculate(gates[x].logic, vals);
    return memo[x] = res;
}
void solve() {
    int M, N;
    cin >> M >> N;
    gates.clear();
    gates.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> gates[i].logic;
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            string s;
            cin >> s;
            gates[i].IO.push_back({s[0], stoi(s.substr(1))});
        }
    }
    int S;
    cin >> S;
    vector<vector<int>> inputs(S, vector<int>(M + 1, -1));
    for (int i = 0; i < S; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> inputs[i][j];
        }
    }
    vector<vector<int>> target_gates(S);
    for (int i = 0; i < S; i++) {
        int s;
        cin >> s;
        for (int j = 0; j < s; j++) {
            int x;
            cin >> x;
            target_gates[i].push_back(x);
        }
    }
    vector<vector<int>> ans(S);
    has_loop = false;
    fill(memo, memo + N + 1, -1);
    vector<int> dummy_input(M + 1, 0);
    for (int i = 1; i <= N; i++) {
        if (memo[i] == -1) {
            dfs(i, dummy_input);
        }
        if (has_loop)
            break;
    }
    if (has_loop) {
        cout << "LOOP" << '\n';
        return;
    }
    for (int i = 0; i < S; i++) {
        fill(memo, memo + N + 1, -1);
        for (int x : target_gates[i]) {
            int res = dfs(x, inputs[i]);
            ans[i].push_back(res);
        }
    }
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << (j == ans[i].size() - 1 ? "" : " ");
        }
        cout << '\n';
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    cin >> Q;
    while (Q--) {
        solve();
    }
    return 0;
}
