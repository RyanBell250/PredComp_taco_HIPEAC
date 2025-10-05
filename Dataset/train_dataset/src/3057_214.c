#include <bits/stdc++.h>
#pragma GCC optimize "trapv"
using namespace std;
template <class t1, class t2>
using pi = pair<t1, t2>;
template <class t>
using vi = vector<t>;
template <class t>
using vvi = vi<vi<t>>;
template <class t1, class t2>
using um = unordered_map<t1, t2>;
template <typename T>
void printv(vi<T> arr) {
  for (long long i = 0; i < arr.size(); ++i) cout << arr[i] << " ";
  cout << "\n";
}
template <class T>
inline void amin(T &x, const T &y) {
  if (y < x) x = y;
}
template <class T>
inline void amax(T &x, const T &y) {
  if (x < y) x = y;
}
class CubeTower {
 public:
  long long difference(int h, int n) {
    long long x = (h / n);
    long long y = h % n;
    long long ans = pow(x, 3) * n;
    ans -= pow(x, 3);
    ans += pow((x + y), 3);
    long long ans2 = (n - 1);
    h -= (n - 1);
    ans2 += pow(h, 3);
    return abs(ans2 - ans);
  }
};
struct jutsu {
  int a, b, c;
};
bool jutsu_compare(jutsu s1, jutsu s2) {
  if (s1.a == s2.a) {
    if (s1.b < s2.b)
      return true;
    else
      return false;
  } else {
    if (s1.a > s2.a)
      return true;
    else
      return false;
  }
}
long long ncr(long long n, long long k) {
  long long res = 1;
  if (k > n - k) k = n - k;
  for (long long i = 0; i < k; ++i) {
    res *= (n - i);
    res /= (i + 1);
  }
  return res;
}
vector<long long> prime(1000005, true);
vi<long long> primev;
void seive(void) {
  prime[1] = prime[0] = false;
  for (long long i = 2; i < 1000005; i++) {
    if (prime[i]) {
      primev.push_back(i);
      for (long long j = i * 2; j < 1000005; j += i) {
        prime[j] = 0;
      }
    }
  }
}
long long max(long long a, long long b) { return (a > b) ? a : b; }
long long min(long long a, long long b) { return (a < b) ? a : b; }
unsigned long long powerMod(long long x, long long y, long long p) {
  unsigned long long res = 1;
  x = x % p;
  while (y > 0) {
    if (y & 1) res = (res * x) % p;
    y = y >> 1;
    x = (x * x) % p;
  }
  return res;
}
unsigned long long modInverse(unsigned long long n, long long p) {
  return powerMod(n, p - 2, p);
}
unsigned long long nCrModPFermat(unsigned long long n, long long r,
                                 long long p) {
  if (n < r) return 0;
  if (r == 0) return 1;
  unsigned long long fac[n + 1];
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = (fac[i - 1] * i) % p;
  return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) %
         p;
}
void swap(long long &a, long long &b) {
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
}
long long index(vector<long long> arr, long long val) {
  auto it = find((arr).begin(), (arr).end(), val);
  if (it != arr.end()) {
    long long ind = it - arr.begin();
    return ind;
  } else
    return -1;
}
unsigned long long modFact(long long n) {
  const unsigned int M = 1000000007;
  unsigned long long f = 1;
  for (int i = 1; i <= n; i++) f = (f * i) % M;
  return f;
}
long long fact(long long x) {
  if (x == 1 || x == 0) return 1;
  return (x * (fact(x - 1)));
}
bool binarySearch(vector<long long> arr, long long val, long long i,
                  long long j) {
  if (i > j) return 0;
  if (arr[i + ((j - i) / 2)] == val) return 1;
  if (arr[i + ((j - i) / 2)] < val)
    return binarySearch(arr, val, i + ((j - i) / 2) + 1, j);
  return binarySearch(arr, val, i, i + ((j - i) / 2) - 1);
}
const int N = 2e5 + 5;
int tree[4 * N];
void build(int a[], int v, int tl, int tr) {
  if (tl == tr) {
    tree[v] = a[tl];
  } else {
    int tm = (tl + tr) / 2;
    build(a, v * 2, tl, tm);
    build(a, v * 2 + 1, tm + 1, tr);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
  }
}
void update(int v, int tl, int tr, int pos, int new_val) {
  if (tl == tr) {
    tree[v] = new_val;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm)
      update(v * 2, tl, tm, pos, new_val);
    else
      update(v * 2 + 1, tm + 1, tr, pos, new_val);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
  }
}
int sum(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (l == tl && r == tr) {
    return tree[v];
  }
  int tm = (tl + tr) / 2;
  return sum(v * 2, tl, tm, l, min(r, tm)) +
         sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}
