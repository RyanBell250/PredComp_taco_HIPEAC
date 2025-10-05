#include <bits/stdc++.h>
using namespace std;
template <class T>
bool setmax(T& _a, T _b) {
  if (_b > _a) {
    _a = _b;
    return true;
  }
  return false;
}
template <class T>
bool setmin(T& _a, T _b) {
  if (_b < _a) {
    _a = _b;
    return true;
  }
  return false;
}
template <class T>
T gcd(T _a, T _b) {
  return _b == 0 ? _a : gcd(_b, _a % _b);
}
int n, a[5010][3], s[5010][3], s2[5010][8];
int solve(pair<int, int> c0, pair<int, int> c1, pair<int, int> c2) {
  auto cal_score = [](int base_score, int t) {
    if (t == 0) return 0;
    if (t < 0) t = -t;
    return base_score * (250 - t) / 250;
  };
  for (int i = int(1); i <= int(n); ++i) {
    s[i][0] = cal_score(c0.first, a[i][0]);
    s[i][1] = cal_score(c1.first, a[i][1]);
    s[i][2] = cal_score(c2.first, a[i][2]);
    for (int m = int(0); m <= int((8) - 1); ++m) {
      s2[i][m] = 0;
      for (int p = int(0); p <= int((3) - 1); ++p)
        if ((m & (1 << p)) == 0 || a[i][p] > 0) s2[i][m] += s[i][p];
    }
  }
  int my_score = s2[1][0] + (c0.second + c1.second + c2.second) * 100;
  int threats = 0;
  static int f[99][99][99];
  memset(f, 0, sizeof(f));
  for (int i = int(2); i <= int(n); ++i) {
    if (s2[i][0] <= my_score) continue;
    ++threats;
    if (s2[i][7] > my_score) continue;
    for (int u0 = int(c0.second); u0 >= int(0); --u0)
      for (int u1 = int(c1.second); u1 >= int(0); --u1)
        for (int u2 = int(c2.second); u2 >= int(0); --u2) {
          for (int m = int(1); m <= int(7); ++m)
            if (s2[i][m] <= my_score) {
              setmax(f[u0 + !!(m & 1)][u1 + !!(m & 2)][u2 + !!(m & 4)],
                     f[u0][u1][u2] + 1);
            }
        }
  }
  int max_f = 0;
  for (int u0 = int(0); u0 <= int(c0.second); ++u0)
    for (int u1 = int(0); u1 <= int(c1.second); ++u1)
      for (int u2 = int(0); u2 <= int(c2.second); ++u2) {
        setmax(max_f, f[u0][u1][u2]);
      }
  return threats - max_f + 1;
}
int main() {
  scanf("%d", &n);
  for (int i = int(1); i <= int(n); ++i)
    for (int p = int(0); p <= int((3) - 1); ++p) scanf("%d", &a[i][p]);
  int possible_hacks = 0;
  for (int i = int(1); i <= int(n); ++i)
    for (int p = int(0); p <= int((3) - 1); ++p)
      if (a[i][p] < 0) ++possible_hacks;
  if (possible_hacks > 90) {
    printf("1\n");
    return 0;
  }
  vector<pair<int, int> > schema[3];
  for (int p = int(0); p <= int((3) - 1); ++p) {
    int lo = 0, hi = 0;
    for (int i = int(1); i <= int(n); ++i) {
      if (a[i][p] > 0) lo++, hi++;
      if (a[i][p] < 0) hi++;
    }
    auto base_score = [](int k) {
      if (n < 2 * k && 2 * k <= 2 * n) return 500;
      if (n < 4 * k && 4 * k <= 2 * n) return 1000;
      if (n < 8 * k && 8 * k <= 2 * n) return 1500;
      if (n < 16 * k && 16 * k <= 2 * n) return 2000;
      if (n < 32 * k && 32 * k <= 2 * n) return 2500;
      return 3000;
    };
    int la = -1;
    for (int k = int(lo); k <= int(hi); ++k) {
      int bs = base_score(k);
      if (bs != la) {
        la = bs;
        schema[p].push_back(make_pair(bs, hi - k));
      }
    }
  }
  int ans = 1 << 30;
  for (const auto& c0 : schema[0])
    for (const auto& c1 : schema[1])
      for (const auto& c2 : schema[2]) setmin(ans, solve(c0, c1, c2));
  printf("%d\n", ans);
  return 0;
}
