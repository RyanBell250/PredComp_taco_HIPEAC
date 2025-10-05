#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll Square(ll x) { return x * x; }
ll Divide(ll x, ll d) {
  d = min(d, x);
  ll group1 = d - x % d;
  ll group2 = x % d;
  ll res = group1 * Square(x / d) + group2 * Square(x / d + 1);
  return res;
}
int main() {
  ll i, j, k;
  ll n;
  cin >> n >> k;
  priority_queue<pair<ll, pair<ll, ll>>> pq;
  ll res = 0;
  for (i = 0; i < n; ++i) {
    cin >> j;
    res += Divide(j, 1);
    pq.push({Divide(j, 1) - Divide(j, 2), {j, 1}});
  }
  for (i = n; i < k; ++i) {
    pair<ll, ll> p = pq.top().second;
    res -= Divide(p.first, p.second);
    res += Divide(p.first, p.second + 1);
    pq.pop();
    pq.push({Divide(p.first, p.second + 1) - Divide(p.first, p.second + 2),
             {p.first, p.second + 1}});
  }
  cout << res << endl;
}
