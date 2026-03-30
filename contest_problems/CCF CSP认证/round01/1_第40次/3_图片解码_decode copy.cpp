/*
 * 图片解码 (decode)
 * CCF CSP 第40次认证 真题3
 * 时间限制: 1.5秒  内存限制: 512 MiB
 *
 * 题目背景：
 * InkGraph系统对图片进行加密操作。图片由n*m的字符表格P表示，
 * 仅含大小写字母、数字和下划线。
 *
 * 加密步骤：
 * 1. 设定规模参数Z(1<=Z<=400)，用'?'将图片补齐成Z*Z的正方形图片A0。
 * 2. 请求加密次数t(1<=t<=5*10^4)，从A0开始进行t次加密操作。
 * 3. 密钥K：先添加t，然后每次操作追加6个参数。
 *
 * 加密类型1 - 旋转加密(op=1)：
 *   参数(u,v,L,d,r): 抽取从第u到u+L-1行、第v到v+L-1列的L*L子表B，
 *   将B顺时针旋转d度(90/180/270)后放回原位，再对整体逆时针旋转r次90度。
 *   密钥追加: op,u,v,L,d,r
 *
 * 加密类型2 - 翻转加密(op=2)：
 *   参数(u,d,l,r,o): 抽取第u到d行、第l到r列的矩形子表B，
 *   o=1时上下翻转，o=-1时左右翻转，然后放回原位。
 *   密钥追加: op,u,d,l,r,o
 *
 * 题目描述：
 * 给定加密后的最终结果图At与密钥K，还原出原始图片P。
 *
 * 输入格式：
 * 第一行正整数Z。
 * 接下来Z行，每行Z个字符，为最终结果图At。
 * 接下来一行正整数k(密钥长度)，下一行k个整数表示密钥K。
 *
 * 输出格式：
 * 第一行n和m(原始图片尺寸)。
 * 接下来n行，每行m个字符，为原始图片。
 *
 * 样例输入：
 * 4
 * ?Nk?
 * ??F?
 * ??C?
 * C1??
 * 13
 * 2 1 2 2 3 90 1 2 2 3 1 3 -1
 *
 * 样例输出：
 * 2 3
 * CCF
 * 1Nk
 *
 * 数据范围：
 * 测试点1~5:  op=2 且 Z<=10
 * 测试点6~10: op=2
 * 测试点11~15: Z<=10
 * 测试点16~20: Z<=400
 */

#include <bits/stdc++.h>

using namespace std;

/*struct operation {
  int op;
  int p1, p2, p3, p4, p5;
};

class solution1 {
  struct pixel {
    char c;
    int x, y;

    bool operator<(const pixel &other) const {
      if (x != other.x) {
        return x < other.x;
      }
      return y < other.y;
    }
  };
  void rotate(int p1, int p2, int p3, int p4, int p5, int Z,
              vector<pixel> &active_pixels) {

    for (int i = 0; i < p5 % 4; i++) {
      for (auto &p : active_pixels) {
        int temp = p.x;
        p.x = p.y;
        p.y = Z + 1 - temp;
      }
    }

    if (p4 == 90) {
      for (auto &p : active_pixels) {
        if (p.x >= p1 && p.x <= p1 + p3 - 1 && p.y >= p2 &&
            p.y <= p2 + p3 - 1) {
          int rem_x = p.x;
          int rem_y = p.y;
          p.x = p1 + p2 + p3 - 1 - rem_y;
          p.y = rem_x - p1 + p2;
        }
      }
    } else if (p4 == 180) {
      for (auto &p : active_pixels) {
        if (p.x >= p1 && p.x <= p1 + p3 - 1 && p.y >= p2 &&
            p.y <= p2 + p3 - 1) {
          int rem_x = p.x;
          int rem_y = p.y;
          p.x = 2 * p1 + p3 - 1 - rem_x;
          p.y = 2 * p2 + p3 - 1 - rem_y;
        }
      }
    } else {
      for (auto &p : active_pixels) {
        if (p.x >= p1 && p.x <= p1 + p3 - 1 && p.y >= p2 &&
            p.y <= p2 + p3 - 1) {
          int rem_x = p.x;
          int rem_y = p.y;
          p.x = p1 - p2 + rem_y;
          p.y = p2 + p3 - p1 - rem_x - 1;
        }
      }
    }
  }
  void flip(int p1, int p2, int p3, int p4, int p5,
            vector<pixel> &active_pixels) {
    if (p5 == 1) {
      for (auto &p : active_pixels) {
        if (p.x >= p1 && p.x <= p2 && p.y >= p3 && p.y <= p4) {
          p.x = p1 + p2 - p.x;
        }
      }
    } else {
      for (auto &p : active_pixels) {
        if (p.x >= p1 && p.x <= p2 && p.y >= p3 && p.y <= p4) {
          p.y = p3 + p4 - p.y;
        }
      }
    }
  }
  void solve_1() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Z;
    cin >> Z;

    vector<pixel> active_pixels;
    for (int i = 1; i <= Z; i++) {
      for (int j = 1; j <= Z; j++) {
        char c;
        cin >> c;
        if (c != '?') {
          pixel p;
          p.c = c;
          p.x = i;
          p.y = j;
          active_pixels.push_back(p);
        }
      }
    }

    int k;
    cin >> k;

    int t;
    cin >> t;

    vector<operation> operations(t);
    for (int i = 0; i < t; i++) {
      cin >> operations[i].op >> operations[i].p1 >> operations[i].p2 >>
          operations[i].p3 >> operations[i].p4 >> operations[i].p5;
    }

    for (int i = t - 1; i >= 0; i--) {
      if (operations[i].op == 1) {
        rotate(operations[i].p1, operations[i].p2, operations[i].p3,
               operations[i].p4, operations[i].p5, Z, active_pixels);
      } else {
        flip(operations[i].p1, operations[i].p2, operations[i].p3,
             operations[i].p4, operations[i].p5, active_pixels);
      }
    }

    sort(active_pixels.begin(), active_pixels.end());

    int n = (active_pixels.end() - 1)->x - active_pixels.begin()->x + 1;
    int m = (active_pixels.end() - 1)->y - active_pixels.begin()->y + 1;
    cout << n << ' ' << m << '\n';

    int count = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cout << active_pixels[count].c;
        count++;
      }
      cout << '\n';
    }
  }
};
class solution2 {};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
}*/

