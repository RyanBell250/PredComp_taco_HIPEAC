#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 200 * 1000;
vector<int> adjacencyList[MAX_N + 1];
void optimizeIO() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}
int main() {
  int n, color0 = 0, color1 = 0, v;
  bitset<MAX_N + 1> color;
  bitset<MAX_N + 1> mark;
  optimizeIO();
  cin >> n;
  for (int i = 1, v, u; i <= n - 1; ++i) {
    cin >> v >> u;
    adjacencyList[v].push_back(u);
    adjacencyList[u].push_back(v);
  }
  queue<int> Q;
  Q.push(1);
  while (not Q.empty()) {
    v = Q.front();
    for (auto u : adjacencyList[v])
      if (not mark[u]) {
        mark[u] = true;
        Q.push(u);
        color[u] = !color[v];
      }
    Q.pop();
  }
  for (int v = 1; v <= n; ++v)
    if (color[v] == 1)
      ++color1;
    else
      ++color0;
  cout << min(color0, color1) - 1 << endl;
  return 0;
}
