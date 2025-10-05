#include <bits/stdc++.h>
using namespace std;
map<long long int, int> soinnsuu(long long int a) {
  map<long long int, int> ans;
  for (long long i = 2; i * i <= a; ++i) {
    while (a % i == 0) {
      ans[i]++;
      a /= i;
    }
  }
  if (a != 1) ans[a]++;
  return ans;
}
const int mod = 1000000007;
struct Mod {
 public:
  int num;
  Mod() : num(0) { ; }
  Mod(long long int n) : num((n % mod + mod) % mod) { ; }
  Mod(int n) : num((n % mod + mod) % mod) { ; }
  operator int() { return num; }
};
Mod operator+(const Mod a, const Mod b) { return Mod((a.num + b.num) % mod); }
Mod operator+(const long long int a, const Mod b) { return Mod(a) + b; }
Mod operator++(Mod &a) { return a + Mod(1); }
Mod operator-(const Mod a, const Mod b) {
  return Mod((mod + a.num - b.num) % mod);
}
Mod operator-(const long long int a, const Mod b) { return Mod(a) - b; }
Mod operator--(Mod &a) { return a - Mod(1); }
Mod operator*(const Mod a, const Mod b) {
  return Mod(((long long)a.num * b.num) % mod);
}
Mod operator*(const long long int a, const Mod b) { return Mod(a) * b; }
Mod operator+=(Mod &a, const Mod b) { return a = a + b; }
Mod operator+=(long long int &a, const Mod b) { return a = a + b; }
Mod operator-=(Mod &a, const Mod b) { return a = a - b; }
Mod operator-=(long long int &a, const Mod b) { return a = a - b; }
Mod operator*=(Mod &a, const Mod b) { return a = a * b; }
Mod operator*=(long long int &a, const Mod b) { return a = a * b; }
Mod operator^(const Mod a, const int n) {
  if (n == 0) return Mod(1);
  Mod res = (a * a) ^ (n / 2);
  if (n % 2) res = res * a;
  return res;
}
Mod inv(const Mod a) { return a ^ (mod - 2); }
Mod operator/(const Mod a, const Mod b) {
  assert(b.num != 0);
  return a * inv(b);
}
Mod operator/(const long long int a, const Mod b) {
  assert(b.num != 0);
  return Mod(a) * inv(b);
}
Mod operator/=(Mod &a, const Mod b) {
  assert(b.num != 0);
  return a = a * inv(b);
}
Mod fact[1024000], factinv[1024000];
void init() {
  fact[0] = Mod(1);
  factinv[0] = 1;
  for (int i = 0; i < 1024000 - 1; ++i) {
    fact[i + 1] = fact[i] * Mod(i + 1);
    factinv[i + 1] = factinv[i] / Mod(i + 1);
  }
}
Mod comb(const int a, const int b) {
  return fact[a] * factinv[b] * factinv[a - b];
}
using namespace std;
const int INF = 2147483647;
const long long int L_INF = 9223372036854775807;
struct Edge {
  int src, dst;
  int capacity;
  int cost;
  Edge(int src, int dst, int acap, int acost)
      : src(src), dst(dst), capacity(acap), cost(acost) {}
};
bool operator<(const Edge &e, const Edge &f) { return e.cost > f.cost; }
pair<int, int> minimumCostFlow(const vector<vector<Edge>> &ag, int s, int t) {
  vector<vector<Edge>> g(ag);
  for (int i = 0; i < ag.size(); ++i) {
    for (int j = 0; j < ag[i].size(); ++j) {
      int d = ag[i][j].dst;
      int s = ag[i][j].src;
      bool ok = false;
      for (int k = 0; k < ag[d].size(); ++k) {
        if (ag[d][k].src == s) {
          ok = true;
          break;
        }
      }
      if (!ok) {
        g[d].push_back(Edge(d, s, 0, ag[i][j].cost));
      }
    }
  }
  const int n = g.size();
  vector<vector<int>> capacity(n, vector<int>(n)), cost(n, vector<int>(n)),
      flow(n, vector<int>(n));
  for (int u = 0; u < (int)n; ++u)
    for (auto e = (g[u]).begin(); e != (g[u]).end(); ++e) {
      capacity[e->src][e->dst] += e->capacity;
      cost[e->src][e->dst] += e->cost;
    }
  pair<int, int> total;
  vector<int> h(n);
  for (int F = INF; F > 0;) {
    vector<int> d(n, INF);
    d[s] = 0;
    vector<int> p(n, -1);
    priority_queue<Edge> Q;
    for (Q.push(Edge(-2, s, 0, 0)); !Q.empty();) {
      Edge e = Q.top();
      Q.pop();
      if (p[e.dst] != -1) continue;
      p[e.dst] = e.src;
      for (auto f = (g[e.dst]).begin(); f != (g[e.dst]).end(); ++f)
        if ((capacity[f->src][f->dst] - flow[f->src][f->dst]) > 0) {
          if (d[f->dst] >
              d[f->src] + (cost[f->src][f->dst] + h[f->src] - h[f->dst])) {
            d[f->dst] =
                d[f->src] + (cost[f->src][f->dst] + h[f->src] - h[f->dst]);
            Q.push(Edge(f->src, f->dst, 0, d[f->dst]));
          }
        }
    }
    if (p[t] == -1) break;
    int f = F;
    for (int u = t; u != s; u = p[u])
      f = min(f, (capacity[p[u]][u] - flow[p[u]][u]));
    for (int u = t; u != s; u = p[u]) {
      total.first += f * cost[p[u]][u];
      flow[p[u]][u] += f;
      flow[u][p[u]] -= f;
    }
    F -= f;
    total.second += f;
    for (int u = 0; u < (int)n; ++u) h[u] += d[u];
  }
  return total;
}
long long int gcd(long long int l, long long int r) {
  assert(l > 0 && r > 0);
  if (l > r)
    return gcd(r, l);
  else {
    if (r % l) {
      return gcd(l, r % l);
    } else {
      return l;
    }
  }
}
int main() {
  int n;
  cin >> n;
  set<int> sos;
  vector<vector<Edge>> g;
  vector<map<long long, int>> mps;
  vector<int> nums;
  for (int i = 0; i < n; ++i) {
    long long int l;
    cin >> l;
    map<long long int, int> mp(soinnsuu(l));
    mps.push_back(mp);
    nums.push_back(l);
  }
  vector<int> costs;
  map<long long int, int> finalmap;
  for (int i = 0; i < n; ++i) {
    long long int l;
    cin >> l;
    costs.push_back(l);
  }
  for (int i = 0; i < n; ++i) {
    if (finalmap.count(nums[i])) {
      finalmap[nums[i]] = min(finalmap[nums[i]], costs[i]);
    } else {
      finalmap[nums[i]] = costs[i];
    }
    for (auto it = finalmap.begin(); it != finalmap.end(); ++it) {
      long long int agcd = gcd(it->first, nums[i]);
      if (finalmap.count(agcd)) {
        finalmap[agcd] = min(finalmap[agcd], it->second + costs[i]);
      } else {
        finalmap[agcd] = it->second + costs[i];
      }
    }
  }
  int ans = finalmap[1];
  if (ans) {
    cout << ans << endl;
  } else {
    cout << -1 << endl;
  }
  return 0;
}
