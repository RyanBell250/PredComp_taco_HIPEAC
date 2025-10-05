#include <bits/stdc++.h>
using namespace std;
mt19937_64 rang(
    chrono::high_resolution_clock::now().time_since_epoch().count());
long long mpow(long long base, long long exp);
long long power(long long a, long long b);
const long long mod = 1000000007;
vector<int> g[300001];
struct node {
  set<int> s;
};
struct segTree {
  long long arr[2001];
  long long res[8003];
  int idx_mx[8003];
  int operation_arr[4003];
  int NO_OPERATION = 0;
  void init(int x, int lo, int hi) {
    if (lo == hi) {
      res[x] = arr[lo];
      return;
    }
    int mid = (lo + hi) / 2;
    init(2 * x, lo, mid);
    init(2 * x + 1, mid + 1, hi);
    update_point(x);
  }
  int merge_operation(int a, int b) {
    if (b != NO_OPERATION) return (b);
    return a;
  }
  long long merge_results(int a, int b) { return a + b; }
  void modify(int x, int lo, int hi, int l, int r, int op) {
    prop(x, lo, hi);
    if (lo >= l && hi <= r) {
      operation_arr[x] = merge_operation(operation_arr[x], op);
      return;
    }
    int mid = (lo + hi) / 2;
    if (lo > r || hi < l) return;
    modify(2 * x, lo, mid, l, r, op);
    modify(2 * x + 1, mid + 1, hi, l, r, op);
    update(x, lo, hi);
  }
  long long get_sum(int x, int lo, int hi, int l, int r) {
    if (lo >= l && hi <= r) return res[x];
    if (lo > r || hi < l) return 0;
    int mid = (lo + hi) / 2;
    return get_sum(2 * x, lo, mid, l, r) +
           get_sum(2 * x + 1, mid + 1, hi, l, r);
  }
  void point_modify(int x, int lo, int hi, int pos, long long val) {
    if (lo == hi) {
      res[x] = val;
      return;
    }
    int mid = (lo + hi) / 2;
    if (pos <= mid)
      point_modify(2 * x, lo, mid, pos, val);
    else
      point_modify(2 * x + 1, mid + 1, hi, pos, val);
    update_point(x);
  }
  long long max_query(int x, int lo, int hi, int l, int r) {
    if (lo >= l && hi <= r) return res[x];
    if (lo > r || hi < l) return LLONG_MIN;
    int mid = (lo + hi) / 2;
    return max(max_query(2 * x, lo, mid, l, r),
               max_query(2 * x + 1, mid + 1, hi, l, r));
  }
  long long get_idx(int x, int lo, int hi, long long v) {
    if (res[x] < v) return hi + 1;
    if (lo == hi) return lo;
    int mid = (lo + hi) / 2;
    if (res[2 * x] >= v)
      return get_idx(2 * x, lo, mid, v);
    else
      return get_idx(2 * x + 1, mid + 1, hi, v);
  }
  pair<int, int> mx_q(int x, int lo, int hi, int l, int r) {
    if (lo >= l && hi <= r) return {res[x], idx_mx[x]};
    if (lo > r || hi < l) return {LLONG_MIN, -1};
    int mid = (lo + hi) / 2;
    pair<int, int> p1 = mx_q(2 * x, lo, mid, l, r);
    pair<int, int> p2 = mx_q(2 * x + 1, mid + 1, hi, l, r);
    if (p1.first > p2.first) {
      return p1;
    } else
      return p2;
  }
  int mx_idx = -1;
  void max_idx(int x, int lo, int hi, int val, int r) {
    if (res[x] < val) return;
    int mid = (lo + hi) / 2;
    if (lo > r) return;
    if (hi == lo && res[x] == val) {
      mx_idx = lo;
      return;
    }
    max_idx(2 * x, lo, mid, val, r);
    max_idx(2 * x + 1, mid + 1, hi, val, r);
  }
  int get_max_idx(int x, int lo, int hi, int val, int r) {
    max_idx(x, lo, hi, val, r);
    return mx_idx;
  }
  void update_point(int x) { res[x] = res[2 * x] + res[2 * x + 1]; }
  int query(int x, int lo, int hi, int l, int r) {
    prop(x, lo, hi);
    if (lo >= l && hi <= r) return operate(res[x], operation_arr[x], lo, hi);
    if (lo > r || hi < l) return 0;
    int mid = (lo + hi) / 2;
    return merge_results(query(2 * x, lo, mid, l, r),
                         query(2 * x + 1, mid + 1, hi, l, r));
  }
  int kth_one(int x, int lo, int hi, int k) {
    if (lo == hi) return lo;
    int v1 = res[2 * x];
    int mid = (lo + hi) / 2;
    if (k <= v1)
      return kth_one(2 * x, lo, mid, k);
    else
      return kth_one(2 * x + 1, mid + 1, hi, k - v1);
  }
  long long point_query(int x, int lo, int hi, int p) {
    prop(x, lo, hi);
    if (lo == hi) return operate(res[x], operation_arr[x], lo, lo);
    int mid = (lo + hi) / 2;
    if (p <= mid)
      return point_query(2 * x, lo, mid, p);
    else
      return point_query(2 * x + 1, mid + 1, hi, p);
  }
  void prop(int x, int lo, int hi) {
    if (lo == hi) return;
    int mid = (hi + lo) / 2;
    long long len = mid - lo + 1;
    operation_arr[2 * x] =
        merge_operation(operation_arr[2 * x], operation_arr[x]);
    operation_arr[2 * x + 1] =
        merge_operation(operation_arr[2 * x + 1], operation_arr[x]);
    operation_arr[x] = NO_OPERATION;
    update(x, lo, hi);
  }
  int operate(int val, int operatr, int l, int r) {
    if (operatr == NO_OPERATION) return NO_OPERATION;
    return operatr;
  }
  void update(int x, int lo, int hi) {
    if (lo == hi) return;
    int mid = (lo + hi) / 2;
    long long len1 = (mid - lo + 1);
    long long len2 = (hi - mid);
    res[x] = merge_results(
        operate(res[2 * x], operation_arr[2 * x], lo, mid),
        operate(res[2 * x + 1], operation_arr[2 * x + 1], mid + 1, hi));
  }
};
struct FenwickTree {
  int arr[100];
  int n;
  void update(int i, int delta) {
    while (i <= n) {
      arr[i] += delta;
      i = i + (i & (-i));
    }
  }
  int sum(int i) {
    if (i == 0) return 0;
    int res = 0;
    while (i > 0) {
      res = res + arr[i];
      i -= (i & (-i));
    }
    return res;
  }
};
struct dsu {
  int par[1001];
  int size_set[1001];
  void init(int n) {
    for (int i = 0; i <= n; i++) par[i] = i, size_set[i] = 1;
  }
  int get_par(int u) {
    vector<int> temp;
    while (par[u] != u) {
      temp.push_back(u);
      u = par[u];
    }
    for (int i : temp) par[i] = u;
    return u;
  }
  void union_set(int a, int b) {
    a = get_par(a);
    b = get_par(b);
    if (a == b) return;
    if (size_set[a] < size_set[b]) {
      int temp = a;
      a = b;
      b = temp;
    }
    par[b] = a;
    size_set[a] += size_set[b];
  }
  int get_size(int u) {
    u = get_par(u);
    return size_set[u];
  }
};
int check(string s1, string s2) {
  int n1 = s1.size();
  int n2 = s2.size();
  s1 = '$' + s1;
  s2 = '$' + s2;
  int dp[n1 + 1][n2 + 1];
  for (int j = 0; j <= n2; j++) dp[0][j] = 0;
  dp[0][0] = 1;
  for (int i = 1; i <= n1; i++) {
    dp[i][0] = 0;
  }
  int i1 = 1;
  while (i1 <= n1 && s1[i1] == '*') {
    dp[i1][0] = 1;
    i1++;
  }
  int sum[n2 + 1];
  int s = 0;
  for (int i = 0; i <= n2; i++) s = s + dp[0][i], sum[i] = s;
  for (int i = 1; i <= n1; i++) {
    for (int j = 1; j <= n2; j++) {
      char c1 = s1[i];
      char c2 = s2[j];
      if (c1 == '*') {
        if (sum[j] > 0)
          dp[i][j] = 1;
        else
          dp[i][j] = 0;
      } else if (c1 == '?') {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        if (c1 != c2)
          dp[i][j] = 0;
        else
          dp[i][j] = dp[i - 1][j - 1];
      }
    }
    s = 0;
    for (int j = 0; j <= n2; j++) {
      s += dp[i][j];
      sum[j] = s;
    }
  }
  return dp[n1][n2];
}
long long gcd(long long a, long long b) {
  if (a == 0) return b;
  if (b == 0) return a;
  return gcd(b, a % b);
}
int a[100002];
int curr_ans = 0;
map<int, int> coded;
int code2[100001];
bool contains_dup(string s) {
  int cnt[26];
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < s.size(); i++) {
    cnt[s[i] - 'a']++;
    if (cnt[s[i] - 'a'] > 1) return 1;
  }
  return 0;
}
bool isOverflow(long long a, long long b) {
  if (a == 0 || b == 0) return false;
  if (a <= LLONG_MAX / b)
    return false;
  else
    return true;
}
bool isOverflow_add(long long a, long long b) {
  long long res = a + b;
  if (res - a == b && res - b == a) return 0;
  return 1;
}
long long fact(long long i) {
  long long res = 1;
  for (int j = 1; j <= i; j++) res *= j;
  return res;
}
long long f1[5001];
long long f2[5001];
void fct() {
  f1[0] = 1;
  f2[0] = mpow(1, mod - 2);
  for (long long i = 1; i <= 5000; i++) {
    f1[i] = (f1[i - 1] * i) % mod;
    f2[i] = mpow(f1[i], mod - 2);
  }
}
long long ncr(int n, int r) {
  long long res = f1[n];
  res = (res * f2[r]) % mod;
  res = (res * f2[n - r]) % mod;
  return res;
}
void solve() {
  int n, v;
  cin >> n >> v;
  vector<pair<long long, long long> > c, k;
  for (int i = 0; i < n; i++) {
    long long t, w;
    cin >> t >> w;
    if (t == 1)
      k.push_back({w, i});
    else
      c.push_back({w, i});
  }
  sort(c.begin(), c.end());
  sort(k.begin(), k.end());
  long long n1 = (int)c.size();
  long long n2 = (int)k.size();
  long long suf_sum1[n1 + 1];
  long long suf_sum2[n2 + 1];
  suf_sum1[n1] = 0;
  suf_sum2[n2] = 0;
  for (int i = n2 - 1; i >= 0; i--) suf_sum2[i] = suf_sum2[i + 1] + k[i].first;
  for (int i = n1 - 1; i >= 0; i--) suf_sum1[i] = suf_sum1[i + 1] + c[i].first;
  int cc = 0, ck = 0;
  long long res = 0;
  for (int cat = 0; cat <= n1; cat++) {
    long long vol_cat = cat * 2;
    long long vol_rem = v - vol_cat;
    long long kayak = min(n2, vol_rem);
    if (kayak < 0) break;
    long long sum = suf_sum1[n1 - cat] + suf_sum2[n2 - kayak];
    if (sum > res) {
      res = sum;
      cc = cat;
      ck = kayak;
    }
  }
  cout << res << "\n";
  vector<int> res_p;
  for (int i = n1 - cc; i < n1; i++) res_p.push_back(c[i].second);
  for (int i = n2 - ck; i < n2; i++) res_p.push_back(k[i].second);
  sort(res_p.begin(), res_p.end());
  for (int i : res_p) cout << i + 1 << " ";
  cout << "\n";
}
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());
  int t = 1;
  int t1 = 1;
  while (t--) {
    solve();
    t1++;
  }
  return 0;
}
long long mpow(long long base, long long exp) {
  base %= mod;
  long long result = 1;
  while (exp > 0) {
    if (exp & 1) result = ((long long)result * base) % mod;
    base = ((long long)base * base) % mod;
    exp >>= 1;
  }
  return result;
}
long long power(long long a, long long b) {
  long long res = 1;
  while (b > 0) {
    if (b % 2 == 0) {
      b /= 2;
      if (isOverflow(a, a)) return LLONG_MAX;
      a = a * a;
    } else {
      if (isOverflow(res, a)) return LLONG_MAX;
      res = res * a;
      b--;
    }
  }
  return res;
}
