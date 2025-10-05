#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5 + 10, MD = 1e9 + 7;
long long n, m, a[MX], ans, tmp, x, y, w, k, c[MX], dist[MX], par[MX], p[MX],
    t[MX];
bool mark[MX];
vector<pair<long long, long long>> adj2[MX], adj[MX];
pair<long long, pair<long long, pair<long long, long long>>> edge2[MX],
    edge[MX];
vector<long long> CN[MX];
int parent(int node) {
  if (p[node] == node) return node;
  return (p[node] = parent(p[node]));
}
int dsu(int u, int v) {
  u = parent(u);
  v = parent(v);
  if (adj[t[u]].size() < adj[t[v]].size()) swap(u, v);
  p[v] = u;
  return 0;
}
void dijkstra() {
  set<pair<int, int>> st;
  for (int i = 1; i <= n; i++) {
    dist[i] = 1e18;
    if (mark[i] == 1) continue;
    st.insert({dist[i], i});
  }
  for (int i = 0; i < k; i++) {
    dist[c[i]] = 0;
    st.insert({dist[c[i]], c[i]});
    par[c[i]] = c[i];
  }
  while (st.size() > 0) {
    int v = (st.begin())->second;
    st.erase({dist[v], v});
    for (auto u : adj2[v]) {
      if (dist[u.first] > dist[v] + u.second) {
        st.erase({dist[u.first], u.first});
        dist[u.first] = dist[v] + u.second;
        par[u.first] = par[v];
        st.insert({dist[u.first], u.first});
      }
    }
  }
  return;
}
int main() {
  scanf("%lld%lld", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%lld%lld%lld", &x, &y, &w);
    adj2[x].push_back({y, w});
    adj2[y].push_back({x, w});
    edge2[i] = {w, {x, {y, i}}};
  }
  scanf("%lld", &k);
  for (int i = 0; i < k; i++) {
    scanf("%lld", &c[i]);
    mark[c[i]] = 1;
  }
  dijkstra();
  for (int i = 0; i < m; i++) {
    int v = edge2[i].second.first, u = edge2[i].second.second.first;
    if (par[v] == par[u]) continue;
    adj[par[v]].push_back({par[u], edge2[i].first + dist[u] + dist[v]});
    adj[par[u]].push_back({par[v], edge2[i].first + dist[u] + dist[v]});
    edge[tmp++] = {edge2[i].first + dist[u] + dist[v],
                   {par[v], {par[u], tmp - 1}}};
  }
  sort(edge, edge + tmp);
  for (int i = 0; i < n; i++) p[i] = i;
  for (int i = 0; i < tmp; i++) {
    if (parent(edge[i].second.first) != parent(edge[i].second.second.first)) {
      ans += edge[i].first;
      dsu(edge[i].second.first, edge[i].second.second.first);
    }
  }
  printf("%lld", ans + dist[1]);
}