struct operation {
    int op;
    int p1, p2, p3, p4, p5;
};
void resolve(vector<vector<char>> &A, operation op) {
    int Z = A.size() - 1;
    vector<vector<char>> B(Z + 1, vector<char>(Z + 1, '?'));
    int u = op.p1;
    int v = op.p2;
    int L = op.p3;
    int d = op.p4;
    int r = op.p5;
    for (int k = 0; k < r % 4; k++) {
        for (int i = 1; i <= Z; i++) {
            for (int j = 1; j <= Z; j++) {
                B[j][Z + 1 - i] = A[i][j];
            }
        }
        swap(A, B);
    }
    for (int k = 0; k < d / 90; k++) {
        B = A;
        for (int i = u; i <= u + L - 1; i++) {
            for (int j = v; j <= v + L - 1; j++) {
                B[u + v + L - j - 1][i + v - u] = A[i][j];
            }
        }
        swap(A, B);
    }
}

void flip(vector<vector<char>> &A, operation op) {
    int u = op.p1;
    int d = op.p2;
    int l = op.p3;
    int r = op.p4;
    int o = op.p5;
    if (o == 1) {
        for (int i = u; i < u + (d - u + 1) / 2; i++) {
            for (int j = l; j <= r; j++) {
                swap(A[i][j], A[u + d - i][j]);
            }
        }
    }
    if (o == -1) {
        for (int i = u; i <= d; i++) {
            for (int j = l; j < l + (r - l + 1) / 2; j++) {
                swap(A[i][j], A[i][r + l - j]);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Z;
    cin >> Z;
    vector<vector<char>> A(Z + 1, vector<char>(Z + 1, 0));
    for (int i = 1; i <= Z; i++) {
        for (int j = 1; j <= Z; j++) {
            cin >> A[i][j];
        }
    }
    int k;
    cin >> k;
    int t;
    cin >> t;
    vector<operation> ops(t);
    for (int i = 0; i < t; i++) {
        cin >> ops[i].op >> ops[i].p1 >> ops[i].p2 >> ops[i].p3 >> ops[i].p4 >> ops[i].p5;
    }
    for (int i = t - 1; i >= 0; i--) {
        if (ops[i].op == 1) {
            resolve(A, ops[i]);
        } else {
            flip(A, ops[i]);
        }
    }

    
    int n = 1, m = 1;
    while (n <= Z && A[n][1] != '?')
        n++;
    n--;
    while (m <= Z && A[1][m] != '?')
        m++;
    m--;
    cout << n << ' ' << m << '\n';
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << A[i][j];
        }
        cout << '\n';
    }
}
