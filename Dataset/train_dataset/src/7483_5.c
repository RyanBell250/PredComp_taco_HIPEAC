#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
const int maxL = 20;
const long long mod = 1e9 + 7;
const long double inf = 1e12;
const long long baze = 333;
long long flag[4 * maxn];
long long sum_data[4 * maxn];
long long min_data[4 * maxn];
long long n, ar[maxn], where[maxn];
void build(long long st = 0, long long en = n, long long id = 1) {
  if (en - st < 2) {
    min_data[id] = st;
    sum_data[id] = st;
    return;
  }
  long long mid = (st + en) >> 1;
  build(st, mid, id << 1);
  build(mid, en, id << 1 ^ 1);
  min_data[id] = min(min_data[id << 1], min_data[id << 1 ^ 1]);
  sum_data[id] = sum_data[id << 1] + sum_data[id << 1 ^ 1];
}
void relax_flag(const long long &st, const long long &en, const long long &id) {
  if (flag[id] == -1) return;
  sum_data[id] = (en - st) * flag[id];
  min_data[id] = flag[id];
  if (en - st > 1) {
    flag[id << 1] = flag[id];
    flag[id << 1 ^ 1] = flag[id];
  }
  flag[id] = -1;
}
void add(long long l, long long r, long long x, long long st = 0,
         long long en = n, long long id = 1) {
  relax_flag(st, en, id);
  if (l <= st && en <= r) {
    flag[id] = x;
    relax_flag(st, en, id);
    return;
  }
  if (r <= st || en <= l) return;
  long long mid = (st + en) >> 1;
  add(l, r, x, st, mid, id << 1);
  add(l, r, x, mid, en, id << 1 ^ 1);
  min_data[id] = min(min_data[id << 1], min_data[id << 1 ^ 1]);
  sum_data[id] = sum_data[id << 1] + sum_data[id << 1 ^ 1];
}
long long get(long long l, long long r, long long x, long long st = 0,
              long long en = n, long long id = 1) {
  relax_flag(st, en, id);
  if (l <= st && en <= r) {
    if (min_data[id] >= x)
      return -1;
    else if (en - st < 2)
      return en;
  }
  if (r <= st || en <= l) return -1;
  long long mid = (st + en) >> 1;
  long long ret = get(l, r, x, mid, en, id << 1 ^ 1);
  if (ret != -1) return ret;
  return get(l, r, x, st, mid, id << 1);
}
void helper(long long s, long long e) { return add(s, get(s, e, e), e); }
int32_t main() {
  ios_base::sync_with_stdio(false), cin.tie(), cout.tie();
  long long ans = 0;
  for (long long i = 0; i < 4 * maxn; i++) flag[i] = -1;
  cin >> n;
  for (long long i = 0; i < maxn; i++) where[i] = -1;
  for (long long i = 0; i < n; i++) cin >> ar[i], where[ar[i]] = i;
  build();
  for (long long i = maxn - 1; i > 0; i--) {
    vector<long long> vc;
    for (long long j = i; j < maxn; j += i)
      if (where[j] != -1) vc.push_back(where[j]);
    sort((vc).begin(), (vc).end());
    if (((long)(vc).size()) > 1) {
      helper(0, vc[((long)(vc).size()) - 2]);
      helper(vc[1] + 1, n);
      helper(vc[0] + 1, vc.back());
    }
    relax_flag(0, n, 1);
    ans += sum_data[1] - ((n * (n - 1)) >> 1);
  }
  cout << ans << endl;
}
