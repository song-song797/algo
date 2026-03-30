/*
 * 解压缩 (decompress)
 * CCF CSP 第30次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 实现一种压缩算法的解压缩程序。
 * 数据流包含字面量和回溯引用两种元素。
 * 需要解析导引域（原始数据长度）和数据域（字面量和回溯引用）。
 *
 * 输入格式：
 * 第一行正整数 s（字节数）。
 * 接下来若干行十六进制数据。
 *
 * 输出格式：
 * 解压缩后的数据，每行 8 个字节（十六进制），最后一行可不满。
 *
 * 数据范围：
 * 解压后数据长度不超过 2MiB, s<=2*10^6。
 *
 * 样例输入：
 * 81
 * 8001240102030405
 * 060708090af03c00
 * (... 后续省略 ...)
 *
 * 样例输出：
 * 0102030405060708
 * 090a000102030405
 * (... 后续省略 ...)
 */

#include <bits/stdc++.h>
using namespace std;
struct LogDecoder {
  vector<unsigned char> res;
  vector<unsigned char> raw;
  int cursor = 0;
  int n = 0;
  void parse_header() {
    int shift = 0;
    while (1) {
      int val = raw[cursor] & 127;
      n += val * (1 << shift);
      shift += 7;
      if (((raw[cursor] >> 7) & 1) == 0)
        break;
      cursor++;
    }
    cursor++;
    res.reserve(n);
  }
  void parse_literal() {
    int t_l = (raw[cursor] & 252) >> 2;
    if (t_l < 60) {
      int l = t_l + 1;
      cursor++;
      while (l > 0) {
        res.push_back(raw[cursor]);
        cursor++;
        l--;
      }
    } else {
      int b = t_l - 60 + 1;
      cursor++;
      int l = 1;
      int shift = 0;
      while (b > 0) {
        l += raw[cursor] * (1 << shift);
        cursor++;
        b--;
        shift += 8;
      }
      while (l > 0) {
        res.push_back(raw[cursor]);
        cursor++;
        l--;
      }
    }
  }
  void parse_ref() {
    if ((raw[cursor] & 3) == 1) {
      int l = ((raw[cursor] & 28) >> 2) + 4;
      int high_3 = (raw[cursor] & 224) << 3;
      cursor++;
      int o = high_3 + raw[cursor];
      int start = res.size() - o;
      for (int k = 0; k < l; k++) {
        res.push_back(res[start + k]);
      }
      cursor++;
    } else {
      int l = ((raw[cursor] & 252) >> 2) + 1;
      cursor++;
      int o = 0;
      o += raw[cursor];
      cursor++;
      o += raw[cursor] * 256;
      int start = res.size() - o;
      for (int k = 0; k < l; k++) {
        res.push_back(res[start + k]);
      }
      cursor++;
    }
  }
  void decode() {
    while (res.size() < n) {
      int flag = raw[cursor] & 3;
      if (flag == 0)
        parse_literal();
      else {
        parse_ref();
      }
    }
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int s;
  cin >> s;

  LogDecoder ld;
  string line;
  while (ld.raw.size() < s && cin >> line) {
    for (int i = 0; i < line.size(); i += 2) {
      string temp = line.substr(i, 2);
      unsigned char c = stoi(temp, nullptr, 16);
      ld.raw.push_back(c);
    }
  }
  ld.parse_header();
  ld.decode();
  cout << hex << setfill('0');
  for (int i = 0; i < ld.res.size(); i++) {
    cout << setw(2) << (int)ld.res[i];
    if (i % 8 == 7)
      cout << '\n';
  }
  return 0;
}
