#include <bits/stdc++.h>
using std::cerr;
using std::endl;
const int N = 2e5 + 233;
int n, q, fa[N], cnt[N][26], sum[N], len[N], f[N][26], ban, id[N];
char C[N];
std::vector<int> G[N], T[N];
void dfs1(int x) {
  if (G[x].empty()) {
    id[x] = x;
    return;
  }
  for (int y : G[x]) {
    dfs1(y);
    len[x] = std::max(len[x], len[y] + 1);
  }
  for (int y : G[x])
    if (len[x] != len[y] + 1) {
      while (q--) std::cout << "Fou" << '\n';
      exit(0);
    }
  if (x != 1 && G[x].size() == 1)
    id[x] = id[G[x][0]];
  else
    id[x] = x;
}
void dfs2(int x) {
  for (int y : T[x]) {
    fa[y] = x;
    dfs2(y);
  }
}
inline void update(int x, int c, int v) {
  cnt[x][c] += v;
  for (x = fa[x]; x; x = fa[x]) {
    ban -= sum[x] > len[x];
    sum[x] -= f[x][c];
    f[x][c] = 0;
    for (int y : T[x]) {
      f[x][c] = std::max(f[x][c], f[y][c] + cnt[y][c]);
    }
    sum[x] += f[x][c];
    ban += sum[x] > len[x];
  }
}
int main() {
  std::ios::sync_with_stdio(0);
  std::cin >> n >> q;
  for (int i = 2, x; i <= n; ++i) {
    std::cin >> x >> C[i];
    G[x].push_back(i);
  }
  dfs1(1);
  for (int i = 1; i <= n; ++i)
    if (id[i] == i) {
      for (int y : G[i]) T[i].push_back(id[y]);
    }
  dfs2(1);
  for (int i = 1; i <= n; ++i)
    if (C[i] != '?') update(id[i], C[i] - 'a', 1);
  while (q--) {
    int x;
    std::cin >> x;
    if (C[x] != '?') update(id[x], C[x] - 'a', -1);
    std::cin >> C[x];
    if (C[x] != '?') update(id[x], C[x] - 'a', 1);
    if (ban)
      std::cout << "Fou" << '\n';
    else {
      std::cout << "Shi" << ' ';
      long long ans = 0;
      for (int i = 0; i < 26; ++i) {
        ans += (i + 1) * (len[1] - sum[1] + f[1][i]);
      }
      std::cout << ans << '\n';
    }
  }
  return 0;
}
