#include <bits/stdc++.h>
using namespace std;
int const N = 2e6 + 20, mod = 1e9 + 7;
long long p, root[N], k, ans = 1;
int find(int v) { return root[v] < 0 ? v : root[v] = find(root[v]); }
void merge(int v, int u) {
  if ((u = find(u)) == (v = find(v))) return;
  if (root[u] < root[v]) swap(u, v);
  root[v] += root[u];
  root[u] = v;
  return;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> p >> k;
  fill(root, root + p, -1);
  if (!k) {
    for (int i = 1; i < p; i++) (ans *= p) %= mod;
    return cout << ans, 0;
  }
  for (int i = 1; i < p; i++) {
    merge(i, k * i % p);
  }
  for (int i = 1; i < p; i++) {
    if (find(i) == i) (ans *= p) %= mod;
  }
  int cnt = 0;
  for (int i = 0; i < p; i++) {
    cnt += (k * i % p == i);
  }
  (ans *= cnt) %= mod;
  return cout << ans, 0;
}
