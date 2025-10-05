#include <bits/stdc++.h>
using namespace std;
vector<bool> prime(1000005 + 1, true);
void sieve() {
  long long i, j, k;
  prime[0] = prime[1] = false;
  for (i = 2; i * i <= 1000005; i++) {
    if (prime[i]) {
      for (j = i * i; j <= 1000005; j += i) {
        prime[j] = false;
      }
    }
  }
}
long long power(long long a, long long b) {
  long long r = 1;
  while (b) {
    if (b % 2 == 1) r = r * a;
    b /= 2;
    a *= a;
  }
  return r;
}
long long power(long long a, long long b, long long m) {
  a = a % m;
  long long r = 1;
  while (b) {
    if (b % 2 == 1) r = (r * a) % m;
    b /= 2;
    a = (a * a) % m;
  }
  return r;
}
vector<long long> factors(long long n) {
  vector<long long> r;
  long long i, j;
  for (i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      r.push_back(i);
      if (n / i != i) r.push_back(n / i);
    }
  }
  return r;
}
long long gcd(long long a, long long b) {
  if (b > a) {
    long long t = a;
    a = b;
    b = t;
  }
  if (b == 0) return a;
  return gcd(b, a % b);
}
long long lcm(long long a, long long b) { return (a * b) / gcd(a, b); }
vector<bool> bvisited(1000005, false);
vector<vector<long long>> G(1000005);
vector<long long> bfs(long long s) {
  vector<long long> order;
  queue<long long> q;
  bvisited[s] = true;
  q.push(s);
  while (!q.empty()) {
    s = q.front();
    q.pop();
    order.push_back(s);
    for (auto x : G[s]) {
      if (!bvisited[x]) {
        bvisited[x] = true;
        q.push(x);
      }
    }
  }
  return order;
}
vector<bool> dvisited(1000005, false);
vector<long long> dfs(long long s) {
  vector<long long> order;
  stack<long long> q;
  q.push(s);
  while (!q.empty()) {
    long long v = q.top();
    q.pop();
    if (!dvisited[v]) {
      order.push_back(v);
      dvisited[v] = true;
    }
    for (long long i = 0; i < G[v].size(); i++) {
      if (!dvisited[G[v][i]]) {
        q.push(G[v][i]);
      }
    }
  }
  return order;
}
void print(pair<long long, long long> a) { cout << a.first << " " << a.second; }
void print(vector<long long> a) {
  for (auto x : a) cout << x << " ";
}
bool sortbysec(const pair<long long, long long>& a,
               const pair<long long, long long>& b) {
  return a.second < b.second;
}
vector<long long> an(1000005 + 1, -1);
void bfs(vector<long long> s, vector<long long> e, long long n) {
  vector<long long> d(n, INT64_MAX);
  queue<long long> q;
  for (auto x : s) {
    d[x] = 0;
    q.push(x);
  }
  while (!q.empty()) {
    long long v = q.front();
    q.pop();
    for (auto x : G[v]) {
      if (d[x] == INT64_MAX) {
        d[x] = d[v] + 1;
        q.push(x);
      }
    }
  }
  for (auto x : e) {
    if (d[x] != INT64_MAX) an[x] = d[x];
  }
}
void solve() {
  long long a, b, i, j, k, l;
  cin >> a >> b;
  long long x = 0;
  vector<long long> p, q;
  k = a;
  while (k > 0) {
    p.push_back(k % 2);
    k /= 2;
  }
  k = b;
  while (k > 0) {
    q.push_back(k % 2);
    k /= 2;
  }
  k = min(p.size(), q.size());
  for (i = 0; i < k; i++) {
    x = x << 1;
    if (p[i] == 1 && q[i] == 1) x |= 1;
  }
  k = ((a ^ x) + (b ^ x));
  k = min(k, ((a ^ b) + (b ^ b)));
  k = min(k, ((a ^ a) + (b ^ a)));
  cout << k << "\n";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}
