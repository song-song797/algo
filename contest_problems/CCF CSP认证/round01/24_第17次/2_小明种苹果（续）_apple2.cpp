/*
 * 小明种苹果（续） (apple2)
 * CCF CSP 第17次认证 真题2
 */

#include <bits/stdc++.h>
using namespace std;
bool is_drop[1005];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    int D = 0;
    int T = 0;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        int curr;
        cin >> curr;
        bool valid = false;
        for (int j = 1; j <= num - 1; j++) {
            int m;
            cin >> m;
            if (m <= 0) {
                curr += m;
            } else {
                if (curr != m) {
                    curr = m;
                    valid = true;
                }
            }
        }
        T += curr;
        if (valid) {
            D++;
            is_drop[i] = true;
        }
    }
    int E = 0;
    for (int i = 0; i < N;i++){
        if(is_drop[i]&&is_drop[(i+1)%N]&&is_drop[(i+2)%N]){
            E++;
        }
    }
    cout << T << ' ' << D << ' ' << E << '\n';

    return 0;
}
