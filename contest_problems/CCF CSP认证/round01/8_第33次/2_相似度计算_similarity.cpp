/*
 * 相似度计算 (similarity)
 * CCF CSP 第33次认证 真题2
 * 时间限制: 1.0秒  内存限制: 512 MiB
 *
 * 题目描述：
 * 使用 Jaccard 相似度评估两篇文章的相似性。
 * 提取两者的单词集合 A 和 B（忽略大小写），计算 |A∩B| 和 |A∪B|。
 *
 * 输入格式：
 * 第一行两个正整数 n 和 m。
 * 第二行 n 个单词，第三行 m 个单词。
 *
 * 输出格式：
 * 第一行 |A∩B|，第二行 |A∪B|。
 *
 * 数据范围：
 * n,m<=10^4，每个单词最多 10 个字母。
 *
 * 样例输入：
 * 3 2
 * The tHe thE
 * the THE
 *
 * 样例输出：
 * 1
 * 1
 */

#include <iostream>
#include <unordered_set>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n,m;
  cin >> n >> m;
  unordered_set<string> A;
  for(int i=0;i<n;i++){
    string s;
    cin >> s;
    for(int j=0;j<s.size();j++){
       if(s[j]>='A'&&s[j]<='Z'){
        s[j]=s[j]+32;
      }
    }
    A.insert(s);
  }
  unordered_set<string> B;
  for(int i=0;i<m;i++){
    string s;
    cin >> s;
    for(int j=0;j<s.size();j++){
       if(s[j]>='A'&&s[j]<='Z'){
        s[j]=s[j]+32;
      }
    }
    B.insert(s);
  }
  unordered_set<string> C;
  for(auto it=A.begin();it!=A.end();it++){
    C.insert(*it);
  }
  for(auto it=B.begin();it!=B.end();it++){
    C.insert(*it);
  }
  int count=0;
  for(auto it=B.begin();it!=B.end();it++){
      if(A.count(*it)){
        count++;
      }
  }
  cout << count << '\n';
  cout << C.size() << '\n';
  return 0; 
}
