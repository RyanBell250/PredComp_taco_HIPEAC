#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
const long long inf = 0x3f3f3f3f3f3f3f3fll;
using namespace std;
vector<long long> vec;
void dfs(vector<vector<long long> >& graph, long long g[], long long v,
         long long graphno) {
  g[v] = graphno;
  vec.push_back(v);
  for (long long u = 0; u < graph[v].size(); u++) {
    if (g[graph[v][u]] != graphno) {
      dfs(graph, g, graph[v][u], graphno);
    }
  }
}
int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  long long v, e, i, a, b, j, graphno = 0, ans = 0;
  map<long long, long long> m;
  cin >> v >> e;
  long long g[v + 1];
  for (i = 0; i < v + 1; i++) g[i] = 0;
  vector<vector<long long> > graph(v + 1);
  for (i = 0; i < e; i++) {
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
    m[a]++;
    m[b]++;
  }
  for (i = 1; i < v + 1; i++) {
    if (g[i] != 0) continue;
    vec.clear();
    dfs(graph, g, i, i);
    long long count = 0;
    bool flag = true;
    for (j = 0; j < vec.size(); j++)
      if (m[vec[j]] != 2) flag = false;
    if (flag) ans++;
  }
  cout << ans << endl;
  return 0;
}
