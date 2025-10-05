#include <bits/stdc++.h>
using namespace std;
const long long INF = 1LL << 60;
int n, u;
long long r;
long long a[35], b[35], k[35], p[35];
long long ans;
void dfs(int cur, int used) {
  if ((u - cur) % 2 == 0) {
    long long ret = 0;
    for (int i = 1; i <= n; i++) ret += (long long)a[i] * k[i];
    ans = max(ans, ret);
  }
  if (cur == u) return;
  if (!used) {
    for (int i = 1; i <= n; i++) a[i] ^= b[i];
    dfs(cur + 1, 1);
    for (int i = 1; i <= n; i++) a[i] ^= b[i];
  }
  long long tmp[35];
  for (int i = 1; i <= n; i++) tmp[i] = a[p[i]] + r;
  for (int i = 1; i <= n; i++) swap(tmp[i], a[i]);
  dfs(cur + 1, 0);
  for (int i = 1; i <= n; i++) swap(tmp[i], a[i]);
}
int main() {
  while (cin >> n >> u >> r) {
    for (int i = 1; i <= n; i++) scanf("%I64d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%I64d", &b[i]);
    for (int i = 1; i <= n; i++) scanf("%I64d", &k[i]);
    for (int i = 1; i <= n; i++) scanf("%I64d", &p[i]);
    ans = -INF;
    dfs(0, 0);
    cout << ans << endl;
  }
  return 0;
}
