#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
const ll inf = 2e9 + 3;
const ll MAXINT = 1e9 + 7;
const double PI = 3.14159265358979323846;
const double pi = acos(-1);
const int N = 300005, M = 2 * N;
map<pair<int, int>, pair<int, bool>> ei;
queue<int> q;
vi adj[300005];
int cntRes = 0, n, k, d, visited[300005], vid;
void solve() {
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    visited[u] = vid;
    for (int i = 0; i < adj[u].size(); ++i) {
      int v = adj[u][i];
      if (visited[v] != vid) {
        q.push(v);
        visited[v] = vid;
        ei[{u, v}].second = true;
        ei[{v, u}].second = true;
        cntRes--;
      }
    }
  }
}
int main() {
  cin >> n >> k >> d;
  vid++;
  for (int i = 0; i < k; ++i) {
    int x;
    cin >> x;
    --x;
    q.push(x);
    visited[x] = vid;
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
    ei[{u, v}] = {i, false};
    ei[{v, u}] = {i, false};
  }
  cntRes = n - 1;
  solve();
  cout << cntRes << endl;
  for (auto it = ei.begin(); it != ei.end(); it++) {
    int u = it->first.first, v = it->first.second;
    if (!it->second.second) {
      cout << it->second.first << " ";
      ei[{v, u}].second = true;
    }
  }
  return 0;
}
