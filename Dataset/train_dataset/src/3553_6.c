#include <bits/stdc++.h>
using namespace std;
vector<int> adj[100005];
map<pair<int, int>, int> cost;
map<pair<int, int>, bool> done;
vector<int> cycle[45];
vector<int> par(100005);
bool seen[100005];
int cnt_cycles;
map<int, int> match;
long long int Ninv;
void init() {
  cnt_cycles = 0;
  return;
}
int dfs(int src) {
  seen[src] = true;
  int marker = 0;
  for (auto it : adj[src]) {
    if (!seen[it]) {
      par[it] = src;
      marker = max(marker, dfs(it));
    } else if ((seen[it]) and (it != par[src]) and
               (done.find(make_pair(it, src)) == done.end())) {
      marker = it;
      match[marker] = cnt_cycles;
      cnt_cycles++;
      cycle[match[marker]].push_back(it);
      done[make_pair(it, src)] = done[make_pair(src, it)] = 1;
    }
  }
  if (marker > 0) {
    cycle[match[marker]].push_back(src);
    if (marker == src) {
      marker = 0;
    }
  }
  return marker;
}
inline long long int add(long long int a, long long int b) {
  return (a + b) % 1000000007;
}
inline long long int sub(long long int a, long long int b) {
  return (a - b + 1000000007) % 1000000007;
}
inline long long int mul(long long int a, long long int b) {
  return (1ll * a * b) % 1000000007;
}
long long int power(long long int x, long long int n) {
  if (n == 1) return x;
  long long int temp = power(x, n / 2);
  temp = mul(temp, temp);
  if ((n % 2) == 1) {
    temp = mul(temp, x);
  }
  return temp;
}
long long int compinv() { return power(1 << 17, 1000000007 - 2); }
vector<long long int> FWHT(vector<long long int>& P, bool inverse = false) {
  int n = P.size();
  for (int len = 1; 2 * len <= n; len <<= 1) {
    for (int i = 0; i < n; i += 2 * len) {
      for (int j = 0; j < len; j++) {
        int u = P[i + j];
        int v = P[i + len + j];
        P[i + j] = add(u, v);
        P[i + len + j] = sub(u, v);
      }
    }
  }
  if (inverse) {
    for (int i = 0; i < n; i++) {
      P[i] = mul(P[i], Ninv);
    }
  }
  return P;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  init();
  int n, m;
  cin >> n >> m;
  int u, v, w;
  int total_weight = 0;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adj[u].push_back(v);
    adj[v].push_back(u);
    cost[make_pair(u, v)] = cost[make_pair(v, u)] = w;
    total_weight ^= w;
  }
  memset(seen, false, sizeof(seen));
  cnt_cycles = 0;
  par[1] = -1;
  dfs(1);
  Ninv = compinv();
  vector<long long int> arr, arr2;
  vector<long long int> prod(1 << 17, 1ll), prod2(1 << 17, 1ll);
  for (int i = 0; i < cnt_cycles; i++) {
    arr.clear();
    arr2.clear();
    arr.resize(1 << 17, 0ll);
    arr2.resize(1 << 17, 0ll);
    int len = cycle[i].size();
    for (int j = 0; j < len - 1; j++) {
      arr[cost[make_pair(cycle[i][j], cycle[i][j + 1])]]++;
      arr2[cost[make_pair(cycle[i][j], cycle[i][j + 1])]] = 1ll;
    }
    arr = FWHT(arr);
    arr2 = FWHT(arr2);
    for (int j = 0; j < (1 << 17); j++) {
      prod[j] = mul(prod[j], arr[j]);
      prod2[j] = mul(prod2[j], arr2[j]);
    }
  }
  prod = FWHT(prod, true);
  prod2 = FWHT(prod2, true);
  long long int minm = INT_MAX;
  long long int ways = 0ll;
  for (int i = 0; i < (1 << 17); i++) {
    long long int temp = total_weight ^ i;
    if (prod2[i]) {
      if (minm > temp) {
        minm = temp;
        ways = prod[i];
      } else if (minm == temp) {
        ways = add(ways, prod[i]);
      }
    }
  }
  cout << minm << " " << ways << endl;
  return 0;
}
