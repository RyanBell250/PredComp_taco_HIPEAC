#include <bits/stdc++.h>
using namespace std;
const int MAX = 300010;
const long long INF = 0x3f3f3f3f3f3f3f;
int assoc_weight[MAX];
int assoc_edge[MAX];
map<pair<long long, long long>, long long> edge_map;
bool choose[MAX];
vector<long long> dijkstra(int source,
                           vector<vector<pair<long long, long long> > > g) {
  int n = (int)g.size();
  priority_queue<pair<long long, long long>,
                 vector<pair<long long, long long> >,
                 greater<pair<long long, long long> > >
      heap;
  vector<long long> dis = vector<long long>(n);
  fill(dis.begin(), dis.end(), INF);
  heap.push(make_pair(0, source));
  dis[source] = 0;
  while (!heap.empty()) {
    pair<long long, long long> p = heap.top();
    heap.pop();
    long long d = p.first;
    int x = p.second;
    if (d != dis[x]) {
      continue;
    }
    int m = (int)g[x].size();
    for (int i = 0; i < m; ++i) {
      long long y = g[x][i].first;
      long long val = (long long)g[x][i].second;
      if (dis[x] + val < dis[y]) {
        dis[y] = dis[x] + val;
        heap.push(make_pair(dis[y], y));
        assoc_weight[y] = val;
        int edge_num = edge_map[make_pair(x, i)];
        choose[assoc_edge[y]] = false;
        choose[edge_num] = true;
        assoc_edge[y] = edge_num;
      }
      if (dis[x] + val == dis[y]) {
        if (val < assoc_weight[y]) {
          assoc_weight[y] = val;
          int edge_num = edge_map[make_pair(x, i)];
          choose[assoc_edge[y]] = false;
          choose[edge_num] = true;
          assoc_edge[y] = edge_num;
        }
      }
    }
  }
  return dis;
}
vector<vector<pair<long long, long long> > > graph(MAX);
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    graph[a].push_back(make_pair(b, c));
    graph[b].push_back(make_pair(a, c));
    edge_map[make_pair(a, graph[a].size() - 1)] = i + 1;
    edge_map[make_pair(b, graph[b].size() - 1)] = i + 1;
  }
  int source;
  scanf("%d", &source);
  dijkstra(source, graph);
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += assoc_weight[i];
  }
  cout << ans << endl;
  for (int i = 0; i < MAX; ++i) {
    if (choose[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
  return 0;
}
