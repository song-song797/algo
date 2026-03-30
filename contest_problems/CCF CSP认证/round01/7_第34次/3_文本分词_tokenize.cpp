/*
 * 文本分词 (tokenize)
 * CCF CSP 第34次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 实现 BPE（Byte Pair Encoding）词汇表生成过程。
 * 首先将输入单词拆分为单字母，然后反复合并出现频率最高的"词汇对"，
 * 直到词汇表达到指定长度或所有单词都被合并为一个词汇。
 *
 * 输入格式：
 * 第一行两个正整数 n 和 m（单词数量和期望词汇表长度）。
 * 接下来 n 行每行一个字符串和一个正整数（单词和频率）。
 *
 * 输出格式：
 * m 行，按照加入顺序输出词汇表中的词汇。
 *
 * 数据范围：
 * n<=10000, m<=5000, |s|<=25, 总频率不超过 10^6。
 *
 * 样例输入：
 * 4 8
 * cut 15
 * cute 10
 * but 6
 * execute 3
 *
 * 样例输出：
 * b
 * c
 * e
 * t
 * u
 * x
 * ut
 * cut
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<string>> vs(n);
  int freq[10005] = {0};
  vector<string> wordList;
  unordered_set<string> is_seen;

  for (int i = 0; i < n; i++) {
    string temp;
    cin >> temp >> freq[i];
    for (int j = 0; j < temp.size(); j++) {
      string s(1, temp[j]);
      vs[i].push_back(s);
      if (!is_seen.count(vs[i][j])) {
        wordList.push_back(vs[i][j]);
        is_seen.insert(vs[i][j]);
      }
    }
  }
  sort(wordList.begin(), wordList.end());

  auto cmp = [&](const auto &A, const auto &B) {
    if (A.second != B.second) {
      return A.second > B.second;
    }
    if (A.first.first.size() + A.first.second.size() !=
        B.first.first.size() + B.first.second.size()) {
      return A.first.first.size() + A.first.second.size() <
             B.first.first.size() + B.first.second.size();
    }
    if (A.first.first.size() != B.first.first.size()) {
      return A.first.first.size() < B.first.first.size();
    }
    return A.first.first + A.first.second < B.first.first + B.first.second;
  };

  while (wordList.size() < m) {
    map<pair<string, string>, int> mp;
    for (int i = 0; i < vs.size(); i++) {
      for (int j = 0; j < vs[i].size(); j++) {
        if (j + 1 >= vs[i].size())
          continue;
        mp[{vs[i][j], vs[i][j + 1]}] += freq[i];
      }
    }

    if (mp.empty())
      break;
    auto best_it = mp.begin();
    for (auto it = mp.begin(); it != mp.end(); it++) {
      if (cmp(*it, *best_it)) {
        best_it = it;
      }
    }
    string best_left = best_it->first.first;
    string best_right = best_it->first.second;
    wordList.push_back(best_left + best_right);

    for (int i = 0; i < n; i++) {
      vector<string> new_word;
      for (int j = 0; j < vs[i].size(); j++) {
        if (j + 1 < vs[i].size() && vs[i][j] == best_left &&
            vs[i][j + 1] == best_right) {
          new_word.push_back(best_left + best_right);
          j++;
        } else {
          new_word.push_back(vs[i][j]);
        }
      }
      vs[i] = new_word;
    }
  }
  for (const auto &word : wordList) {
    cout << word << '\n';
  }
  return 0;
}
