/*
 * LDAP (ldap)
 * CCF CSP 第29次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
enum OpType {
  Assertation = ':',
  ANTI_Assertation = '~',
  Logic_And = '&',
  Logic_Or = '|'
};
struct User {
  int DN;
  int num;
  unordered_map<int, int> attribute;
};
vector<int> parse(const string &s, int &idx, const vector<User> &users) {
  if (idx == s.size() || s[idx] == ')')
    return {};
  if (s[idx] == Logic_And || s[idx] == Logic_Or) {
    int t = idx;
    idx += 2;
    vector<int> left_res;
    left_res = parse(s, idx, users);
    idx += 2;
    vector<int> right_res;
    right_res = parse(s, idx, users);
    if (s[t] == Logic_And) {
      vector<int> result;
      set_intersection(left_res.begin(), left_res.end(), right_res.begin(),
                       right_res.end(), back_inserter(result));
      idx++;
      return result;
    } else {
      vector<int> result;
      set_union(left_res.begin(), left_res.end(), right_res.begin(),
                right_res.end(), back_inserter(result));
      idx++;
      return result;
    }
  } else {
    string str1 = "";
    while (isdigit(s[idx])) {
      str1 += s[idx];
      idx++;
    }
    int left = stoi(str1);
    char op = s[idx];
    idx++;
    string str2 = "";
    while (isdigit(s[idx])) {
      str2 += s[idx];
      idx++;
    }
    int right = stoi(str2);
    if (op == Assertation) {
      vector<int> res;
      for (int i = 0; i < users.size(); i++) {
        if (users[i].attribute.count(left) &&
            users[i].attribute.at(left) == right) {
          res.push_back(users[i].DN);
        }
      }
      return res;
    } else {
      vector<int> res;
      for (int i = 0; i < users.size(); i++) {
        if (users[i].attribute.count(left) &&
            users[i].attribute.at(left) != right) {
          res.push_back(users[i].DN);
        }
      }
      return res;
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<User> users(n);
  for (int i = 0; i < n; i++) {
    cin >> users[i].DN >> users[i].num;
    for (int j = 0; j < users[i].num; j++) {
      int attribute, value;
      cin >> attribute >> value;
      users[i].attribute.insert({attribute, value});
    }
  }
  sort(users.begin(), users.end(),
       [&](const User &A, const User &B) { return A.DN < B.DN; });
  cin.get();

  int m;
  cin >> m;
  while (m--) {
    string s;
    cin >> s;
    int idx = 0;
    vector<int> result = parse(s, idx, users);
    for (int i = 0; i < result.size(); i++) {
      cout << result[i] << ' ';
    }
    cout << '\n';
  }

  return 0;
}
