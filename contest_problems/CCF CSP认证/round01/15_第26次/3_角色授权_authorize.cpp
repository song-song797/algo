/*
 * 角色授权 (authorize)
 * CCF CSP 第26次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
struct Role {
  unordered_set<string> operations;
  unordered_set<string> source_types;
  unordered_set<string> source_names;
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  unordered_map<string, Role> roles;
  int n, m, q;
  cin >> n >> m >> q;
  cin.get();

  for (int i = 0; i < n; i++) {
    string role_name;
    cin >> role_name;
    Role current_role;
    int nv;
    cin >> nv;
    for (int j = 0; j < nv; j++) {
      string operation;
      cin >> operation;
      current_role.operations.insert(operation);
    }
    int no;
    cin >> no;
    for (int k = 0; k < no; k++) {
      string source_type;
      cin >> source_type;
      current_role.source_types.insert(source_type);
    }
    int nn;
    cin >> nn;
    for (int l = 0; l < nn; l++) {
      string source_name;
      cin >> source_name;
      current_role.source_names.insert(source_name);
    }
    roles[role_name] = current_role;
  }

  unordered_map<string, vector<string>> user_roles;
  unordered_map<string, vector<string>> group_roles;
  for (int i = 0; i < m; i++) {
    string role_name1;
    cin >> role_name1;
    int ns;
    cin >> ns;
    for (int j = 0; j < ns; j++) {
      char object_type;
      string name;
      cin >> object_type >> name;
      if (object_type == 'u') {
        user_roles[name].push_back(role_name1);
      } else {
        group_roles[name].push_back(role_name1);
      }
    }
  }

  for (int i = 0; i < q; i++) {
    vector<string> role;
    string user_name;
    cin >> user_name;
    if (user_roles.count(user_name)) {
      for (auto &r : user_roles[user_name]) {
        role.push_back(r);
      }
    }
    int ng;
    cin >> ng;
    for (int j = 0; j < ng; j++) {
      string user_group;
      cin >> user_group;
      if (group_roles.count(user_group)) {
        for (auto r : group_roles[user_group]) {
          role.push_back(r);
        }
      }
    }

    string operation, source_type, source_name;
    cin >> operation >> source_type >> source_name;
    bool valid = false;
    for (auto &r : role) {
      if (!roles[r].operations.count(operation) &&
          !roles[r].operations.count("*"))
        continue;
      if (!roles[r].source_types.count(source_type) &&
          !roles[r].source_types.count("*"))
        continue;
      if (!roles[r].source_names.count(source_name) &&
          !roles[r].source_names.empty()) {
        continue;
      }
      valid = true;
      break;
    }

    if (valid)
      cout << 1 << '\n';
    else
      cout << 0 << '\n';
  }
  return 0;
}
