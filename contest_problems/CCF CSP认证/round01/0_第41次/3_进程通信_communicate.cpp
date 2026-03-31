/*
 * 进程通信 (communicate)
 * CCF CSP 第41次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 某操作系统具有动态链接接口并对外广播信息的功能。初始有一段存储容量为10^100的
 * 初始为空的全局内存，内存地址从左到右依次编号0, 1, 2···。
 * 每个字节可以存储一个对象，用ei ∈ {0, 1}, xi ∈ {0, 1}两个状态变量代表
 * i号地址处是否被占用以及是否有对象被存储。
 *
 * 有n个准备进行对象传输的进程，依次编号1, 2, ···, n。
 *
 * 定义三种操作：
 * new p L：建立一个只负责接收进程p所发出对象的新接口，同时建立在进程p与该接口
 *         之间进行消息传递的队列，队列存储容量为L。分配器根据最优适应原则存储队列。
 * send p：进程p同时向所有其对接的接口发送一个对象。如果队列为空，则对象存储在
 *         队列起始地址处；否则存储在最近一次存储位置的下一个位置，若已达末尾则
 *         循环回到起始位置。
 * delete p i：删除进程p对接的第i个接口及对应队列，释放内存，并调整后续接口编号。
 *
 * 输入格式：
 * 第一行用空格隔开的两个整数n, q，依次代表进程数量与操作数量。
 * 接下来q行，每行为一个操作。
 *
 * 输出格式：
 * 对于每一个new操作，输出进程p所对接的新接口相应队列在内存中存储的地址起始位置a。
 * 对于每一个send操作，输出该操作中k个新发送的对象所存储的地址的和。
 *
 * 样例输入：
 * 2 13
 * new 1 2
 * new 1 3
 * send 1
 * delete 1 1
 * new 1 4
 * send 1
 * new 2 3
 * send 2
 * delete 1 2
 * new 1 3
 * send 1
 * delete 1 1
 * send 1
 *
 * 样例输出：
 * 0
 * 2
 * 2
 * 5
 * 8
 * 9
 * 9
 * 5
 * 9
 * 6
 *
 * 数据范围：
 * 1 ≤ n ≤ 100, 1 ≤ q ≤ 8000, 1 ≤ Lm ≤ 5 × 10^5
 * 前40%数据保证不存在delete操作；前80%数据保证Lm ≤ 10, q ≤ 800
 */

#include <bits/stdc++.h>
using namespace std;
const long long INF = 2e18;
#define int long long
struct Queue {
    int l, r;
    int cur_pos;
    bool is_empty;
};
struct Process {
    vector<Queue> q_list;
};
struct NodeBySize {
    int l, r, len;
    bool operator<(const NodeBySize &other) const {
        if (len != other.len) {
            return len < other.len;
        }
        return l < other.l;
    }
};
struct NodeByAddr {
    int l, r, len;
    bool operator<(const NodeByAddr &other) const {
        return l < other.l;
    }
};
Process p_list[105];
set<NodeBySize> pool_by_size;
set<NodeByAddr> pool_by_addr;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    pool_by_size.insert({0, INF, INF + 1});
    pool_by_addr.insert({0, INF, INF + 1});
    while (q--) {
        string op;
        cin >> op;
        if (op == "new") {
            int p, L;
            cin >> p >> L;
            auto it = pool_by_size.lower_bound({0, 0, L});
            cout << it->l << '\n';
            int old_l = it->l;
            int old_r = it->r;
            int old_len = it->len;
            Queue q1;
            q1.l = it->l;
            q1.r = it->l + L - 1;
            q1.cur_pos = it->l - 1;
            q1.is_empty = true;
            p_list[p].q_list.push_back(q1);
            pool_by_size.erase(it);
            pool_by_addr.erase({old_l, old_r, old_len});
            if (old_len - L > 0) {
                int new_l = old_l + L;
                pool_by_size.insert({new_l, old_r, old_len - L});
                pool_by_addr.insert({new_l, old_r, old_len - L});
            }
        }
        if (op == "send") {
            int p;
            cin >> p;
            int sum = 0;
            for (int i = 0; i < p_list[p].q_list.size(); i++) {
                int a = p_list[p].q_list[i].l;
                int b = p_list[p].q_list[i].r;
                if (p_list[p].q_list[i].is_empty) {
                    p_list[p].q_list[i].is_empty = false;
                    p_list[p].q_list[i].cur_pos++;
                } else {
                    if (p_list[p].q_list[i].cur_pos < b) {
                        p_list[p].q_list[i].cur_pos++;
                    } else {
                        p_list[p].q_list[i].cur_pos = a;
                    }
                }
                sum += p_list[p].q_list[i].cur_pos;
            }
            cout << sum << '\n';
        }
        if (op == "delete") {
            int p, i;
            cin >> p >> i;
            auto it = p_list[p].q_list.begin() + i - 1;
            NodeBySize node1;
            int target_l = it->l;
            int target_r = it->r;
            int target_len = it->r - it->l + 1;
            p_list[p].q_list.erase(it);
            auto it_right = pool_by_addr.lower_bound({target_r, 0, 0});
            if (it_right != pool_by_addr.end() && it_right->l == target_r + 1) {
                int r_l = it_right->l, r_r = it_right->r, r_len = it_right->len;
                pool_by_size.erase({r_l, r_r, r_len});
                pool_by_addr.erase({r_l, r_r, r_len});
                target_r = r_r;
            }
            auto it_left = pool_by_addr.lower_bound({target_l, 0, 0});
            if (it_left != pool_by_addr.begin()) {
                it_left--;
                if (it_left != pool_by_addr.end() && it_left->r + 1 == target_l) {
                    int l_l = it_left->l, l_r = it_left->r, l_len = it_left->len;
                    pool_by_size.erase({l_l, l_r, l_len});
                    pool_by_addr.erase({l_l, l_r, l_len});
                    target_l = l_l;
                }
            }
            int final_len = target_r - target_l + 1;
            pool_by_size.insert({target_l, target_r, final_len});
            pool_by_addr.insert({target_l, target_r, final_len});
        }
    }
    return 0;
}