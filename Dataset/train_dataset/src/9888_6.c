#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20010;
const int MAXM = 880010;
const int INF = 0x3f3f3f3f;
struct Node {
  int from, to, next;
  int cap;
} edge[MAXM];
int tol;
int head[MAXN];
int dep[MAXN];
int gap[MAXN];
int n;
void init() {
  tol = 0;
  memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int w) {
  edge[tol].from = u;
  edge[tol].to = v;
  edge[tol].cap = w;
  edge[tol].next = head[u];
  head[u] = tol++;
  edge[tol].from = v;
  edge[tol].to = u;
  edge[tol].cap = 0;
  edge[tol].next = head[v];
  head[v] = tol++;
}
void BFS(int start, int end) {
  memset(dep, -1, sizeof(dep));
  memset(gap, 0, sizeof(gap));
  gap[0] = 1;
  int que[MAXN];
  int front, rear;
  front = rear = 0;
  dep[end] = 0;
  que[rear++] = end;
  while (front != rear) {
    int u = que[front++];
    if (front == MAXN) front = 0;
    for (int i = head[u]; i != -1; i = edge[i].next) {
      int v = edge[i].to;
      if (dep[v] != -1) continue;
      que[rear++] = v;
      if (rear == MAXN) rear = 0;
      dep[v] = dep[u] + 1;
      ++gap[dep[v]];
    }
  }
}
int SAP(int start, int end) {
  int res = 0;
  BFS(start, end);
  int cur[MAXN];
  int S[MAXN];
  int top = 0;
  memcpy(cur, head, sizeof(head));
  int u = start;
  int i;
  while (dep[start] < n) {
    if (u == end) {
      int temp = INF;
      int inser;
      for (i = 0; i < top; i++)
        if (temp > edge[S[i]].cap) {
          temp = edge[S[i]].cap;
          inser = i;
        }
      for (i = 0; i < top; i++) {
        edge[S[i]].cap -= temp;
        edge[S[i] ^ 1].cap += temp;
      }
      res += temp;
      top = inser;
      u = edge[S[top]].from;
    }
    if (u != end && gap[dep[u] - 1] == 0) break;
    for (i = cur[u]; i != -1; i = edge[i].next)
      if (edge[i].cap != 0 && dep[u] == dep[edge[i].to] + 1) break;
    if (i != -1) {
      cur[u] = i;
      S[top++] = i;
      u = edge[i].to;
    } else {
      int min = n;
      for (i = head[u]; i != -1; i = edge[i].next) {
        if (edge[i].cap == 0) continue;
        if (min > dep[edge[i].to]) {
          min = dep[edge[i].to];
          cur[u] = i;
        }
      }
      --gap[dep[u]];
      dep[u] = min + 1;
      ++gap[dep[u]];
      if (u != start) u = edge[S[--top]].from;
    }
  }
  return res;
}
bool flag[100000];
int prime[100000], cnt = 0;
inline void get_prime() {
  for (int i = 2; i < 100000; ++i) {
    if (!flag[i]) prime[cnt++] = i;
    for (int j = 0; j < cnt && prime[j] * i < 100000; ++j) {
      flag[prime[j] * i] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}
vector<pair<int, int> > p[105];
int V[105][105];
int main() {
  get_prime();
  int N, M;
  scanf("%d%d", &N, &M);
  for (int x, i = 1; i <= N; ++i) {
    scanf("%d", &x);
    for (int j = 0; j < cnt; ++j) {
      if (prime[j] * prime[j] > x) break;
      if (x % prime[j]) continue;
      int cc = 0;
      while (x % prime[j] == 0) ++cc, x /= prime[j];
      p[i].push_back(make_pair(prime[j], cc));
    }
    if (x != 1) p[i].push_back(make_pair(x, 1));
  }
  init();
  int id = 2, S = 0, T = 1;
  for (int i = 1; i <= N; ++i)
    for (int j = 0; j < (int)p[i].size(); ++j) {
      if (i & 1)
        addedge(S, id, p[i][j].second);
      else
        addedge(id, T, p[i][j].second);
      V[i][j] = id++;
    }
  for (int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    if (v & 1) swap(u, v);
    for (int j = 0; j < (int)p[u].size(); ++j)
      for (int k = 0; k < (int)p[v].size(); ++k) {
        if (p[u][j].first != p[v][k].first) continue;
        addedge(V[u][j], V[v][k], INF);
      }
  }
  n = id + 3;
  printf("%d\n", SAP(S, T));
  return 0;
}
