/*
 * 重复局面 (repeat)
 * CCF CSP 第30次认证 真题1
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 国际象棋局面用 8×8 字符数组表示。
 * 给定 n 步棋后的局面，统计每个局面是第几次出现。
 *
 * 输入格式：
 * 第一行正整数 n。
 * 接下来 8*n 行，每 8 行对应一个局面。
 *
 * 输出格式：
 * n 行，每行一个整数。
 *
 * 数据范围：
 * n<=100。
 *
 * 样例输入：
 * 8
 * ********
 * ******pk
 * *****r*p
 * p*pQ****
 * ********
 * **b*B*PP
 * ****qP**
 * **R***K*
 * (... 后续省略 ...)
 *
 * 样例输出：
 * 1
 * 1
 * 1
 * 1
 * 1
 * 2
 * 2
 * 1
 */

#include <iostream>
#include <vector>
using namespace std;
bool is_equal(vector<char>& A, vector<char>& B) {
	for (int i = 0; i < 64; i++) {
		if (A[i] != B[i]) return false;
	}
	return true;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<vector<char>> situations(n, vector<char>(64, ' '));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 64; j++) {
			cin >> situations[i][j];
		}
	}
	vector<int> counts(n, 1);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (is_equal(situations[i], situations[j])) counts[j]++;
		}
	}
	for (int& count : counts) {
		cout << count << '\n';
	}
	return 0; 
}
