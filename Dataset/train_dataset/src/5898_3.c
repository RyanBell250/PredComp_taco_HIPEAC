#include <bits/stdc++.h>
const long long MOD = 1e9 + 7;
using pii = std::pair<long long, long long>;
using namespace std;
long long n, u, v, up[200005] = {0}, down[200005] = {0}, visited[200005] = {0};
vector<pii> adj[200005];
class DChoosingCapitalForTreeland {
 public:
  void solve(std::istream& in, std::ostream& out) {
    in >> n;
    for (long long i = (0); i < (n - 1); i++) {
      in >> u >> v;
      u--;
      v--;
      adj[u].push_back({v, 0});
      adj[v].push_back({u, 1});
    }
    coming(0);
    long long sumgoing = 0;
    for (long long i = (0); i < (n); i++) visited[i] = 0;
    going(0, 0);
    long long ans = 0;
    for (long long i = (0); i < (n); i++) ans = max(ans, up[i] + down[i]);
    out << n - 1 - ans << "\n";
    for (long long i = (0); i < (n); i++)
      if (up[i] + down[i] == ans) out << i + 1 << " ";
    out << "\n";
  }
  long long coming(long long x) {
    if (visited[x]) return 0;
    visited[x] = 1;
    for (auto v : adj[x])
      if (!visited[v.first]) up[x] += coming(v.first) + (!v.second);
    return up[x];
  }
  void going(long long x, long long cost) {
    if (visited[x]) return;
    visited[x] = 1;
    down[x] = cost;
    for (auto v : adj[x])
      if (!visited[v.first])
        going(v.first, cost + up[x] - up[v.first] + ((v.second) ? 1 : -1));
  }
};
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  DChoosingCapitalForTreeland solver;
  std::istream& in(std::cin);
  std::ostream& out(std::cout);
  solver.solve(in, out);
  return 0;
}
