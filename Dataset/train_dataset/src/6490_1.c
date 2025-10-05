#include <bits/stdc++.h>
using namespace std;
namespace Elaina {
template <class T>
inline T fab(T x) {
  return x < 0 ? -x : x;
}
template <class T>
inline void getmin(T& x, const T rhs) {
  x = min(x, rhs);
}
template <class T>
inline void getmax(T& x, const T rhs) {
  x = max(x, rhs);
}
template <class T>
inline T readin(T x) {
  x = 0;
  int f = 0;
  char c;
  while ((c = getchar()) < '0' || '9' < c)
    if (c == '-') f = 1;
  for (x = (c ^ 48); '0' <= (c = getchar()) && c <= '9';
       x = (x << 1) + (x << 3) + (c ^ 48))
    ;
  return f ? -x : x;
}
template <class T>
inline void writc(T x, char s = '\n') {
  static int fwri_sta[1005], fwri_ed = 0;
  if (x < 0) putchar('-'), x = -x;
  do fwri_sta[++fwri_ed] = x % 10, x /= 10;
  while (x);
  while (putchar(fwri_sta[fwri_ed--] ^ 48), fwri_ed)
    ;
  putchar(s);
}
}  
using namespace Elaina;
const int maxn = 3e5;
pair<long long, long long> seg[maxn + 5];
long long n;
long long K;
vector<pair<long long, long long> > cmd[maxn + 5];
set<pair<pair<long long, long long>, long long> > s;
inline void add(pair<pair<long long, long long>, long long> x) {
  set<pair<pair<long long, long long>, long long> >::iterator it =
      s.lower_bound(make_pair(make_pair(x.first.first, 0), 0));
  pair<pair<long long, long long>, long long> tmp;
  if (it != s.begin()) {
    --it;
    if (x.first.first < it->first.second) {
      tmp = *it;
      s.erase(it);
      s.insert(
          make_pair(make_pair(tmp.first.first, x.first.first), tmp.second));
      s.insert(
          make_pair(make_pair(x.first.first, tmp.first.second), tmp.second));
    }
  }
  it = s.lower_bound(make_pair(make_pair(x.first.second, 0), 0));
  if (it != s.begin()) {
    --it;
    if (x.first.second < it->first.second) {
      tmp = *it;
      s.erase(it);
      s.insert(
          make_pair(make_pair(tmp.first.first, x.first.second), tmp.second));
      s.insert(
          make_pair(make_pair(x.first.second, tmp.first.second), tmp.second));
    }
  }
  set<pair<pair<long long, long long>, long long> >::iterator
      op = s.lower_bound(make_pair(make_pair(x.first.first, 0), 0)),
      ed = op;
  long long pre = x.first.first;
  if (op != s.end() && op->first.second <= x.first.second) {
    do {
      long long L = ed->first.first, R = ed->first.second;
      if (pre < L) cmd[x.second].push_back(make_pair(1, L - pre));
      cmd[x.second].push_back(make_pair(ed->second + 1, R - L));
      pre = R, ++ed;
    } while (ed != s.end() && ed->first.second <= x.first.second);
    if (pre < x.first.second)
      cmd[x.second].push_back(make_pair(1, x.first.second - pre));
    s.erase(op, ed);
  } else
    cmd[x.second].push_back(make_pair(1, x.first.second - x.first.first));
  s.insert(x);
}
inline void input() {
  n = readin(1), K = readin(1);
  for (long long i = (1), i_end_ = (n); i <= i_end_; ++i) {
    seg[i].first = readin(1), seg[i].second = readin(1);
    add(make_pair(seg[i], i));
  }
}
long long f[maxn + 5];
inline long long counter(long long x) {
  for (long long i = (0), i_end_ = (n); i <= i_end_; ++i) f[i] = 0;
  long long l = 0;
  long long ret = 0;
  for (long long i = (1), i_end_ = (n); i <= i_end_; ++i) {
    for (pair<long long, long long> modi : cmd[i]) {
      long long p = modi.first, delta = modi.second;
      p = max(p, l);
      f[p] += delta, f[i + 1] -= delta;
    }
    while (l + 1 <= n && f[l + 1] + f[l] >= x) {
      f[l + 1] += f[l];
      ++l;
    }
    ret += l;
  }
  return ret;
}
inline long long getans(long long x) {
  for (long long i = (0), i_end_ = (n); i <= i_end_; ++i) f[i] = 0;
  long long l = 0;
  long long ret = 0, cur = 0;
  for (long long i = (1), i_end_ = (n); i <= i_end_; ++i) {
    for (pair<long long, long long> modi : cmd[i]) {
      long long p = modi.first, delta = modi.second;
      if (p <= l) cur += 1ll * delta * (l - p + 1);
      p = max(p, l);
      f[p] += delta, f[i + 1] -= delta;
    }
    while (l + 1 <= n && f[l + 1] + f[l] >= x) {
      f[l + 1] += f[l];
      cur += f[l + 1];
      ++l;
    }
    ret += cur;
  }
  return ret;
}
inline long long bisearch() {
  long long l = 1, r = 1e9, mid, ret, ans = -1;
  while (l <= r) {
    mid = (l + r) >> 1;
    ret = counter(mid);
    if (ret < K)
      r = mid - 1;
    else
      ans = mid, l = mid + 1;
  }
  return ans;
}
signed main() {
  input();
  long long ret = bisearch();
  writc(getans(ret + 1) - 1ll * ret * (counter(ret + 1) - K));
  return 0;
}