void readSentence(void) {
  string s, t;
  getline(cin, s);
  stringstream sent(s);
  while (getline(sent, t, ' ')) {
    cout << t << " ";
  }
}
long long query(long long v, long long tl, long long tr, long long l,
                long long r, long long &to) {
  if (l > r) return 0;
  if (l == tl && r == tr) {
    to = min(to, tree[v]);
    return tree[v];
  }
  long long tm = (tl + tr) / 2;
  return (query(v * 2, tl, tm, l, min(r, tm), to) +
          query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, to));
}
void rangebuild(long long a[], long long v, long long tl, long long tr) {
  if (tl == tr) {
    tree[v] = a[tr];
  } else {
    long long tm = (tl + tr) / 2;
    rangebuild(a, v * 2, tl, tm);
    rangebuild(a, v * 2 + 1, tm + 1, tr);
    tree[v] = 0;
  }
}
void rangeupdate(long long v, long long tl, long long tr, long long l,
                 long long r, long long add) {
  if (l > r) return;
  if (l == tl && r == tr) {
    tree[v] += (add);
  } else {
    long long tm = (tl + tr) / 2;
    rangeupdate(v * 2, tl, tm, l, min(r, tm), add);
    rangeupdate(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, add);
  }
}
long long rangeget(long long v, long long tl, long long tr, long long pos) {
  if (tl == tr) return tree[v];
  long long tm = (tl + tr) / 2;
  if (pos <= tm)
    return tree[v] + rangeget(v * 2, tl, tm, pos);
  else
    return tree[v] + rangeget(v * 2 + 1, tm + 1, tr, pos);
}
void bitsetoperation(long long n) {
  string binary = bitset<14>(n).to_string();
  long long decimal = bitset<14>(binary).to_ulong();
}
int isSubstring(string s2, string s1) {
  int M = s1.length();
  int N = s2.length();
  for (int i = 0; i <= N - M; i++) {
    int j;
    for (j = 0; j < M; j++)
      if (s2[i + j] != s1[j]) break;
    if (j == M) return i;
  }
  return 0;
}
vi<long long> visited(200005, 0);
map<pi<long long, long long>, long long> mppdfs;
vi<long long> adj[200005];
void hinataVSsakura(void);
int main() {
  long long T = 1;
  cin >> T;
  long long k = 1;
  while (T--) {
    hinataVSsakura();
  }
  return 0;
}
void hinataVSsakura(void) {
  long long n, m;
  cin >> n >> m;
  vi<long long> arr(n, 0);
  vi<long long> brr(m, 0);
  for (long long i = 0; i < n; ++i) cin >> arr[i];
  for (long long i = 0; i < m; ++i) cin >> brr[i], brr[i]--;
  bool flg = true;
  while (flg) {
    bool flg1 = true;
    for (long long i = 0; i < m; ++i) {
      if (arr[brr[i]] > arr[brr[i] + 1]) {
        flg1 = false;
        swap(arr[brr[i]], arr[brr[i] + 1]);
      }
    }
    if (flg1) break;
  }
  for (long long i = 0; i < n - 1; ++i) {
    if (arr[i] > arr[i + 1]) {
      cout << "NO" << endl;
      return;
    }
  }
  cout << "YES" << endl;
}
