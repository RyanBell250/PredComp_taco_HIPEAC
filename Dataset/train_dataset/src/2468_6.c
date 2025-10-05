#include <bits/stdc++.h>
using namespace ::std;
const int N = (int)1e5 + 5;
int n, m, wyn, suma, sk[N], ile[N];
vector<int> t1[N], t2[N], t3[N], q;
bool o1[N], o2[N], byla;
void dfs1(int v) {
  o1[v] = true;
  for (int w : t1[v])
    if (!o1[w]) dfs1(w);
  q.push_back(v);
}
void zbij(int v, int x) {
  sk[v] = x;
  ile[x]++;
  for (int w : t2[v])
    if (sk[w] == 0) zbij(w, x);
}
void dfs3(int v) {
  suma += ile[v];
  if (ile[v] > 1) byla = true;
  o2[v] = true;
  for (int w : t3[v])
    if (!o2[w]) dfs3(w);
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    t1[a].push_back(b);
    t2[b].push_back(a);
  }
  for (int i = 1; i <= n; i++)
    if (!o1[i]) dfs1(i);
  while (!q.empty()) {
    int w = q.back();
    q.pop_back();
    if (sk[w] == 0) zbij(w, w);
  }
  for (int i = 1; i <= n; i++) {
    for (int w : t1[i])
      if (sk[i] != sk[w]) {
        t3[sk[i]].push_back(sk[w]);
        t3[sk[w]].push_back(sk[i]);
      }
  }
  for (int i = 1; i <= n; i++)
    if (!o2[i] and sk[i] == i) {
      byla = false;
      suma = 0;
      dfs3(i);
      wyn += suma - 1 + byla;
    }
  printf("%d", wyn);
}
