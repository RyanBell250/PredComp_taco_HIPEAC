#include <bits/stdc++.h>
using namespace std;
const long double PI = acos(-1.0l);
const long long MOD = 1e9 + 7;
bool debug = 0;
const int N = 1;
long long n, m, r, k;
long long w, h;
long long currn, currm;
long double ans = 0, falta = 0;
long long qualmenor(long long ii, long long val) {
  long long lo = 1, hi = currm;
  while (lo < hi) {
    long long mid = (lo + hi) / 2;
    if (ii * mid < val) {
      lo = mid + 1;
    } else
      hi = mid;
  }
  if (ii * lo >= val) return lo;
  return 0;
}
long long qnt(long long val) {
  long long ans = 0;
  for (int i = 1; i <= currn; i++) {
    long long j = qualmenor(i, val);
    if (j == 0) continue;
    long long nn;
    if (i == currn) {
      nn = h * (2 * (currm - j) + w);
    } else {
      nn = 4 * (currm - j);
      nn += 2 * w;
    }
    ans += nn;
  }
  return ans;
}
int main() {
  cin >> n >> m >> r >> k;
  if (m > n) swap(n, m);
  long long div = (n - r + 1) * (m - r + 1);
  if (r == 1) {
    ans = (long double)k / div;
    printf("%.10lf\n", (double)ans);
    return 0;
  }
  currn = 0, currm;
  ans = 0;
  if (n >= 2 * r + 1) {
    h = n - 2 * r + 2;
    currn = r;
  } else if (n == 2 * r) {
    currn = r;
    h = 2;
  } else {
    currn = n - r + 1;
    h = n - 2 * (n - r);
  }
  if (m >= 2 * r + 1) {
    w = m - 2 * r + 2;
    currm = r;
  } else if (m == 2 * r) {
    currm = r;
    w = 2;
  } else {
    currm = m - r + 1;
    w = m - 2 * (m - r);
  }
  long long lo = 1, hi = currn * currm + 1;
  while (lo < hi) {
    long long mid = (lo + hi) / 2;
    if (qnt(mid) >= k) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }
  lo--;
  long long falta = k;
  if (debug)
    cout << "lo"
         << " = " << (lo) << endl;
  map<long double, long long> mapa;
  for (int i = 1; i <= currn; i++) {
    for (int j = currm; j >= 0; j--) {
      long long ii = i;
      if (ii * j <= lo) break;
      long long nn = 4;
      if (ii == currn and j == currm)
        nn = w * h;
      else if (ii == currn)
        nn = 2 * h;
      else if (j == currm)
        nn = 2 * w;
      for (int k = 0; k < nn; k++) {
        ans += (long double)ii * j / div;
        mapa[(long double)ii * j / div]++;
        falta--;
      }
    }
  }
  for (int i = 0; i < falta; i++) {
    mapa[(long double)lo / div]++;
    ans += (long double)lo / div;
  }
  for (auto it : mapa) {
    if (debug)
      cout << "it"
           << ".fi=" << (it).first << " "
           << "it"
           << ".se=" << (it).second << endl;
  }
  printf("%.10lf\n", (double)ans);
  if (debug)
    cout << "h"
         << " = " << (h) << endl;
  if (debug)
    cout << "w"
         << " = " << (w) << endl;
  if (debug)
    cout << "h * w"
         << " = " << (h * w) << endl;
  if (debug)
    cout << "(h + 2) * (w)"
         << " = " << ((h + 2) * (w)) << endl;
  return 0;
}
