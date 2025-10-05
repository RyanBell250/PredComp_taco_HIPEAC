#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
template <class C>
void mini(C &a4, C b4) {
  a4 = min(a4, b4);
}
template <class C>
void maxi(C &a4, C b4) {
  a4 = max(a4, b4);
}
template <class TH>
void _dbg(const char *sdbg, TH h) {
  cerr << sdbg << '=' << h << endl;
}
template <class TH, class... TA>
void _dbg(const char *sdbg, TH h, TA... a) {
  while (*sdbg != ',') cerr << *sdbg++;
  cerr << '=' << h << ',';
  _dbg(sdbg + 1, a...);
}
template <class T>
ostream &operator<<(ostream &os, vector<T> V) {
  os << "[";
  for (auto vv : V) os << vv << ",";
  return os << "]";
}
template <class L, class R>
ostream &operator<<(ostream &os, pair<L, R> P) {
  return os << "(" << P.first << "," << P.second << ")";
}
const long long MAX = 200100;
set<long long> gd[MAX];
struct node {
  long long cal;
  long long naj;
  long long najpref;
  long long najsuf;
  long long pref;
  long long suf;
  bool ok;
} dp[1 << 19];
long long t[MAX];
long long n, nn, q;
void ak(long long v) {
  long long sze = 1;
  while (v != 1) {
    v /= 2;
    dp[v].naj = max(dp[v * 2].naj, dp[v * 2 + 1].naj);
    dp[v].cal = 0;
    dp[v].ok = 0;
    dp[v].najpref = 0;
    dp[v].najsuf = 0;
    dp[v].pref = dp[v * 2].pref;
    dp[v].suf = dp[v * 2 + 1].suf;
    if (dp[v * 2].suf > sze) {
      maxi(dp[v].suf, dp[v * 2].suf - sze);
      maxi(dp[v].najsuf, max(dp[v * 2 + 1].naj, dp[v * 2].najsuf));
    } else {
      if (dp[v * 2 + 1].pref <= sze) {
        if (dp[v * 2].ok && dp[v * 2 + 1].ok) {
          dp[v].cal += max(dp[v * 2 + 1].najpref, dp[v * 2].najsuf);
        }
        if (!dp[v * 2].ok) {
          maxi(dp[v].najpref, max(dp[v * 2 + 1].najpref, dp[v * 2].najsuf));
        }
        if (!dp[v * 2 + 1].ok) {
          maxi(dp[v].najsuf, max(dp[v * 2 + 1].najpref, dp[v * 2].najsuf));
        }
      }
      dp[v].ok |= dp[v * 2 + 1].ok;
      dp[v].cal += dp[v * 2 + 1].cal;
      maxi(dp[v].najsuf, dp[v * 2 + 1].najsuf);
    }
    if (dp[v * 2 + 1].pref > sze) {
      maxi(dp[v].pref, dp[v * 2 + 1].pref - sze);
      maxi(dp[v].najpref, max(dp[v * 2].naj, dp[v * 2 + 1].najpref));
    } else {
      dp[v].ok |= dp[v * 2].ok;
      dp[v].cal += dp[v * 2].cal;
      maxi(dp[v].najpref, dp[v * 2].najpref);
    }
    (v, dp[v].cal, dp[v].naj, dp[v].najpref, dp[v].najsuf, dp[v].pref,
     dp[v].suf, dp[v].ok);
    sze *= 2;
  }
}
void dodaj(long long i) {
  long long kr = ((long long)(gd[i]).size());
  if (!kr) return;
  long long a = *gd[i].begin();
  if (kr == 1) {
    dp[a + nn] = {1, 1, 0, 0, 0, 0, true};
    ak(a + nn);
  } else {
    long long b = *gd[i].rbegin();
    dp[a + nn] = {0, kr, 0, kr, 0, b - a, true};
    dp[b + nn] = {0, kr, kr, 0, b - a, 0, true};
    ak(a + nn);
    ak(b + nn);
  }
}
void us(long long i) {
  node empty = {0, 0, 0, 0, 0, 0, false};
  long long kr = ((long long)(gd[i]).size());
  if (!kr) return;
  long long a = *gd[i].begin();
  if (kr == 1) {
    dp[a + nn] = empty;
    ak(a + nn);
  } else {
    long long b = *gd[i].rbegin();
    dp[a + nn] = empty;
    dp[b + nn] = empty;
    ak(a + nn);
    ak(b + nn);
  }
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(11);
  if (0) cout << fixed << setprecision(6);
  cin >> n >> q;
  nn = 1;
  while (nn <= n) nn *= 2;
  for (long long i = (0); i <= ((long long)(n)-1); i++) {
    cin >> t[i];
    gd[t[i]].insert(i);
  }
  for (long long i = (0); i <= ((long long)(MAX)-1); i++) dodaj(i);
  cout << n - dp[1].cal << "\n";
  for (long long i = (0); i <= ((long long)(q)-1); i++) {
    long long a, v;
    cin >> a >> v;
    a--;
    us(t[a]);
    gd[t[a]].erase(a);
    dodaj(t[a]);
    us(v);
    t[a] = v;
    gd[v].insert(a);
    dodaj(v);
    cout << n - dp[1].cal << "\n";
  }
}
