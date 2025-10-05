#include <bits/stdc++.h>
using namespace std;
int rd() {
  char c = getchar();
  int t = 0, f = 1;
  while (!isdigit(c)) f = (c == '-') ? -1 : 1, c = getchar();
  while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
  return t * f;
}
void wt(int x) {
  if (x < 0)
    putchar('-'), wt(-x);
  else {
    if (x > 9) wt(x / 10);
    putchar(x % 10 + 48);
  }
}
const int N = 300035;
vector<int> VI[N];
int n, m, ele, x[N], y[N], be[N], id[N];
int chk(int x, int y) {
  if (VI[x] == VI[y]) return -1;
  return VI[x] < VI[y] ? 1 : 0;
}
bool cmp_VI(int x, int y) {
  int t = chk(x, y);
  return t == -1 ? 0 : t;
}
vector<int> E[N];
int ok[N], col[N], C;
void dfs(int x) {
  ok[x] = 1, col[x] = ++C;
  for (int i = ((int)0); i <= ((int)E[x].size() - 1); i++)
    if (!ok[E[x][i]]) dfs(E[x][i]);
}
int deg[N], st;
map<int, int> vis[N];
int main() {
  n = rd(), m = rd();
  for (int i = ((int)1); i <= ((int)n); i++) VI[i].push_back(i), id[i] = i;
  for (int i = ((int)1); i <= ((int)m); i++) {
    x[i] = rd(), y[i] = rd();
    VI[x[i]].push_back(y[i]), VI[y[i]].push_back(x[i]);
  }
  for (int i = ((int)1); i <= ((int)n); i++) sort(VI[i].begin(), VI[i].end());
  sort(id + 1, id + n + 1, cmp_VI);
  for (int j = 1, i = 1; i <= n;) {
    ele++;
    while (chk(id[i], id[j]) == -1) j++;
    while (i < j) be[id[i]] = ele, i++;
  }
  if (ele == 1) {
    puts("YES");
    for (int i = ((int)1); i <= ((int)n); i++) printf("1 ");
    return 0;
  }
  for (int i = ((int)1); i <= ((int)m); i++)
    if (be[x[i]] != be[y[i]] && vis[be[x[i]]][be[y[i]]] == 0) {
      if (++deg[be[x[i]]] == 3) return puts("NO"), 0;
      if (++deg[be[y[i]]] == 3) return puts("NO"), 0;
      E[be[x[i]]].push_back(be[y[i]]), E[be[y[i]]].push_back(be[x[i]]);
      vis[be[x[i]]][be[y[i]]] = 1, vis[be[y[i]]][be[x[i]]] = 1;
    }
  for (int i = ((int)1); i <= ((int)ele); i++)
    if (deg[i] == 1) st = i;
  puts("YES"), dfs(st);
  for (int i = ((int)1); i <= ((int)n); i++) printf("%d ", col[be[i]]);
  return 0;
}
