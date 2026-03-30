/*
 * JPEG 解码 (jpeg)
 * CCF CSP 第28次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
double idct(int x, int i, int j, const int M[8][8]) {
  double res = 0;
  for (int u = 0; u < 8; u++) {
    for (int v = 0; v < 8; v++) {
      double au = 1;
      double av = 1;
      if (u == 0)
        au = sqrt(0.5);
      if (v == 0)
        av = sqrt(0.5);
      res += au * av * M[u][v] * cos(pi * u / 8 * (i + 0.5)) *
             cos(pi * v / 8 * (j + 0.5));
    }
  }
  return 0.25 * res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int Q[8][8];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cin >> Q[i][j];
    }
  }

  int n;
  cin >> n;
  int T;
  cin >> T;
  int M[8][8] = {0};
  int x = 0, y = 0;
  int direction = 0;

  for (int i = 0; i < n; i++) {
    cin >> M[x][y];
    if (x == 7 && y == 7)
      break;
    if (direction == 0) {
      if (y == 7) {
        x++;
        direction = 1;
      } else if (x == 0) {
        y++;
        direction = 1;
      } else {
        x--;
        y++;
      }
    } else if (direction == 1) {
      if (x == 7) {
        y++;
        direction = 0;
      } else if (y == 0) {
        x++;
        direction = 0;
      } else {
        x++;
        y--;
      }
    }
  }
  if (T == 0) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        cout << M[i][j] << ' ';
      }
      cout << '\n';
    }
    return 0;
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      M[i][j] = M[i][j] * Q[i][j];
    }
  }
  if (T == 1) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        cout << M[i][j] << ' ';
      }
      cout << '\n';
    }
    return 0;
  }

  if (T == 2) {
    int M_prime[8][8];
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        M_prime[i][j] = round(idct(M[i][j], i, j, M) + 1e-6 + 128);
        cout << min(255, max(0, M_prime[i][j])) << ' ';
      }
      cout << '\n';
    }
  }
  return 0;
}
