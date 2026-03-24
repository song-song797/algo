/*
 * 防疫大数据 (epidemic)
 * CCF CSP 第27次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
struct Record {
  int d0;
  int d1;
  int r;
};
bool is_risk(int p, int D,
             const unordered_map<int, vector<int>> &risk_announcements) {
  if (risk_announcements.find(p) == risk_announcements.end())
    return false;
  for (auto ap : risk_announcements.at(p)) {
    if (ap > D - 7 && ap <= D) {
      return true;
    }
  }
  return false;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  unordered_map<int, vector<Record>> users;
  unordered_map<int, vector<int>> risk_announcements;
  for (int i = 0; i < n; i++) {
    int r, m;
    cin >> r >> m;

    for (int j = 0; j < r; j++) {
      int p;
      cin >> p;
      risk_announcements[p].push_back(i);
    }

    for (int k = 0; k < m; k++) {
      int d, u, r;
      cin >> d >> u >> r;
      Record record;
      record.d0 = i;
      record.d1 = d;
      record.r = r;
      users[u].push_back(record);
    }

    vector<int> res;
    for (auto &user : users) {
      int valid = -1;
      for (auto record : user.second) {
        if (record.d0 <= i - 7 || record.d0 > i)
          continue;
        if (record.d1 <= i - 7 || record.d1 > i)
          continue;
        valid = 0;
        for (int l = record.d1; l <= i; l++) {
          if (!is_risk(record.r, l, risk_announcements)) {
            valid = 1;
            break;
          }
        }
        if (valid == 0)
          break;
      }
      if (valid == 0)
        res.push_back(user.first);
    }

    sort(res.begin(), res.end());
    cout << i << ' ';
    for (auto r : res) {
      cout << r << ' ';
    }
    cout << '\n';
  }
  return 0;
}
