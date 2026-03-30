#include <bits/stdc++.h>
using namespace std;
struct Image {
  int Z;
  vector<vector<char>> grid;
  int current_rot;
  Image(int Z) {
    this->Z = Z;
    this->current_rot = 0;
    grid.assign(Z + 1, vector<char>(Z + 1, '?'));
  }
};
struct operation {
  int op;
  int p1, p2, p3, p4, p5;
};
pair<int, int> maps(int r, int c, int Z, int rot) {
  int x = r;
  int y = c;
  if (rot == 90) {
    x = Z + 1 - c;
    y = r;
  } else if (rot == 180) {
    x = Z + 1 - r;
    y = Z + 1 - c;
  } else if (rot == 270) {
    x = c;
    y = Z + 1 - r;
  }
  return {x, y};
}
void rotate(int p1, int p2, int p3, int p4, int p5, Image &image) {
  // 1. 先撤销全局旋转（逆时针 r 次变为顺时针 r 次，每次 90 度）
  image.current_rot = (image.current_rot + p5 * 90) % 360;

  // 2. 提取当前视角下的子表到临时数组 sub
  vector<vector<char>> sub(p3, vector<char>(p3));
  for (int i = 0; i < p3; i++) {
    for (int j = 0; j < p3; j++) {
      // 找到当前逻辑坐标 (p1+i, p2+j) 对应的物理位置
      pair<int, int> phys = maps(p1 + i, p2 + j, image.Z, image.current_rot);
      sub[i][j] = image.grid[phys.first][phys.second];
    }
  }

  // 3. 计算局部逆向旋转（逆时针转 d 度，即顺时针转 360-d 度）
  int rotate_count = (360 - p4) / 90;
  for (int c = 0; c < rotate_count; c++) {
    vector<vector<char>> next_sub(p3, vector<char>(p3));
    for (int i = 0; i < p3; i++) {
      for (int j = 0; j < p3; j++) {
        // 顺时针 90 度公式：(i, j) -> (j, L-1-i)
        next_sub[j][p3 - 1 - i] = sub[i][j];
      }
    }
    sub = next_sub;
  }

  // 4. 将旋转后的 sub 写回物理 grid
  for (int i = 0; i < p3; i++) {
    for (int j = 0; j < p3; j++) {
      pair<int, int> phys = maps(p1 + i, p2 + j, image.Z, image.current_rot);
      image.grid[phys.first][phys.second] = sub[i][j];
    }
  }
}
void flip(int u, int d, int l, int r, int o, Image &image) {
  int rows = d - u + 1;
  int cols = r - l + 1;

  // 1. 提取：按当前全局角度，把逻辑矩形“抠”出来存入 sub
  vector<vector<char>> sub(rows, vector<char>(cols));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // 注意：maps 传入的是全图逻辑坐标 (u+i, l+j)
      pair<int, int> phys = maps(u + i, l + j, image.Z, image.current_rot);
      sub[i][j] = image.grid[phys.first][phys.second];
    }
  }

  // 2. 局部变换：在 sub 内部进行翻转
  if (o == 1) { // 上下翻转
    for (int i = 0; i < rows / 2; i++) {
      swap(sub[i], sub[rows - 1 - i]);
    }
  } else { // 左右翻转 (o == -1)
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols / 2; j++) {
        swap(sub[i][j], sub[i][cols - 1 - j]);
      }
    }
  }

  // 3. 写回：将翻转后的 sub 重新放回物理底片
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      pair<int, int> phys = maps(u + i, l + j, image.Z, image.current_rot);
      image.grid[phys.first][phys.second] = sub[i][j];
    }
  }
}
int main() {
  int Z;
  cin >> Z;

  // 1. 读取加密后的底片
  Image image(Z);
  for (int i = 1; i <= Z; i++) {
    for (int j = 1; j <= Z; j++) {
      cin >> image.grid[i][j];
    }
  }

  // 2. 解析密钥
  int K_len;
  cin >> K_len;
  int t;
  cin >> t; // 第一个数是 t

  vector<operation> ops;
  for (int i = 0; i < t; i++) {
    operation cur;
    cin >> cur.op;
    if (cur.op == 1) {
      cin >> cur.p1 >> cur.p2 >> cur.p3 >> cur.p4 >> cur.p5;
    } else {
      cin >> cur.p1 >> cur.p2 >> cur.p3 >> cur.p4 >> cur.p5;
    }
    ops.push_back(cur);
  }

  // 3. 【关键】从后往前逆向解密
  for (int i = t - 1; i >= 0; i--) {
    if (ops[i].op == 1) {
      // 撤销旋转：p1=u, p2=v, p3=L, p4=d, p5=r
      rotate(ops[i].p1, ops[i].p2, ops[i].p3, ops[i].p4, ops[i].p5, image);
    } else {
      // 撤销翻转：p1=u, p2=d, p3=l, p4=r, p5=o
      flip(ops[i].p1, ops[i].p2, ops[i].p3, ops[i].p4, ops[i].p5, image);
    }
  }

  // 4. 寻找原始图片的边界 n x m
  int n = 0, m = 0;
  for (int r = 1; r <= Z; r++) {
    for (int c = 1; c <= Z; c++) {
      pair<int, int> phys = maps(r, c, Z, image.current_rot);
      if (image.grid[phys.first][phys.second] != '?') {
        n = max(n, r);
        m = max(m, c);
      }
    }
  }

  // 5. 输出还原后的图片
  cout << n << " " << m << endl;
  for (int r = 1; r <= n; r++) {
    for (int c = 1; c <= m; c++) {
      pair<int, int> phys = maps(r, c, Z, image.current_rot);
      cout << image.grid[phys.first][phys.second];
    }
    cout << endl;
  }

  return 0;
}
