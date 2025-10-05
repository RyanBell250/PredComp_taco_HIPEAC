#include <bits/stdc++.h>
using namespace std;
const int MAXN = (int)3e5 + 1000;
vector<int> v1[MAXN], store[MAXN];
int valid[MAXN];
int col[MAXN];
int n, m;
void DFS(int node, int par) {
  vector<int> notcolored;
  vector<int> colored;
  for (auto itr : store[node]) {
    if (col[itr] == 0) {
      notcolored.push_back(itr);
    } else {
      colored.push_back(itr);
    }
  }
  for (auto itr : colored) {
    valid[col[itr]] = true;
  }
  for (int i = 1;; i += 1) {
    if (notcolored.size() == 0) break;
    if (valid[i]) continue;
    col[notcolored.back()] = i;
    notcolored.pop_back();
  }
  for (auto itr : store[node]) {
    valid[col[itr]] = false;
  }
  for (auto itr : v1[node]) {
    if (itr == par) continue;
    DFS(itr, node);
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  int mex = 1;
  int ans = 0;
  for (int i = 1; i <= n; i += 1) {
    int howmany;
    cin >> howmany;
    ans = max(ans, howmany);
    if (howmany == mex) {
      mex = i;
    }
    while (howmany--) {
      int x;
      cin >> x;
      store[i].push_back(x);
    }
  }
  for (int j = 0; j < n - 1; j += 1) {
    int u, v;
    cin >> u >> v;
    v1[u].push_back(v);
    v1[v].push_back(u);
  }
  DFS(mex, -1);
  set<int> s1;
  for (int i = 1; i <= m; i += 1) {
    if (col[i] == 0) col[i] = 1;
    s1.insert(col[i]);
  }
  cout << s1.size() << endl;
  for (int i = 1; i <= m; i += 1) {
    cout << col[i] << " ";
  }
  return 0;
}
