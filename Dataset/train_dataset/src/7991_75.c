#include <bits/stdc++.h>
using namespace std;
using namespace std;
#pragma GCC optimize("-O3")
using l = long;
using ll = long long;
using ld = long double;
const ll mod = 1000000007;
const ll INF = 1000000000000000000;
const ll rk = 256;
const ld PI = 3.141592653589793;
using namespace std;
ll inpt() {
  ll TemporaryVariable;
  cin >> TemporaryVariable;
  return TemporaryVariable;
}
vector<string> splitstring(string str) {
  stringstream ss(str);
  vector<string> s;
  string word;
  while (ss >> word) {
    s.push_back(word);
  }
  return s;
}
bool isPrime(int n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (int i = 5; i * i <= n; i = i + 6)
    if (n % i == 0 || n % (i + 2) == 0) return false;
  return true;
}
vector<int> SieveOfEratosthenes(int n) {
  vector<int> prm;
  bool prime[n + 1];
  memset(prime, true, sizeof(prime));
  for (int p = 2; p * p <= n; p++) {
    if (prime[p] == true) {
      for (int i = p * p; i <= n; i += p) prime[i] = false;
    }
  }
  for (int p = 2; p <= n; p++)
    if (prime[p]) prm.push_back(p);
  return prm;
}
ll gcd(ll a, ll b, ll x, ll y) {
  if (!a) return b;
  ll g = gcd(b % a, a, x, y);
  x = y - (b / a) * x;
  y = x;
  return g;
}
bool cmp(pair<ll, ll> p1, pair<ll, ll> p2) { return p1.second <= p2.second; }
ll power(int x, int i) {
  ll res = 1;
  for (__typeof(i) j = (0) - ((0) > (i)); j != (i) - ((0) > (i));
       j += 1 - 2 * ((0) > (i))) {
    res *= x;
  }
  return res;
}
vector<pair<ll, ll>> findSubArrays(vector<ll> arr, ll n) {
  unordered_map<ll, vector<ll>> map;
  vector<pair<ll, ll>> out;
  ll sum = 0;
  for (int i = 0; i < n; i++) {
    sum += arr[i];
    if (sum == 0) out.push_back(make_pair(0, i));
    if (map.find(sum) != map.end()) {
      vector<ll> vector = map[sum];
      for (auto it = vector.begin(); it != vector.end(); it++) {
        out.push_back(make_pair(*it + 1, i));
      }
    }
    map[sum].push_back(i);
  }
  return out;
}
int greatestDigit(ll n) {
  ll s = 0;
  while (n) {
    s = max(s, n % 10);
    n /= 10;
  }
  return s;
}
ll nCr[1001][1001];
void precompute() {
  for (__typeof(1001) i = (0) - ((0) > (1001)); i != (1001) - ((0) > (1001));
       i += 1 - 2 * ((0) > (1001))) {
    for (__typeof(1001) j = (0) - ((0) > (1001)); j != (1001) - ((0) > (1001));
         j += 1 - 2 * ((0) > (1001))) {
      nCr[i][j] = 0;
    }
    nCr[i][0] = 1;
  }
  for (__typeof(1001) i = (1) - ((1) > (1001)); i != (1001) - ((1) > (1001));
       i += 1 - 2 * ((1) > (1001))) {
    for (__typeof(i + 1) j = (1) - ((1) > (i + 1));
         j != (i + 1) - ((1) > (i + 1)); j += 1 - 2 * ((1) > (i + 1))) {
      nCr[i][j] = (nCr[i - 1][j] + nCr[i - 1][j - 1]) % mod;
    }
  }
}
ll fact(ll n) {
  if (n == 1) return 1;
  return n * fact(n - 1);
}
string LCSubStr(string X, string Y) {
  int m = X.length();
  int n = Y.length();
  int result = 0;
  int end;
  int len[2][n];
  int currRow = 0;
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0 || j == 0) {
        len[currRow][j] = 0;
      } else if (X[i - 1] == Y[j - 1]) {
        len[currRow][j] = len[1 - currRow][j - 1] + 1;
        if (len[currRow][j] > result) {
          result = len[currRow][j];
          end = i - 1;
        }
      } else {
        len[currRow][j] = 0;
      }
    }
    currRow = 1 - currRow;
  }
  if (result == 0) {
    return "";
  }
  return X.substr(end - result + 1, result);
}
void update(ll &x, ll y) {
  if (y == 0) return;
  if (x == 0) x = y;
  x = min(x, y);
}
ll ceil(ll a, ll b) {
  if (a % b) return a / b + 1;
  return a / b;
}
bitset<1000006> siv;
vector<ll> prime;
void sieve() {
  siv[0] = siv[1] = 1;
  prime.push_back(2);
  for (int i = 4; i <= 1000006; i += 2) siv[i] = 1;
  int sqrtn = sqrt(1000006);
  for (int i = 3; i <= sqrtn; i += 2) {
    if (siv[i] == 0) {
      for (int j = i * i; j <= 1000006; j += 2 * i) siv[j] = 1;
    }
  }
  for (int i = 3; i <= 1000006; i += 2)
    if (siv[i] == 0) prime.push_back(i);
}
int factorize(int n) {
  int ret = 1;
  int sqrtn = sqrt(n);
  for (int i = 0; i < prime.size() && prime[i] <= sqrtn; i++) {
    if (n % prime[i] == 0) {
      int cnt = 0;
      while (n % prime[i] == 0) {
        n /= prime[i];
        cnt++;
      }
      if (cnt % 2) ret *= prime[i];
      sqrtn = sqrt(n);
    }
  }
  if (n != 1) {
    ret *= n;
  }
  return ret;
}
ll exponentiation(ll base, ll exp) {
  if (exp == 0) return 1;
  if (exp == 1) return base % 1000000007;
  ll t = exponentiation(base, exp / 2);
  t = (t * t) % 1000000007;
  if (exp % 2 == 0)
    return t;
  else
    return ((base % 1000000007) * t) % 1000000007;
}
ll countDivisors(ll n) {
  ll cnt = 0;
  for (ll i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      if (n / i == i)
        cnt++;
      else
        cnt = cnt + 2;
    }
  }
  return cnt;
}
bool isSubSequence(string str1, string str2, int m, int n) {
  if (m == 0) return true;
  if (n == 0) return false;
  if (str1[m - 1] == str2[n - 1])
    return isSubSequence(str1, str2, m - 1, n - 1);
  return isSubSequence(str1, str2, m, n - 1);
}
bool hasdigit(ll num, ll d) {
  while (num) {
    if (num % 10 == d) return true;
    num /= 10;
  }
  return false;
}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll abs_(ll n) {
  if (n > 0) return n;
  return -n;
}
ll maxSubseq(vector<ll> vec, int n) {
  ll suffix = 0;
  for (ll i = n - 1; i >= 0; i--) {
    if (vec[i] == 1) {
      suffix++;
      vec[i] = suffix;
    }
  }
  ll res = 0;
  ll zero = 0;
  for (int i = 0; i < n; i++) {
    if (vec[i] == 0) zero++;
    if (vec[i] > 0) res = max(res, zero + vec[i]);
  }
  return max(res, zero);
}
vector<ll> g[200005], vis(200005);
ll mn = 0;
void dfs(ll s, int f) {
  vis[s] = f;
  for (auto it : g[s]) {
    if (!vis[it]) {
      vis[it] = s;
      if (s == 1) mn++;
      dfs(it, s);
    }
  }
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  ll n, m, u, v, d;
  cin >> n >> m >> d;
  ll mxd = 0, x = 0;
  for (__typeof(m) i = (0) - ((0) > (m)); i != (m) - ((0) > (m));
       i += 1 - 2 * ((0) > (m))) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  if (g[1].size() < d)
    cout << "NO\n";
  else {
    dfs(1, -1);
    if (mn > d)
      cout << "NO\n";
    else {
      for (auto it : g[1]) {
        if (mn < d && vis[it] != 1) {
          mn++;
          vis[it] = 1;
        }
      }
      cout << "YES\n";
      for (__typeof(n + 1) i = (2) - ((2) > (n + 1));
           i != (n + 1) - ((2) > (n + 1)); i += 1 - 2 * ((2) > (n + 1)))
        cout << i << " " << vis[i] << '\n';
    }
  }
  cerr << "Time : " << 1000 * (ld)clock() / (ld)CLOCKS_PER_SEC << "ms\n";
  ;
  return 0;
}
