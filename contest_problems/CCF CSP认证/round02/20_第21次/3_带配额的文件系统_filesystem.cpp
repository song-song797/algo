/*
 * 带配额的文件系统 (filesystem)
 * CCF CSP 第21次认证 真题3
 * 时间限制: 5.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long

struct file {
    int size = 0;
    int type; // 0:普通文件 1:目录
    int LD = 0;
    int LR = 0;
    int curr_LD = 0;
    int curr_LR = 0;
};

unordered_map<string, file> maps;

vector<string> parse(string path) {
    vector<string> dirs;
    stringstream ss(path);
    string token;
    while (getline(ss, token, '/')) {
        if (!token.empty()) {
            dirs.push_back(token);
        }
    }
    return dirs;
}

bool is_valid(const string &path) {
    if (path.empty())
        return false;
    int n = path.size();
    if (path[0] != '/')
        return false;
    if (n > 1 && path[n - 1] == '/')
        return false;
    for (int i = 0; i < n; i++) {
        if (i + 1 < n && path[i] == '/' && path[i + 1] == '/')
            return false;
        if (path[i] != '/' && !isalnum(path[i]))
            return false;
    }
    return true;
}

bool can_add_success(const vector<string> &dirs, int size) {
    // 【修复】1. 根目录的特判
    if (maps["/"].LR != 0 && maps["/"].curr_LR + size > maps["/"].LR)
        return false;
    if (dirs.size() == 1 && maps["/"].LD != 0 && maps["/"].curr_LD + size > maps["/"].LD)
        return false;

    string curr = "";
    for (int i = 0; i < (int)dirs.size(); i++) {
        curr += '/';
        curr += dirs[i];
        if (i < (int)dirs.size() - 1) {
            if (maps.count(curr) && maps[curr].type == 0) {
                return false;
            }
            // 【修复】2. 必须加上 LR != 0 的判断
            if (maps.count(curr) && maps[curr].LR != 0 && maps[curr].curr_LR + size > maps[curr].LR) {
                return false;
            }
        }
        if (i == (int)dirs.size() - 2) {
            // 【修复】3. 必须加上 LD != 0 的判断
            if (maps.count(curr) && maps[curr].LD != 0 && maps[curr].curr_LD + size > maps[curr].LD) {
                return false;
            }
        }
    }
    return true;
}

void create_files(const vector<string> &dirs, const string &path, int size) {
    // 【修复】1. 根目录配额累加
    maps["/"].curr_LR += size;
    if (dirs.size() == 1) {
        maps["/"].curr_LD += size;
    }

    string curr = "";
    for (int i = 0; i < (int)dirs.size() - 1; i++) {
        curr += '/';
        curr += dirs[i];

        auto it = maps.find(curr);
        if (it == maps.end()) {
            file f;
            f.type = 1;
            f.curr_LR = size;
            if (i == (int)dirs.size() - 2) {
                f.curr_LD = size;
            }
            maps[curr] = f;
        } else {
            it->second.curr_LR += size;
            if (i == (int)dirs.size() - 2) {
                it->second.curr_LD += size;
            }
        }
    }

    file f;
    f.type = 0;
    f.size = size;
    maps[path] = f;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 【关键修复】：初始化世界之树的根节点
    file root;
    root.type = 1;
    maps["/"] = root;

    int n;
    cin >> n;

    while (n--) {
        char op;
        cin >> op;
        if (op == 'C') {
            string path;
            int size;
            cin >> path >> size;

            if (!is_valid(path)) {
                cout << "N\n";
                continue;
            }

            vector<string> dirs = parse(path);

            if (!maps.count(path)) {
                if (!can_add_success(dirs, size)) {
                    cout << "N\n";
                } else {
                    create_files(dirs, path, size);
                    cout << "Y\n";
                }
            } else {
                if (maps[path].type == 0) {
                    int old_size = maps[path].size;
                    int diff = size - old_size;
                    bool ok = true;

                    if (diff > 0) {
                        // 覆盖检查也要带上根目录
                        if (maps["/"].LR != 0 && maps["/"].curr_LR + diff > maps["/"].LR)
                            ok = false;
                        if (dirs.size() == 1 && maps["/"].LD != 0 && maps["/"].curr_LD + diff > maps["/"].LD)
                            ok = false;

                        string curr = "";
                        for (int i = 0; i < (int)dirs.size() - 1 && ok; i++) {
                            curr += '/';
                            curr += dirs[i];
                            if (maps[curr].LR != 0 && maps[curr].curr_LR + diff > maps[curr].LR) {
                                ok = false;
                            }
                            if (i == (int)dirs.size() - 2 && maps[curr].LD != 0 && maps[curr].curr_LD + diff > maps[curr].LD) {
                                ok = false;
                            }
                        }
                    }

                    if (!ok) {
                        cout << "N\n";
                    } else {
                        // 检查通过，累加差值
                        maps["/"].curr_LR += diff;
                        if (dirs.size() == 1)
                            maps["/"].curr_LD += diff;

                        string curr = "";
                        for (int i = 0; i < (int)dirs.size() - 1; i++) {
                            curr += '/';
                            curr += dirs[i];
                            maps[curr].curr_LR += diff;
                            if (i == (int)dirs.size() - 2) {
                                maps[curr].curr_LD += diff;
                            }
                        }
                        maps[path].size = size;
                        cout << "Y\n";
                    }
                } else {
                    cout << "N\n";
                }
            }
        }

        if (op == 'R') {
            string path;
            cin >> path;
            if (!maps.count(path)) {
                cout << "Y\n";
                continue;
            }

            file target = maps[path];
            int removed_size = 0;

            if (target.type == 0) {
                removed_size = target.size;
            } else {
                removed_size = target.curr_LR;
            }

            vector<string> dirs = parse(path);

            // 根目录扣减
            maps["/"].curr_LR -= removed_size;
            if (target.type == 0 && dirs.size() == 1) {
                maps["/"].curr_LD -= removed_size;
            }

            string curr = "";
            for (int i = 0; i < (int)dirs.size() - 1; i++) {
                curr += '/';
                curr += dirs[i];
                if (maps.count(curr)) {
                    maps[curr].curr_LR -= removed_size;
                    if (target.type == 0 && i == (int)dirs.size() - 2) {
                        maps[curr].curr_LD -= removed_size;
                    }
                }
            }

            // 安全擦除
            vector<string> to_delete;
            for (auto &kv : maps) {
                string p = kv.first;
                if (p == path || (p.length() > path.length() && p.substr(0, path.length()) == path && p[path.length()] == '/')) {
                    to_delete.push_back(p);
                }
            }

            for (const string &p : to_delete) {
                maps.erase(p);
            }

            cout << "Y\n";
        }

        if (op == 'Q') {
            string path;
            int LD, LR;
            cin >> path >> LD >> LR;

            // 【修复】增加输出判定、目录类型判定、逻辑运算符括号
            if (!maps.count(path) || maps[path].type != 1) {
                cout << "N\n";
                continue;
            }

            if ((LD != 0 && LD < maps[path].curr_LD) || (LR != 0 && LR < maps[path].curr_LR)) {
                cout << "N\n";
            } else {
                maps[path].LD = LD;
                maps[path].LR = LR;
                cout << "Y\n";
            }
        }
    }
    return 0;
}