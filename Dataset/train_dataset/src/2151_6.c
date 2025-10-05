#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e6 + 5;
vector<int> adjList[N];
unordered_set<int> remaining;
bitset<N> inQ, nextToQ;
vector<int> ans;
void solve(int u) {
  remaining.erase(u);
  for (auto v : adjList[u]) {
    remaining.erase(v);
  }
  if (!remaining.empty()) {
    solve(*remaining.begin());
  }
  if (!nextToQ[u]) {
    inQ[u] = 1;
    nextToQ[u] = 1;
    for (auto v : adjList[u]) {
      nextToQ[v] = 1;
    }
    ans.push_back(u);
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adjList[u].push_back(v);
  }
  for (int i = 1; i <= n; i++) {
    remaining.insert(i);
  }
  solve(1);
  cout << ans.size() << endl;
  for (auto u : ans) {
    cout << u << " ";
  }
  cout << endl;
}
