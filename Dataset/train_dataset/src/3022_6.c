#include <bits/stdc++.h>
using namespace std;
const long long int INF = 9223372036854775807;
const long long int mod = 998244353;
int MOD(int a, int b) {
  if (a > b)
    return a - b;
  else
    return b - a;
}
int max3(int a, int b, int c) { return max(c, max(a, b)); }
int min3(int a, int b, int c) { return min(a, min(b, c)); }
long long int power(long long int x, long long int y, long long int mod1) {
  long long int res = 1;
  while (y > 0) {
    if (y & 1) res = (res * x) % mod1;
    y = y >> 1;
    x = (x * x) % mod1;
  }
  return res;
}
long long int logg(long long int a) {
  long long int x = 0;
  while (a > 1) {
    x++;
    a /= 2;
  }
  return x;
}
long long int gcd(long long int a, long long int b) {
  if (a == 0) return b;
  return gcd(b % a, a);
}
long long int abso(long long int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}
long long int ceiling(long long int a, long long int b) {
  if (a % b == 0) {
    return a / b;
  } else {
    return a / b + 1;
  }
}
long long int modinv(long long int x, long long int p) {
  return power(x, p - 2, p);
}
long long int m, a, b;
vector<long long int> vis;
vector<long long int> dist;
vector<vector<long long int>> adj;
void dijkstra(int i) {
  dist[i] = 0;
  vis[i] = 0;
  set<pair<long long int, long long int>> pq;
  ;
  pq.insert(make_pair(0, 0));
  while (!pq.empty()) {
    auto cur = *pq.begin();
    pq.erase(pq.begin());
    vis[cur.second] = 1;
    dist[cur.second] = cur.first;
    for (int j = 0; j < adj[cur.second].size(); j++) {
      if (!vis[adj[cur.second][j]]) {
        pq.erase(make_pair(dist[adj[cur.second][j]], adj[cur.second][j]));
        dist[adj[cur.second][j]] = min(
            dist[adj[cur.second][j]],
            max(dist[cur.second], max((long long int)i, adj[cur.second][j])));
        pq.insert(make_pair(dist[adj[cur.second][j]], adj[cur.second][j]));
      }
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  cin >> m >> a >> b;
  adj.resize(min(m + 1, a + b + 1));
  vis.resize(min(m + 1, a + b + 1));
  dist.resize(min(m + 1, a + b + 1), 2 * a + 2 * b + 3);
  for (int i = 0; i <= min(m, a + b); i++) {
    if (i + a <= min(m, a + b)) {
      adj[i].push_back(i + a);
    }
    if (i - b >= 0) {
      adj[i].push_back(i - b);
    }
  }
  dijkstra(0);
  vector<int> solve(min(m + 1, a + b + 1));
  for (int i = 0; i < min(m + 1, a + b + 1); i++) {
    if (dist[i] < min(m + 1, a + b + 1)) {
      solve[dist[i]]++;
    }
  }
  long long int ans = solve[0];
  for (int i = 1; i < min(m + 1, a + b + 1); i++) {
    solve[i] += solve[i - 1];
    ans += solve[i];
  }
  if (m <= a + b) {
    cout << ans << endl;
  } else {
    ans -= solve[a + b];
    long long int num = m + 1 - (a + b);
    num = num / gcd(a, b);
    long long int x = (a + b) / gcd(a, b);
    x++;
    ans += gcd(a, b) * (x * num + (num) * (num - 1) / 2);
    ans += (x + num) * ((m + 1 - a - b) % (gcd(a, b)));
    cout << ans;
  }
}
