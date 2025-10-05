#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define INF (1LL << 60)
#define MOD 1000000007LL
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef pair<vll, vll> pvll;

struct state {
  ll d, v, p;

public:
  bool operator<(const state s) const { return d > s.d; }
};

const ll S = 0, G = 1;
ll N, M, A[100000], B[100000], C[100000];
vector< vector<pll> > E1(100000), E2(100000);

pvll dijkstra(vector< vector<pll> > &E, ll s) {
  vll dist(N, INF), cnt(N, 0);
  priority_queue<state> q;
  q.push((state) { 0, s, -1 });

  while(q.size()) {
    ll d = q.top().d, v = q.top().v, p = q.top().p;
    q.pop();

    if(dist[v] < d) continue;
    (cnt[v] += (p != -1 ? cnt[p] : 1)) %= MOD;

    if(dist[v] <= d) continue;

    dist[v] = d;
    REP(i, 0, E[v].size()) {
      ll u = E[v][i].first, c = E[v][i].second;
      if(dist[u] > d + c) q.push((state) { d + c, u, v });
    }
  }

  return pvll(dist, cnt);
}

int main(void) {
  cin >> N >> M;
  REP(i, 0, M) {
    cin >> A[i] >> B[i] >> C[i]; A[i]--; B[i]--;
    E1[A[i]].push_back(pll(B[i], C[i]));
    E2[B[i]].push_back(pll(A[i], C[i]));
  }

  pvll d1 = dijkstra(E1, S), d2 = dijkstra(E2, G);
  vll dist1 = d1.first, dist2 = d2.first, cnt1 = d1.second, cnt2 = d2.second;

  ll orgd = dist1[G];
  ll orgc = cnt1[G];

  REP(i, 0, M) {
    ll u = A[i], v = B[i], cost = C[i];
    if(dist1[v] + cost + dist2[u] < orgd) cout << "HAPPY" << endl;
    else if(dist1[u] + cost + dist2[v] == orgd && (cnt1[u] * cnt2[v]) % MOD == orgc) cout << "SAD" << endl;
    else cout << "SOSO" << endl;
  }
}