#include <bits/stdc++.h>
using namespace std;
int n;
vector<pair<long long, long long> > sT, bT;
vector<long long> p;
pair<long long, long long> get(vector<pair<long long, long long> > &T, int i) {
  long long ans = T[i].first, ai = T[i].second;
  while (i) {
    if (T[i].first > ans) {
      ans = T[i].first;
      ai = T[i].second;
    }
    i -= i & (-i);
  }
  return {ans, ai};
}
void update(vector<pair<long long, long long> > &T, int i, long long j) {
  int I = i;
  while (i <= n) {
    if (T[i].first < j) {
      T[i].first = j;
      T[i].second = I;
    }
    i += i & (-i);
  }
}
int main() {
  ios::sync_with_stdio(false);
  int d;
  cin >> n >> d;
  sT.assign(n + 1, {0, 0});
  bT.assign(n + 1, {0, 0});
  p.assign(n + 1, 0);
  vector<pair<long long, long long> > a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].first;
    a[i].second = i;
  }
  sort(a.begin(), a.end());
  vector<pair<long long, long long> > dp(n + 1);
  dp[0] = make_pair(0, -1);
  for (int i = 1; i <= n; ++i) p[a[i].second] = i;
  vector<long long> P(n + 1);
  for (int i = 1; i <= n; ++i) P[i] = a[i].second;
  for (int i = 1; i <= n; ++i) {
    int v = p[i];
    long long f = 0, lst = -1;
    auto k =
        upper_bound(
            a.begin() + 1, a.end(), make_pair(a[v].first - d, a[v].second),
            [](pair<long long, long long> x, pair<long long, long long> y) {
              return x.first < y.first;
            }) -
        1;
    if (k > a.begin()) {
      pair<long long, long long> I = get(sT, k - a.begin());
      if (f < I.first) {
        f = I.first;
        lst = I.second;
      }
    }
    k = lower_bound(
            a.begin() + 1, a.end(), make_pair(a[v].first + d, a[v].second),
            [](pair<long long, long long> x, pair<long long, long long> y) {
              return x.first < y.first;
            }) -
        1;
    if (k < a.end()) {
      pair<long long, long long> I = get(bT, n - (k - a.begin()));
      if (f < I.first) {
        f = I.first;
        lst = n + 1 - I.second;
      }
    }
    update(sT, v, f + 1);
    update(bT, n - v + 1, f + 1);
    dp[i] = make_pair(f + 1, lst);
  }
  int mx = get(sT, n).second;
  cout << dp[P[mx]].first << endl;
  vector<long long> ans;
  mx = P[mx];
  while (mx != -1) {
    ans.push_back(mx);
    if (dp[mx].second != -1)
      mx = P[dp[mx].second];
    else
      mx = -1;
  }
  for (int i = ans.size() - 1; i + 1; --i) cout << ans[i] << ' ';
  cout << endl;
}
