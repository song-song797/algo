#include <iostream>
#include <vector>
#include <string>

using namespace std;

static const int MOD = 929;

// 取模到 [0, MOD)
int norm(long long x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return (int)x;
}

// 获取字符所属模式
// 0: 大写, 1: 小写, 2: 数字
int get_mode(char c) {
    if ('A' <= c && c <= 'Z') return 0;
    if ('a' <= c && c <= 'z') return 1;
    return 2;
}

// 生成有效数据码字（不含长度码字内容，不含填充，不含校验）
// 返回值中 data[0] 先放占位符，之后再补真实长度
vector<int> generate_data_codewords(const string &str) {
    int current_mode = 0; // 初始为大写模式
    vector<int> sub_nums;

    for (char c : str) {
        int target_mode = get_mode(c);

        if (target_mode != current_mode) {
            // 选择最短切换方式
            if (current_mode == 0) { // 大写
                if (target_mode == 1) sub_nums.push_back(27);     // 大写 -> 小写
                else sub_nums.push_back(28);                      // 大写 -> 数字
            } else if (current_mode == 1) { // 小写
                if (target_mode == 0) {                           // 小写 -> 大写
                    sub_nums.push_back(28);                       // 先到数字
                    sub_nums.push_back(28);                       // 再到大写
                } else {
                    sub_nums.push_back(28);                       // 小写 -> 数字
                }
            } else { // 数字
                if (target_mode == 0) sub_nums.push_back(28);     // 数字 -> 大写
                else sub_nums.push_back(27);                      // 数字 -> 小写
            }
            current_mode = target_mode;
        }

        // 录入字符值
        if (current_mode == 0) sub_nums.push_back(c - 'A');
        else if (current_mode == 1) sub_nums.push_back(c - 'a');
        else sub_nums.push_back(c - '0');
    }

    // 若个数为奇数，补 29
    if (sub_nums.size() % 2 == 1) sub_nums.push_back(29);

    vector<int> data_words;
    data_words.push_back(0); // 长度码字占位

    for (size_t i = 0; i < sub_nums.size(); i += 2) {
        data_words.push_back(sub_nums[i] * 30 + sub_nums[i + 1]);
    }

    return data_words;
}

// 构造生成多项式 g(x) = (x-3)(x-3^2)...(x-3^k)
// 返回按“低次到高次”存储：g[0] + g[1]x + ... + g[k]x^k
vector<int> build_generator(int k) {
    vector<int> g(1, 1); // g(x)=1
    int pw = 3;          // 3^1

    for (int i = 1; i <= k; ++i) {
        vector<int> ng(g.size() + 1, 0);

        // ng(x) = g(x) * (x - pw)
        for (size_t j = 0; j < g.size(); ++j) {
            ng[j] = norm(ng[j] - 1LL * g[j] * pw); // 乘上 (-pw)
            ng[j + 1] = norm(ng[j + 1] + g[j]);    // 乘上 x
        }

        g = ng;
        pw = (int)(1LL * pw * 3 % MOD); // 3^(i+1)
    }

    return g;
}

// 计算校验码字
// data 为“长度码字 + 有效数据码字 + 填充码字”
// 返回 c_{k-1}, c_{k-2}, ..., c_0
vector<int> compute_check_codewords(const vector<int> &data, int k) {
    vector<int> g = build_generator(k); // 低次到高次，g[k] == 1

    // 构造 x^k * d(x)，其中 data[0] 对应最高次项
    vector<int> a = data;
    int n = (int)data.size();
    for (int i = 0; i < k; ++i) a.push_back(0);

    // 多项式长除法
    // 除式是 g(x)，其高次到低次系数为：
    // 1, g[k-1], g[k-2], ..., g[0]
    for (int i = 0; i < n; ++i) {
        int factor = a[i];
        if (factor == 0) continue;

        for (int j = 1; j <= k; ++j) {
            // 对应除式中第 j 个系数（跳过最高次系数 1）
            int coef =g[k - j];
            a[i + j] = norm(a[i + j] - 1LL * factor * coef);
        }
    }

    // 余式在最后 k 项，表示 x^(k-1) ... x^0 的系数
    // 题意中校验码是 r(x) 的系数，且 x^k d(x) ≡ q(x)g(x) - r(x)
    // 所以 r = -remainder (mod 929)
    vector<int> check(k);
    for (int i = 0; i < k; ++i) {
        check[i] = norm(-a[n + i]);
    }
    return check;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w, s;
    cin >> w >> s;
    string str;
    cin >> str;

    // 1. 生成初始数据码字（长度码字先占位）
    vector<int> data = generate_data_codewords(str);

    // 2. 计算校验码字数量
    int k = (s == -1 ? 0 : (1 << (s + 1)));

    // 3. 计算需要补多少个 900
    // 设最终总码字数 = 数据码字数(data_count) + 校验码字数k
    // 要满足能被 w 整除
    int current_data_count = (int)data.size(); // 含长度占位 + 有效数据
    int padding = (w - (current_data_count + k) % w) % w;

    // 4. 补真实长度码字
    // 长度码字表示全部“数据码字”个数 = 长度码字 + 有效数据码字 + 填充码字
    data[0] = current_data_count + padding;

    // 5. 追加填充码字
    for (int i = 0; i < padding; ++i) data.push_back(900);

    // 6. 输出数据码字
    for (int x : data) {
        cout << x << '\n';
    }

    // 7. 输出校验码字
    if (s != -1) {
        vector<int> check = compute_check_codewords(data, k);
        for (int x : check) {
            cout << x << '\n';
        }
    }

    return 0;
}