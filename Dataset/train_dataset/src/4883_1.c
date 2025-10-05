#include <bits/stdc++.h>
using namespace std;
const int maxn = 222222;
map<int, vector<pair<int, pair<int, int> > > > mapping;
vector<pair<int, pair<int, int> > > adj[maxn];
int findIndex(const vector<int> &a, int v) {
  return lower_bound(a.begin(), a.end(), v) - a.begin();
}
int dist[maxn];
bool inQ[maxn];
int from[maxn], fromID[maxn];
int main() {
  vector<int> positions;
  int n, L;
  scanf("%d%d", &n, &L);
  positions.push_back(0);
  positions.push_back(L);
  for (int i = 0; i < n; i++) {
    int xi, di, ti, pi;
    scanf("%d%d%d%d", &xi, &di, &ti, &pi);
    if (xi - pi < 0) {
      continue;
    }
    positions.push_back(xi - pi);
    positions.push_back(xi + di);
    mapping[xi - pi].push_back(make_pair(xi + di, make_pair(pi + ti, i)));
  }
  sort(positions.begin(), positions.end());
  positions.erase(unique(positions.begin(), positions.end()), positions.end());
  for (int i = 0; i < positions.size(); i++) {
    if (i + 1 < positions.size()) {
      adj[i].push_back(
          make_pair(i + 1, make_pair(positions[i + 1] - positions[i], -1)));
    }
    if (i - 1 >= 0) {
      adj[i].push_back(
          make_pair(i - 1, make_pair(positions[i] - positions[i - 1], -1)));
    }
    if (mapping.count(positions[i])) {
      for (__typeof((mapping[positions[i]]).begin()) it =
               (mapping[positions[i]]).begin();
           it != (mapping[positions[i]]).end(); ++it) {
        adj[i].push_back(
            make_pair(findIndex(positions, it->first), it->second));
      }
    }
  }
  int src = findIndex(positions, 0);
  int dest = findIndex(positions, L);
  priority_queue<pair<int, int> > Q;
  memset(dist, -1, sizeof(dist));
  inQ[src] = true;
  Q.push(make_pair(-0, src));
  dist[src] = 0;
  while (!Q.empty()) {
    int p = Q.top().second;
    Q.pop();
    inQ[p] = false;
    for (__typeof((adj[p]).begin()) it = (adj[p]).begin(); it != (adj[p]).end();
         ++it) {
      int q = it->first;
      int ndist = dist[p] + it->second.first;
      if (dist[q] < 0 || dist[q] > ndist) {
        dist[q] = ndist;
        from[q] = p;
        fromID[q] = it->second.second;
        if (!inQ[q]) {
          inQ[q] = true;
          Q.push(make_pair(-dist[q], q));
        }
      }
    }
  }
  printf("%d\n", dist[dest]);
  vector<int> ramps;
  int ptr = dest;
  while (ptr != src) {
    if (fromID[ptr] >= 0) {
      ramps.push_back(fromID[ptr]);
    }
    ptr = from[ptr];
  }
  reverse(ramps.begin(), ramps.end());
  printf("%d\n", ramps.size());
  for (int i = 0; i < ramps.size(); i++) {
    if (i > 0) {
      putchar(' ');
    }
    printf("%d\n", ramps[i] + 1);
  }
}
