/*
 * 脉冲神经网络 (snn)
 * CCF CSP 第23次认证 真题3
 * 时间限制: 1.0秒  内存限制: 512 MiB
 */

#include <bits/stdc++.h>
using namespace std;
struct neuron
{
  double u;
  double v;
  double a;
  double b;
  double c;
  double d;
  int current_count = 0;
};
struct synapse
{
  int t;
  double w;
  int D;
};
/* RAND_MAX assumed to be 32767 */
static unsigned long next1 = 1;
int myrand(void)
{
  next1 = next1 * 1103515245 + 12345;
  return ((unsigned)(next1 / 65536) % 32768);
}
bool update_neuron(neuron &ne, double I, double delta_t)
{
  // 1. 根据公式计算新的 v 和 u
  double v = ne.v + delta_t * (0.04 * ne.v * ne.v + 5 * ne.v + 140 - ne.u) + I;
  double u = ne.u + delta_t * ne.a * (ne.b * ne.v - ne.u);
  // 2. 判断是否开火 (v >= 30)
  ne.v = v;
  ne.u = u;
  if (v >= 30)
  {
    ne.v = ne.c;
    ne.u = ne.u + ne.d;
    return true;
  }
  return false;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, S, P, T;
  cin >> N >> S >> P >> T;
  double delta_t;
  cin >> delta_t;
  int sum_R = 0;
  vector<neuron> neurons(N);
  while (sum_R < N)
  {
    int RN;
    double v, u, a, b, c, d;
    cin >> RN >> v >> u >> a >> b >> c >> d;
    for (int i = 0; i < RN; i++)
    {
      neuron ne;
      ne.v = v;
      ne.u = u;
      ne.a = a;
      ne.b = b;
      ne.c = c;
      ne.d = d;
      neurons[sum_R + i] = ne;
    }
    sum_R += RN;
  }
  vector<int> r(N + P, 0);
  for (int i = N; i <= N + P - 1; i++)
  {
    cin >> r[i];
  }
  vector<vector<synapse>> adj(N + P);
  int max_D = 0;
  for (int i = 0; i < S; i++){
    int s, t, D;
    double w;
    cin >> s >> t >> w >> D;
    max_D = max(max_D, D);
    synapse sy;
    sy.t = t;
    sy.w = w;
    sy.D = D;
    adj[s].push_back(sy);
  }
  int M = max_D + 5;
  vector<vector<double>> mailbox(max_D + 5, vector<double>(N, 0));
  for (int i = 0; i < T; i++)
  {
    for (int j = N; j <= N + P - 1; j++)
    {
      if (r[j] > myrand())
      {
        for (auto a : adj[j])
        {
          mailbox[(i + a.D) % M][a.t] += a.w;
          ;
        }
        /* for (int k = 0; k < S;k++){
         if(synapses[k].s==j)
           mailbox[i + synapses[k].D][synapses[k].t] += synapses[k].w;
        } */
      }
    }
    for (int j = 0; j < N; j++)
    {
      double I = mailbox[i % M][j];
      mailbox[i % M][j] = 0;
      if (update_neuron(neurons[j], I, delta_t))
      {
        for (auto a : adj[j])
        {
          mailbox[(i + a.D) % M][a.t] += a.w;
        }
        neurons[j].current_count++;
      }
    }
  }
  double max_v = neurons[0].v;
  double min_v = neurons[0].v;
  int max_count = neurons[0].current_count;
  int min_count = neurons[0].current_count;
  for (int i = 1; i < N; i++)
  {
    max_v = max(max_v, neurons[i].v);
    min_v = min(min_v, neurons[i].v);
    max_count = max(max_count, neurons[i].current_count);
    min_count = min(min_count, neurons[i].current_count);
  }
  cout << fixed << setprecision(3);
  cout << min_v << ' ' << max_v << '\n';
  cout << min_count << ' ' << max_count << '\n';
  return 0;
}
