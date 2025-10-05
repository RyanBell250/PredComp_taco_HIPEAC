#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
using namespace std;
const int MAX_SIZE = 1 << 20;
vector<pair<int, int>> adj[100000], E;
queue<int> Q[100001];
int N, dist[100000];
long long pot[100000];
char buf[MAX_SIZE];
inline char get_char() {
  static int p = 0, s = 0;
  if (p == s) {
    p = 0;
    s = fread(buf, 1, MAX_SIZE, stdin);
    if (p == s) return 0;
  }
  return buf[p++];
}
inline int get_int() {
  int ret = 0;
  bool is_negative = false;
  char c = -1;
  while (('0' > c || c > '9') && c != '-') c = get_char();
  if (c == '-') {
    is_negative = true;
    c = get_char();
  }
  while ('0' <= c && c <= '9') ret *= 10, ret += c - '0', c = get_char();
  return (is_negative ? -ret : ret);
}
void dijkstra() {
  memset(dist, 0x7f, sizeof(dist));
  dist[0] = 0;
  Q[0].push(0);
  for (int t = 0; t <= N; t++) {
    while (!Q[t].empty()) {
      int c = Q[t].front();
      Q[t].pop();
      if (t != dist[c]) continue;
      for (auto [n, w] : adj[c])
        if (dist[n] > dist[c] + pot[c] - pot[n] + w) {
          dist[n] = dist[c] + pot[c] - pot[n] + w;
          if (dist[n] <= N) Q[dist[n]].push(n);
        }
    }
  }
  for (int i = 0; i < N; i++)
    if (pot[i] != 0x7f7f7f7f7f7f7f7fLL) pot[i] += dist[i];
}
int main() {
  int M, Q;
  priority_queue<pair<long long, int>> PQ;
  N = get_int();
  M = get_int();
  Q = get_int();
  E.resize(M);
  for (auto &[a, b] : E) {
    int c;
    a = get_int();
    b = get_int();
    c = get_int();
    adj[--a].emplace_back(--b, c);
    b = adj[a].size() - 1;
  }
  memset(pot, 0x7f, sizeof(pot));
  pot[0] = 0;
  PQ.push({0, 0});
  while (!PQ.empty()) {
    auto [t, c] = PQ.top();
    PQ.pop();
    if (-t != pot[c]) continue;
    for (auto [n, w] : adj[c])
      if (pot[n] > pot[c] + w) {
        pot[n] = pot[c] + w;
        PQ.push({-pot[n], n});
      }
  }
  while (Q--) {
    int t = get_int(), c = get_int();
    if (t == 1) {
      c--;
      printf("%lld\n", pot[c] != 0x7f7f7f7f7f7f7f7fLL ? pot[c] : -1);
    } else {
      while (c--) {
        t = get_int() - 1;
        adj[E[t].first][E[t].second].second++;
      }
      dijkstra();
    }
  }
  return 0;
}
