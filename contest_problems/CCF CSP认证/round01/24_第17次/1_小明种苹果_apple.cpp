/*
 * 小明种苹果 (apple)
 * CCF CSP 第17次认证 真题1
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    int T = 0;
    int k = 0;
    int P = 0;
    for (int i = 1; i <= N;i++){
        int pri;
        cin >> pri;
        int curr=0;
        for (int j = 1; j <= M;j++){
            int x;
            cin >> x;
            curr -= x;
        }
        pri -= curr;
        T += pri;
        if(curr>P){
            P = curr;
            k = i;
        }
    }
    cout << T << ' ' << k << ' ' << P << '\n';
    return 0; 
}
