/*
 * HTTP头信息 (HPACK)
 * CCF CSP 第39次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 实现HTTP/2的HPACK头信息压缩算法的解码器。
 * 包含静态表、动态表、三种指令类型（表格引用、字面量并索引、字面量不索引），
 * 以及普通字符串和Huffman编码字符串的解码。
 *
 * 指令格式：
 * - 表格引用指令：1 i，引用编号为i的条目
 * - 字面量并索引指令：2 0 k v 或 2 i v，输出后插入动态表
 * - 字面量不索引指令：3 0 k v 或 3 i v，输出但不插入动态表
 *
 * 字符串格式：
 * - 普通字符串：s（开头非H则原样输出；开头为HH则去掉第一个H）
 * - Huffman编码：Hb（b为偶数个0-9a-f的十六进制串）
 *
 * 输入格式：
 * 第一行S和D，表示静态表条目数和动态表大小限制。
 * 接下来S行为静态表内容。
 * 一行Huffman树表示，一行整数N表示指令数，接下来N行指令。
 *
 * 输出格式：
 * N行，每行格式为 key: value
 *
 * 样例输入：
 * 3 3
 * Foo Bar
 * Foo Barz
 * bar barzz1
 * 001b01c1d1a
 * 11
 * 1 1
 * 3 3 ABCD
 * 3 0 H898007 HHIJK
 * 2 0 H898007 EFGH
 * 1 4
 * 2 0 DDDD EEEE
 * 2 5 GGGG
 * 1 4
 * 1 6
 * 2 0 HHHH IIII
 * 1 4
 *
 * 样例输出：
 * Foo: Bar
 * bar: ABCD
 * abcd: HIJK
 * abcd: EFGH
 * abcd: EFGH
 * DDDD: EEEE
 * abcd: GGGG
 * abcd: GGGG
 * abcd: EFGH
 * HHH: IIII
 * HHH: IIII
 *
 * 数据范围：
 * 1 ≤ S ≤ 64；1 ≤ D ≤ 120；Huffman编码长度不超过8位；
 * 1 ≤ N ≤ 1000；字符串长度不超过150。
 */

#include <iostream>
using namespace std;
int main() {

  return 0;
}
