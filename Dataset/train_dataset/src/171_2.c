#include <bits/stdc++.h>
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
using namespace std;
const double pi =
    3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342;
const int MR = 1e5 + 10;
vector<int> g[MR], g1[MR], rev[MR];
pair<int, int> t[2 * MR];
int u[MR];
int srt[MR], cnt;
int done[MR];
void dfs(int nr, vector<int> *g) {
  done[nr] = 1;
  for (int i : g[nr])
    if (!done[i]) dfs(i, g);
  srt[cnt++] = nr;
}
int sccNr, scc[MR], sz[MR];
void dfs(int nr) {
  scc[nr] = sccNr;
  for (int i : rev[nr])
    if (!scc[i]) dfs(i);
}
int main() {
  int n, mm, h;
  scanf("%d%d%d", &n, &mm, &h);
  for (int i = 0; i < (n); ++i) scanf("%d", &u[i]);
  int m = 0;
  for (int i = 0; i < (mm); ++i) {
    int c0, c1;
    scanf("%d%d", &c0, &c1);
    c0--;
    c1--;
    if (u[c0] == (u[c1] - 1 + h) % h) {
      g[c0].push_back(c1);
      rev[c1].push_back(c0);
      t[m++] = make_pair(c0, c1);
    }
    if (u[c0] == (u[c1] + 1) % h) {
      g[c1].push_back(c0);
      rev[c0].push_back(c1);
      t[m++] = make_pair(c1, c0);
    }
  }
  for (int i = 0; i < (n); ++i)
    if (!done[i]) dfs(i, g);
  reverse(srt, srt + n);
  for (int i = 0; i < (n); ++i)
    if (!scc[srt[i]]) {
      sccNr++;
      dfs(srt[i]);
    }
  for (int i = 0; i < (n); ++i) scc[i]--;
  for (int i = 0; i < (n); ++i) sz[scc[i]]++;
  for (int i = 0; i < (m); ++i)
    if (scc[t[i].first] != scc[t[i].second])
      g1[scc[t[i].first]].push_back(scc[t[i].second]);
  int res = MR, wsk = -1;
  for (int i = 0; i < (sccNr); ++i)
    if (g1[i].empty() && sz[i] < res) {
      res = sz[i];
      wsk = i;
    }
  printf("%d\n", sz[wsk]);
  for (int i = 0; i < (n); ++i)
    if (scc[i] == wsk) printf("%d ", i + 1);
  printf("\n");
  return 0;
}
