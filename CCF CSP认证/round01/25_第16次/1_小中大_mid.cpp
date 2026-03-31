/*
 * 小中大 (mid)
 * CCF CSP 第16次认证 真题1
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> A(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int sum;
    if (n % 2 == 0 && n >= 2) {
        sum = A[n / 2] + A[n / 2 - 1] ;
    } else {
        sum = 2 * A[n / 2];
    }
    if (sum % 2 != 0) {
        cout << fixed << setprecision(1);
    }
    if (A[n - 1] >= A[0]) {
        cout << A[n - 1] << ' ' << double(sum) / 2 << ' ' << A[0] << '\n';
    }else{
        cout << A[0] << ' ' << sum / 2 << ' ' << A[n-1] << '\n';
    }
    return 0;
}
