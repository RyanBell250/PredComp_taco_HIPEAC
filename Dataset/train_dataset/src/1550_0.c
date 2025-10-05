#include <bits/stdc++.h>
using namespace std;
map<pair<long long, long long>, pair<long long, long long> > mp;
long long n;
pair<long long, long long> solve(pair<long long, long long> a) {
  if (a.second < 10)
    return make_pair(a.first || a.second, a.second - max(a.first, a.second));
  if (mp[a].first) return mp[a];
  long long ans = 0, p = 1;
  while (a.second >= p * 10) p *= 10;
  pair<long long, long long> b =
      solve(make_pair(max(a.first, a.second / p), a.second % p));
  ans += b.first;
  pair<long long, long long> c =
      solve(make_pair(a.first, a.second / p * p + b.second));
  ans += c.first;
  return mp[a] = make_pair(ans, c.second);
}
int main() {
  cin >> n;
  cout << solve(make_pair(0, n)).first;
  return 0;
}
