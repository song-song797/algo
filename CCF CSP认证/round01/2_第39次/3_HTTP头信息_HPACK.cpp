/*
 * HTTP头信息 (HPACK)
 * CCF CSP 第39次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 实现HTTP/2的HPACK头信息压缩算法的解码器。
 * 包含静态表、动态表、三种指令类型（表格引用、字面量并索引、字面量不索引），
 * 以及普通字符串和Huffman编码字符串的解码。
 *
 * 指令格式：
 * - 表格引用指令：1 i，引用编号为i的条目
 * - 字面量并索引指令：2 0 k v 或 2 i v，输出后插入动态表
 * - 字面量不索引指令：3 0 k v 或 3 i v，输出但不插入动态表
 *
 * 字符串格式：
 * - 普通字符串：s（开头非H则原样输出；开头为HH则去掉第一个H）
 * - Huffman编码：Hb（b为偶数个0-9a-f的十六进制串）
 *
 * 输入格式：
 * 第一行S和D，表示静态表条目数和动态表大小限制。
 * 接下来S行为静态表内容。
 * 一行Huffman树表示，一行整数N表示指令数，接下来N行指令。
 *
 * 输出格式：
 * N行，每行格式为 key: value
 *
 * 样例输入：
 * 3 3
 * Foo Bar
 * Foo Barz
 * bar barzz1
 * 001b01c1d1a
 * 11
 * 1 1
 * 3 3 ABCD
 * 3 0 H898007 HHIJK
 * 2 0 H898007 EFGH
 * 1 4
 * 2 0 DDDD EEEE
 * 2 5 GGGG
 * 1 4
 * 1 6
 * 2 0 HHHH IIII
 * 1 4
 *
 * 样例输出：
 * Foo: Bar
 * bar: ABCD
 * abcd: HIJK
 * abcd: EFGH
 * abcd: EFGH
 * DDDD: EEEE
 * abcd: GGGG
 * abcd: GGGG
 * abcd: EFGH
 * HHH: IIII
 * HHH: IIII
 *
 * 数据范围：
 * 1 ≤ S ≤ 64；1 ≤ D ≤ 120；Huffman编码长度不超过8位；
 * 1 ≤ N ≤ 1000；字符串长度不超过150。
 */

#include <bits/stdc++.h>
using namespace std;

/* void parase(unordered_map<string, char> &res, const string &s, string &cur,
            int &index) {
  if (index > s.size())
    return;
  if (s[index] == '1') {
    res[cur] = s[index + 1];
    index += 2;
  } else {
    cur.push_back('0');
    parase(res, s, cur, ++index);
    cur.pop_back();
    cur.push_back('1');
    parase(res, s, cur, index);
    cur.pop_back();
  }
}

string convert_to_2(const string &s) {
  string temp;
  for (int i = 0; i < s.size() - 2; i++) {
    if (s[i] == '0')
      temp += "0000";
    if (s[i] == '1')
      temp += "0001";
    if (s[i] == '2')
      temp += "0010";
    if (s[i] == '3')
      temp += "0011";
    if (s[i] == '4')
      temp += "0100";
    if (s[i] == '5')
      temp += "0101";
    if (s[i] == '6')
      temp += "0110";
    if (s[i] == '7')
      temp += "0111";
    if (s[i] == '8')
      temp += "1000";
    if (s[i] == '9')
      temp += "1001";
    if (s[i] == 'a')
      temp += "1010";
    if (s[i] == 'b')
      temp += "1011";
    if (s[i] == 'c')
      temp += "1100";
    if (s[i] == 'd')
      temp += "1101";
    if (s[i] == 'e')
      temp += "1110";
    if (s[i] == 'f')
      temp += "1111";
  }
  for (int i = 0; i < s[s.size() - 1] - '0'; i++) {
    temp.pop_back();
  }
  return temp;
}

string convert_to_char(const string &s,
                       unordered_map<string, char> parase_result) {
  string res;
  string cur;
  for (int i = 0; i < s.size(); i++) {
    cur.push_back(s[i]);
    if (parase_result.count(cur)) {
      res.push_back(parase_result[cur]);
      cur = "";
    }
  }
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int S, D;
  cin >> S >> D;
  vector<pair<string, string>> table(S + D + 1);
  for (int i = 1; i <= S; i++) {
    cin >> table[i].first >> table[i].second;
  }
  string s;
  cin >> s;
  string cur = "";
  int index = 0;
  unordered_map<string, char> parase_result;
  parase(parase_result, s, cur, index);

  /* for (auto p : parase_result) {
    cout << p.first << ": " << p.second << '\n';
  } 

  int N;
  cin >> N;
  while (N--) {
    int p1, p2;
    cin >> p1 >> p2;
    if (p1 == 1) {
      cout << table[p2].first << ": " << table[p2].second << '\n';
    }
    if (p1 == 2) {
      if (p2 == 0) {
        string k, v;
        cin >> k >> v;
        if (k[0] == 'H' && k[1] == 'H') {
          k.erase(0, 1);
        } else if (k[0] == 'H' && k[1] != 'H') {
          k.erase(0, 1);
          string temp = convert_to_2(k);
          k = convert_to_char(temp, parase_result);
        }
        if (v[0] == 'H' && v[1] == 'H') {
          v.erase(0, 1);
        } else if (v[0] == 'H' && v[1] != 'H') {
          v.erase(0, 1);
          string temp = convert_to_2(v);
          v = convert_to_char(temp, parase_result);
        }
        cout << k << ": " << v << '\n';
        table.insert(table.begin() + S + 1, {k, v});
        table.pop_back();
      } else {
        string v;
        cin >> v;
        if (v[0] == 'H' && v[1] == 'H') {
          v.erase(0, 1);
        } else if (v[0] == 'H' && v[1] != 'H') {
          v.erase(0, 1);
          string temp = convert_to_2(v);
          v = convert_to_char(temp, parase_result);
        }
        cout << table[p2].first << ": " << v << '\n';
        table.insert(table.begin() + S + 1, {table[p2].first, v});
        table.pop_back();
      }
    }
    if (p1 == 3) {
      if (p2 == 0) {
        string k, v;
        cin >> k >> v;
        if (k[0] == 'H' && k[1] == 'H') {
          k.erase(0, 1);
        } else if (k[0] == 'H' && k[1] != 'H') {
          k.erase(0, 1);
          string temp = convert_to_2(k);
          k = convert_to_char(temp, parase_result);
        }
        if (v[0] == 'H' && v[1] == 'H') {
          v.erase(0, 1);
        } else if (v[0] == 'H' && v[1] != 'H') {
          v.erase(0, 1);
          string temp = convert_to_2(v);
          v = convert_to_char(temp, parase_result);
        }
        cout << k << ": " << v << '\n';
      } else {
        string v;
        cin >> v;
        if (v[0] == 'H' && v[1] == 'H') {
          v.erase(0, 1);
        } else if (v[0] == 'H' && v[1] != 'H') {
          v.erase(0, 1);
          string temp = convert_to_2(v);
          v = convert_to_char(temp, parase_result);
        }
        cout << table[p2].first << ": " << v << '\n';
      }
    }
  }
  return 0;
} */

