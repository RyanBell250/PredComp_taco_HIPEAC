#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
const int MAXN = 50000;
const int MAXVAL = 100000;
int n;
int a[MAXN];
int pmn[MAXVAL + 1];
vector<int> who[MAXVAL + 1];
vector<pair<int, int>> b;
vector<pair<int, int>> factorize(int x) {
  vector<pair<int, int>> ret;
  while (x > 1) {
    int p = pmn[x], cnt = 0;
    while (x % p == 0) x /= p, ++cnt;
    ret.push_back(make_pair(p, cnt));
  }
  return ret;
}
vector<int> getprimepowers(int x) {
  vector<pair<int, int>> factors = factorize(x);
  vector<int> ret;
  for (int i = (0); i < (((int)(factors).size())); ++i) {
    int cur = 1;
    for (int j = (0); j < (factors[i].second); ++j) cur *= factors[i].first;
    ret.push_back(cur);
  }
  return ret;
}
int findfirstmissing(const vector<int> &lst, int x) {
  int idx = lower_bound(lst.begin(), lst.end(), x) - lst.begin();
  assert(idx < ((int)(lst).size()) && lst[idx] == x);
  int l = 0, r = ((int)(lst).size()) - idx;
  while (l + 1 < r) {
    int m = l + (r - l) / 2;
    if (lst[idx + m] == lst[idx] + m)
      l = m;
    else
      r = m;
  }
  return lst[idx] + l + 1;
}
long long bfcalc(long long lim) {
  int l = 0, loff = 0, r = 0, roff = 0;
  int cnt = 0;
  long long sum = 0, ret = 0;
  while (l < ((int)(b).size())) {
    while (r < ((int)(b).size())) {
      if (roff >= b[r].second) {
        ++r, roff = 0;
        continue;
      }
      if (sum + b[r].first > lim) break;
      ++cnt;
      sum += b[r].first;
      ++roff;
    }
    ret += cnt;
    --cnt;
    sum -= b[l].first;
    ++loff;
    if (loff >= b[l].second) {
      ++l, loff = 0;
    }
  }
  printf("bfcalc(%lld)=%lld\n", lim, ret);
  return ret;
}
long long calc1(int cnt, long long x) { return cnt * x; }
long long calc2(int cnt, long long x) {
  return (long long)cnt * (x + x - cnt + 1) / 2;
}
long long calc3(int cnt, long long x, int a, int b) {
  assert(b != 0);
  long long ret = 0;
  int adiv = a / b;
  a %= b;
  ret += (long long)adiv * cnt * (cnt - 1) / 2;
  int xdiv = x / b;
  x %= b;
  ret += (long long)xdiv * cnt;
  if (a == 0) return ret;
  int zlim = (x + (cnt - 1) * a + 1) / b;
  ret += (long long)zlim * (cnt - 1) - calc3(zlim, b - x - 1, b, a);
  return ret;
}
long long calc(long long lim) {
  int l = 0, loff = 0, r = 0;
  int cnt = 0;
  long long sum = 0, ret = 0;
  while (l < ((int)(b).size())) {
    while (r < ((int)(b).size())) {
      int rem = b[r].second - (l == r ? loff : 0);
      if (sum + (long long)rem * b[r].first > lim) break;
      cnt += rem;
      sum += (long long)rem * b[r].first;
      ++r;
    }
    int nloff = b[l].second;
    if (r < ((int)(b).size())) {
      int rem = b[r].second - (l == r ? loff : 0);
      nloff = min((long long)nloff, loff + (sum + (long long)rem * b[r].first -
                                            lim + b[l].first - 1) /
                                               b[l].first);
    }
    if (l == r) {
      assert(cnt == 0 && sum == 0);
      ret += calc1(nloff - loff, lim / b[r].first);
      loff = nloff;
      if (nloff >= b[l].second) ++l, loff = 0, ++r;
    } else {
      if (r == ((int)(b).size())) {
        ret += calc2(nloff - loff, cnt);
      } else {
        ret += calc2(nloff - loff, cnt) +
               calc3(nloff - loff, lim - sum, b[l].first, b[r].first);
      }
      cnt -= nloff - loff;
      sum -= (long long)(nloff - loff) * b[l].first;
      loff = nloff;
      if (nloff >= b[l].second) ++l, loff = 0;
    }
  }
  return ret;
}
long long solve() {
  memset(pmn, -1, sizeof(pmn));
  for (int i = (2); i <= (MAXVAL); ++i)
    if (pmn[i] == -1) {
      for (int j = i; j <= MAXVAL; j += i)
        if (pmn[j] == -1) pmn[j] = i;
    }
  for (int i = (2); i <= (MAXVAL); ++i) who[i].clear();
  for (int i = (0); i < (n); ++i) {
    vector<pair<int, int>> cur = factorize(a[i]);
    for (int j = (0); j < (((int)(cur).size())); ++j) {
      int val = 1;
      for (int k = (1); k <= (cur[j].second); ++k) {
        val *= cur[j].first;
        who[val].push_back(i);
      }
    }
  }
  b.clear();
  for (int i = (0); i < (n); ++i) {
    int g = 0, at = i;
    while (at < n) {
      g = gcd(g, a[at]);
      vector<int> cur = getprimepowers(g);
      int to = n;
      for (int j = (0); j < (((int)(cur).size())); ++j) {
        int pp = cur[j];
        to = min(to, findfirstmissing(who[pp], at));
      }
      b.push_back(make_pair(g, to - at));
      at = to;
    }
  }
  {
    sort(b.begin(), b.end());
    int nb = 0;
    for (int i = (0); i < (((int)(b).size())); ++i)
      if (i != 0 && b[i].first == b[nb - 1].first)
        b[nb - 1].second += b[i].second;
      else
        b[nb++] = b[i];
    b.resize(nb);
    reverse(b.begin(), b.end());
  }
  int bcnt = 0;
  long long bsum = 0;
  for (int i = (0); i < (((int)(b).size())); ++i)
    bcnt += b[i].second, bsum += (long long)b[i].second * b[i].first;
  long long ccnt = (long long)bcnt * (bcnt + 1) / 2;
  long long need = (ccnt + 1) / 2;
  long long lo = 0, hi = bsum;
  while (lo + 1 < hi) {
    long long mi = lo + (hi - lo) / 2;
    long long have = calc(mi);
    if (have >= need)
      hi = mi;
    else
      lo = mi;
  }
  return hi;
}
void run() {
  scanf("%d", &n);
  for (int i = (0); i < (n); ++i) scanf("%d", &a[i]);
  printf("%lld\n", solve());
}
void stress() {
  for (int cnt = (1); cnt < (50); ++cnt)
    for (int b = (1); b <= (50); ++b)
      for (int a = (1); a <= (50); ++a)
        for (int x = (0); x <= (2 * b); ++x) {
          long long want = 0;
          for (int i = (0); i < (cnt); ++i) want += (x + i * a) / b;
          long long have = calc3(cnt, x, a, b);
          if (have == want) {
            if (x == 2 * b - 1) printf(".");
            continue;
          }
          printf("have=%lld want=%lld\n", have, want);
          printf("cnt=%d a=%d b=%d x=%d\n", cnt, a, b, x);
          exit(0);
        }
}
int main() {
  run();
  return 0;
}
