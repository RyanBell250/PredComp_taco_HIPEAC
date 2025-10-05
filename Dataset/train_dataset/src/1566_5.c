#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:100000000")
long long gcd(long long a, long long b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}
long long lcm(long long a, long long b) { return (((a * b) / gcd(a, b))); }
long long phi(long long n) {
  long long result = n;
  for (long long i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      result -= result / i;
    }
  }
  if (n > 1) result -= result / n;
  return result;
}
long long binpow(long long a, long long n, long long c) {
  long long res = 1;
  while (n) {
    if (n & 1) res *= a;
    res %= c;
    a *= a;
    a %= c;
    n >>= 1;
  }
  res = (res + c) % c;
  return res;
}
void nxi(int& n) {
  bool min = 0;
  char c;
  n = 0;
  while ((c = getc(stdin)) && c <= 32)
    ;
  if (c == '-')
    min = 1;
  else
    n = c - 48;
  while ((c = getc(stdin)) && c > 32) n = (n << 3) + (n << 1) + c - 48;
  if (min) n = -n;
}
void prl(int n) {
  if (n == 0) {
    puts("0");
    return;
  }
  if (n < 0) {
    putchar('-');
    n = -n;
  }
  static int s[10];
  int top = 0;
  while (n > 0) s[top++] = n % 10, n /= 10;
  while (top--) putchar(s[top] + 48);
  puts("");
}
using namespace std;
const int nmax = 1000100;
int a[1000000], n;
int sum[1000000];
pair<int, int> t[2000000];
int top = 0, k;
int cnt[10000000];
vector<int> v[1001000], vv[1001000];
void build(int v, int tl, int tr) {
  if (tl == tr)
    t[v] = make_pair(a[tl], tl);
  else {
    int m = (tl + tr) >> 1;
    build((v << 1), tl, m);
    build(((v << 1) + 1), m + 1, tr);
    t[v] = max(t[(v << 1)], t[((v << 1) + 1)]);
  }
}
pair<int, int> get(int v, int tl, int tr, int l, int r) {
  if (tl == l && tr == r) return t[v];
  int m = (tl + tr) >> 1;
  if (r <= m) return get((v << 1), tl, m, l, r);
  if (l > m) return get(((v << 1) + 1), m + 1, tr, l, r);
  return max(get((v << 1), tl, m, l, m),
             get(((v << 1) + 1), m + 1, tr, m + 1, r));
}
void f(int l, int r) {
  if (l >= r) return;
  int pos = get(1, 1, n, l, r).second;
  int l1 = l;
  int r1 = pos - 1;
  int l2 = pos + 1;
  int r2 = r;
  f(l1, r1);
  f(l2, r2);
  if (pos == l) {
    int aa = (sum[pos - 1] + a[pos] + k + k) % k;
    v[pos + 1].push_back(aa);
    vv[r].push_back(aa);
    return;
  } else if (pos == r) {
    int aa = (sum[pos] - a[pos] + k + k) % k;
    v[l - 1].push_back(aa);
    vv[pos - 2].push_back(aa);
    return;
  }
  if (r1 - l1 < r2 - l2) {
    for (int i = l1 - 1; i < r1; i++) {
      int aa = (sum[i] + a[pos] + k + k) % k;
      v[pos].push_back(aa);
      vv[r2].push_back(aa);
    }
    int aa = (sum[r1] + a[pos] + k + k) % k;
    v[pos + 1].push_back(aa);
    vv[r2].push_back(aa);
  } else {
    for (int i = l2; i <= r2; i++) {
      int aa = (sum[i] - a[pos] + k + k) % k;
      v[l1 - 1].push_back(aa);
      vv[pos - 1].push_back(aa);
    }
    int aa = (sum[pos] - a[pos] + k + k) % k;
    v[l1 - 1].push_back(aa);
    vv[pos - 2].push_back(aa);
  }
}
int main() {
  srand(time(0));
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    a[i] = x;
  }
  build(1, 1, n);
  for (int i = 1; i <= n; i++) {
    a[i] %= k;
    sum[i] = sum[i - 1] + a[i];
    sum[i] %= k;
  }
  top = 1;
  f(1, n);
  long long ans = 0;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j < v[i].size(); j++) {
      ans -= cnt[v[i][j]];
    }
    cnt[sum[i]]++;
    for (int j = 0; j < vv[i].size(); j++) {
      ans += cnt[vv[i][j]];
    }
  }
  cout << ans;
  return 0;
}