struct kv {
    string key;
    string value;
};
unordered_map<string, char> res;
void parse(const string &s, int &idx, string &cur) {
    if (idx == s.size())
        return;
    if (s[idx] == '1') {
        idx++;
        res[cur] = s[idx];
        idx++;
    } else {
        cur.push_back('0');
        idx++;
        parse(s, idx, cur);
        cur.pop_back();
        cur.push_back('1');
        parse(s, idx, cur);
        cur.pop_back();
    }
}
string decode(string s) {
    if (s[0] != 'H') {
        return s;
    }
    if (s[0] == 'H' && s[1] == 'H') {
        return s.substr(1);
    }
    if (s[0] == 'H' && s[1] != 'H') {
        string str = s.substr(1, s.size() - 3);
        int p = s[s.size() - 1] - '0';
        string ans;
        for (int i = 0; i < str.size(); i++) {
            int val;
            if (str[i] >= '0' && str[i] <= '9') {
                val = str[i] - '0';
            } else {
                val = str[i] - 'a' + 10;
            }
            for (int j = 3; j >= 0; j--) {
                ans.push_back(((val >> j) & 1) + '0');
            }
        }
        string current;
        string result;
        for (int i = 0; i < ans.size() - p; i++) {
            current.push_back(ans[i]);
            if (res.count(current)) {
                result.push_back(res[current]);
                current = "";
            }
        }
        return result;
    }
    return "";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S, D;
    cin >> S >> D;
    vector<kv> km(S + D + 1);
    for (int i = 1; i <= S; i++) {
        cin >> km[i].key >> km[i].value;
    }
    string s;
    cin >> s;
    string cur = "";
    int start = 0;
    parse(s, start, cur);

    int N;
    cin >> N;
    while (N--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i;
            cin >> i;
            cout << km[i].key << ": " << km[i].value << '\n';
        } else if (op == 2) {
            int i;
            cin >> i;
            if (i == 0) {
                string k, v;
                cin >> k >> v;
                string k1 = decode(k);
                string v1 = decode(v);
                cout << k1 << ": " << v1 << '\n';
                kv kv1;
                kv1.key = k1;
                kv1.value = v1;
                km.insert(km.begin() + S + 1, kv1);
            } else {
                string v;
                cin >> v;
                string v1 = decode(v);
                cout << km[i].key << ": " << v1 << '\n';
                kv kv1;
                kv1.key = km[i].key;
                kv1.value = v1;
                km.insert(km.begin() + S + 1, kv1);
            }
        } else if (op == 3) {
            int i;
            cin >> i;
            if (i == 0) {
                string k, v;
                cin >> k >> v;
                string k1 = decode(k);
                string v1 = decode(v);
                cout << k1 << ": " << v1 << '\n';
            } else {
                string v;
                cin >> v;
                string v1 = decode(v);
                cout << km[i].key << ": " << v1 << '\n';
            }
        }
    }
}