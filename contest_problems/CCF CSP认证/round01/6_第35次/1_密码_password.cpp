/*
 * 密码 (password)
 * CCF CSP 第35次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 用户密码由大写字母、小写字母、数字和特殊字符(*和#)共64种字符组成。
 * 密码安全度分为高(2)、中(1)、低(0)三档：
 * 高：长度>=6，包含字母、数字和特殊字符，同一字符出现不超过2次；
 * 中：长度>=6，包含字母、数字和特殊字符，未达高要求；
 * 低：长度>=6，未达中要求。
 *
 * 输入格式：
 * 第一行正整数 n，接下来 n 行每行一个密码字符串。
 *
 * 输出格式：
 * n 行，每行输出 2、1 或 0。
 *
 * 数据范围：
 * n<=100，每个字符串不超过 20 个字符。
 *
 * 样例输入：
 * 4
 * csp#ccsp
 * csp#ccsp2024
 * Csp#ccsp2024
 * CSP#2024
 *
 * 样例输出：
 * 0
 * 1
 * 2
 * 2
 */

#include <algorithm>
#include <iostream>

using namespace std;
/* int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  while (n--) {
    string s;
    cin >> s;
    int arr[128] = {0};
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    int max_num = 0;
    for (const char &c : s) {
      if (c >= '0' && c <= '9')
        count1++;
      else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
        count2++;
      } else {
        count3++;
      }
      arr[c]++;
      max_num=max(max_num,arr[c]);
    }
    if (count1 == 0 || count2 == 0 || count3 == 0) {
      cout << 0 << '\n';
      continue;
    }
    if (max_num > 2) {
      cout << 1 << '\n';
    } else {
      cout << 2 << '\n';
    }
  }
  return 0;
} */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        int counts[256]={0};
        string s;
        cin >> s;
        bool have_letter = false;
        bool have_num = false;
        bool have_schar = false;
        bool valid = false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z') {
                have_letter = true;
            } else if (s[i] >= '0' && s[i] <= '9') {
                have_num = true;
            } else {
                have_schar = true;
            }
            counts[s[i]]++;
            if (counts[s[i]] > 2)
                valid = true;
        }
        if (have_letter && have_num && have_schar && !valid) {
            cout << 2 << '\n';
        } else if (have_letter && have_num && have_schar && valid) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
}
