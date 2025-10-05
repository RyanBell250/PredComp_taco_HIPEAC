#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, d, sz = 0;
int a[N];
int vis[N];
bool poss = true;
vector<int> temp(N, 0);
set<int> st;
void dfs(int v) {
  if (!a[v]) return;
  vis[v]++;
  sz++;
  temp[v] = sz, st.insert(v);
  int nxt = (v - d + n) % n;
  if (vis[nxt]) {
    if (st.find(nxt) == st.end()) {
      sz += temp[nxt];
      return;
    } else {
      poss = false;
      return;
    }
  } else
    dfs(nxt);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int test = 1;
  cin >> test;
  while (test--) {
    cin >> n >> d;
    for (int i = 0; i < n; i++) cin >> a[i], vis[i] = 0, temp[i] = 0;
    poss = true;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (vis[i]) continue;
      sz = 0;
      st.clear();
      dfs(i);
      for (auto u : st) temp[u] = sz - temp[u] + 1;
    }
    for (int i = 0; i < n; i++) ans = max(ans, temp[i]);
    if (poss)
      cout << ans;
    else
      cout << -1;
    cout << "\n";
  }
  return 0;
}
