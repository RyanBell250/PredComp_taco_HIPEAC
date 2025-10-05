#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const ll INF = 1e12 + 10;
const int MAXN = 1000006;
ll n, m, k, arr[MAXN], good, bad;
set<ll> divs;
ll __gcdll(ll a, ll b) {
  while (b != 0) {
    a = a % b;
    swap(a, b);
  }
  return a;
}
ll test(ll g) {
  if (g <= 1) return INF;
  ll curAns = 0;
  for (int i = 0; i < n; i++) {
    curAns += arr[i] >= g ? min(arr[i] % g, g - arr[i] % g) : g - arr[i];
  }
  return curAns;
}
void facto(ll n) {
  if (n == 0) return;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      divs.insert(i);
      while (n % i == 0) n /= i;
    }
  }
  if (n != 1) divs.insert(n);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  cin >> n;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    if (arr[i] & 1) ans++;
  }
  sort(arr, arr + n);
  const int numIT = 30;
  for (int it = 0; it < numIT; it++) {
    int id = rng() % n;
    facto(arr[id]);
    facto(arr[id] - 1);
    facto(arr[id] + 1);
  }
  for (ll d : divs) {
    ans = min((ll)ans, test(d));
  }
  cout << ans << endl;
}
