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
struct Word {
    vector<string> wd;
    int num;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    set<string> letter;
    vector<string> wordList;
    auto cmp = [](const pair<pair<string, string>, int> &A, const pair<pair<string, string>, int> &B) {
        if (A.second != B.second) {
            return A.second > B.second;
        }
        int A_size = (A.first.first + A.first.second).size();
        int B_size = (B.first.first + B.first.second).size();
        if (A_size != B_size) {
            return A_size < B_size;
        }
        int A_size1 = A.first.first.size();
        int B_size1 = B.first.first.size();
        if (A_size1 != B_size1) {
            return A_size1 < B_size1;
        }
        return (A.first.first + A.first.second) < (B.first.first + B.first.second);
    };
    vector<pair<pair<string, string>, int>> wordPair;
    vector<Word> vp(n);
    for (int i = 0; i < n; i++) {
        string s;
        int num;
        cin >> s >> num;
        vp[i].num = num;
        for (int j = 0; j < s.size(); j++) {
            vp[i].wd.push_back(string(1, s[j]));
            letter.insert(string(1, s[j]));
            if (j == s.size() - 1)
                continue;
        }
    }
    for (auto lt : letter) {
        wordList.push_back(lt);
    }
    vector<pair<pair<string, string>, int>> tmp;
    map<pair<string, string>, int> ids;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 1 < vp[i].wd.size(); j++) {
            if (!ids.count({vp[i].wd[j], vp[i].wd[j + 1]})) {
                tmp.push_back({{vp[i].wd[j], vp[i].wd[j + 1]}, vp[i].num});
                ids[{vp[i].wd[j], vp[i].wd[j + 1]}] = tmp.size() - 1;
            } else {
                tmp[ids[{vp[i].wd[j], vp[i].wd[j + 1]}]].second += vp[i].num;
            }
        }
    }
    wordPair = tmp;
    while (wordList.size() < m && !wordPair.empty()) {
        sort(wordPair.begin(), wordPair.end(), cmp);
        auto it = wordPair.begin();
        string current = it->first.first + it->first.second;
        wordList.push_back(current);
        vector<Word> vs(n);
        for (int i = 0; i < n; i++) {
            vs[i].num = vp[i].num;
            for (int j = 0; j < vp[i].wd.size();) {
                if (j + 1 < vp[i].wd.size() && vp[i].wd[j] == it->first.first && vp[i].wd[j + 1] == it->first.second) {
                    vs[i].wd.push_back(current);
                    j += 2;
                } else {
                    vs[i].wd.push_back(vp[i].wd[j]);
                    j++;
                }
            }
        }
        vp = vs;
        vector<pair<pair<string, string>, int>> tmp;
        map<pair<string, string>, int> ids;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j + 1 < vp[i].wd.size(); j++) {
                if (!ids.count({vp[i].wd[j], vp[i].wd[j + 1]})) {
                    tmp.push_back({{vp[i].wd[j], vp[i].wd[j + 1]}, vp[i].num});
                    ids[{vp[i].wd[j], vp[i].wd[j + 1]}] = tmp.size() - 1;
                } else {
                    tmp[ids[{vp[i].wd[j], vp[i].wd[j + 1]}]].second += vp[i].num;
                }
            }
        }
        wordPair = tmp;
    }
    for (int i = 0; i < wordList.size(); i++) {
        cout << wordList[i] << '\n';
    }
    return 0;
}
