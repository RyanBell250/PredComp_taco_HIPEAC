#include <bits/stdc++.h>
using namespace std;
int n, m;
long long p[128][128];
long long l[128][128], g[128][128];
long long v[128];
template <class _T>
_T gcd(_T a, _T b) {
  return a ? gcd(b % a, a) : b;
}
template <class _T>
_T lcm(_T a, _T b) {
  return a * b / gcd(a, b);
}
bool solve(int u) {
  for (int i = 0; i < n; i++) {
    if (p[u][i] != -1 && v[i] == -1) {
      if (p[u][i] % v[u]) return false;
      v[i] = p[u][i] / v[u];
      if (l[u][i] != lcm(v[u], v[i]) || g[u][i] != gcd(v[u], v[i]) || !solve(i))
        return false;
    }
  }
  return true;
}
void unmark(int u) {
  v[u] = -1;
  for (int i = 0; i < n; i++)
    if (p[u][i] != -1 && v[i] != -1) unmark(i);
}
int main(void) {
  scanf("%d %d", &n, &m);
  memset(p, -1, sizeof(p));
  memset(v, -1, sizeof(v));
  while (m--) {
    int a, b;
    scanf("%d %d", &a, &b), a--, b--;
    cin >> g[a][b] >> l[a][b];
    g[b][a] = g[a][b];
    l[b][a] = l[a][b];
    p[a][b] = p[b][a] = l[a][b] * g[a][b];
  }
  for (int i = 0; i < n; i++) {
    if (v[i] != -1) continue;
    int x;
    for (x = 1; x <= 1000000; x++) {
      v[i] = x;
      if (solve(i))
        break;
      else
        unmark(i);
    }
    if (x > 1000000) {
      printf("NO\n");
      return 0;
    }
  }
  for (int i = 0; i < n; i++) {
    if (v[i] == -1) {
      printf("NO\n");
      return 0;
    }
  }
  printf("YES\n");
  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    cout << v[i];
  }
  printf("\n");
  return 0;
}
