#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 400000 + 1;
const int INF = 1e9;
const int MOD = 1e9 + 7;
const long double PI = 3.141592653589793238462;
long long n, q;
long long stt[MAX_N], enn[MAX_N];
vector<long long> v[MAX_N];
pair<long long, pair<long long, long long> > all[MAX_N];
long long flag[2 * MAX_N], flag1[2 * MAX_N], MIN[2 * MAX_N];
long long t = 1;
long long edges[MAX_N];
long long find(long long node, long long st, long long en, long long low,
               long long high) {
  if (st == low && en == high) {
    return MIN[node];
  }
  long long mid = (st + en) / 2;
  if (high <= mid)
    return find(2 * node, st, mid, low, high) + flag[node];
  else if (low > mid)
    return find(2 * node + 1, mid + 1, en, low, high) + flag[node];
  else
    return min(find(2 * node, st, mid, low, mid),
               find(2 * node + 1, mid + 1, en, mid + 1, high)) +
           flag[node];
}
void add(long long node, long long st, long long en, long long low,
         long long high, long long val) {
  if (st == low && high == en) {
    flag[node] += val;
    MIN[node] += val;
    return;
  }
  long long mid = (st + en) / 2;
  if (high <= mid) {
    add(2 * node, st, mid, low, high, val);
    MIN[node] = min(MIN[2 * node], MIN[2 * node + 1]) + flag[node];
    return;
  } else if (low > mid) {
    add(2 * node + 1, mid + 1, en, low, high, val);
    MIN[node] = min(MIN[2 * node], MIN[2 * node + 1]) + flag[node];
    return;
  } else {
    add(2 * node, st, mid, low, mid, val);
    add(2 * node + 1, mid + 1, en, mid + 1, high, val);
    MIN[node] = min(MIN[2 * node], MIN[2 * node + 1]) + flag[node];
    return;
  }
}
void dfs(long long u) {
  stt[u] = t++;
  for (long long i = 0; i < v[u].size(); i++) dfs(v[u][i]);
  enn[u] = t - 1;
}
bool is_par(long long a, long long b) {
  if (stt[b] >= stt[a] && enn[b] <= enn[a]) return true;
  return false;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin >> n >> q;
  for (long long i = 1; i < n; i++) {
    cin >> all[i].first >> all[i].second.first >> all[i].second.second;
    v[all[i].first].push_back(all[i].second.first);
  }
  for (long long i = n; i < 2 * n - 1; i++) {
    cin >> all[i].first >> all[i].second.first >> all[i].second.second;
    edges[all[i].first] = all[i].second.second;
  }
  dfs(1);
  for (long long i = 1; i < n; i++) {
    long long u = all[i].second.first;
    add(1, 1, n, stt[u], enn[u], all[i].second.second);
  }
  for (int i = n; i < 2 * n - 1; i++) {
    long long u = all[i].first;
    add(1, 1, n, stt[u], stt[u], all[i].second.second);
  }
  for (long long i = 1; i <= q; i++) {
    long long a, b, c;
    cin >> a >> b >> c;
    if (a == 1) {
      if (b <= n - 1) {
        long long change = c - all[b].second.second;
        long long u = all[b].second.first;
        add(1, 1, n, stt[u], enn[u], change);
        all[b].second.second = c;
      } else {
        long long u = all[b].first;
        long long change = c - edges[u];
        add(1, 1, n, stt[u], stt[u], change);
        edges[all[b].first] = c;
      }
    } else {
      if (is_par(b, c)) {
        long long x = find(1, 1, n, stt[b], stt[b]);
        long long y = find(1, 1, n, stt[c], stt[c]);
        x -= edges[b];
        y -= edges[c];
        cout << y - x;
      } else {
        long long x = find(1, 1, n, stt[b], enn[b]);
        long long y = find(1, 1, n, stt[b], stt[b]);
        y -= edges[b];
        x -= y;
        long long z = find(1, 1, n, stt[c], stt[c]);
        z -= edges[c];
        cout << x + z;
      }
      cout << endl;
    }
  }
}
