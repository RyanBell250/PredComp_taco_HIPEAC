#include <bits/stdc++.h>
using namespace std;
pair<long double, long double> v[300], O, M;
int n, nr, K, nri, OK[300][300], nx[300], val1, val2, val;
long long A1, dt, A2, B1, B2, C1, C2, D[300][300], S, d1, d2, d3, d4;
long double xm, ym, SP;
long double aba(long double a) {
  if (a < 0) return -a;
  return a;
}
long double detu(long double ax, long double ay, long double bx, long double by,
                 long double cx, long double cy) {
  return ax * by + bx * cy + cx * ay - ay * bx - by * cx - cy * ax;
}
long double det(pair<long double, long double> a,
                pair<long double, long double> b,
                pair<long double, long double> c) {
  long double dt = a.first * b.second + b.first * c.second +
                   c.first * a.second - a.second * b.first -
                   b.second * c.first - c.second * a.first;
  if (dt > 0) dt = 1;
  if (dt < 0) dt = -1;
  return dt;
}
int intersect(pair<long double, long double> a,
              pair<long double, long double> b,
              pair<long double, long double> c,
              pair<long double, long double> d) {
  long double d1 = det(a, b, c), d2 = det(a, b, d), d3 = det(c, d, a),
              d4 = det(c, d, b);
  if (!d1 || !d2 || !d3 || !d4) return 0;
  if (d1 == -d2 && d3 == -d4)
    return 1;
  else
    return 0;
}
int inside(pair<long double, long double> M) {
  int c = 0;
  for (int i = 1; i <= n; ++i)
    if (det(O, M, v[i]) == 0 && v[i].first >= O.first &&
        v[i].first <= M.first && v[i].second >= min(O.second, M.second) &&
        v[i].second <= max(O.second, M.second))
      c = 1 - c;
  for (int i = 1; i <= n; ++i) {
    if (intersect(O, M, v[i], v[nx[i]])) c = 1 - c;
  }
  return c;
}
long long solve(int st, int dr) {
  if (nx[st] == dr || nx[nx[st]] == dr || st == dr) return 1;
  if (D[st][dr]) return D[st][dr];
  for (int i = nx[st]; i != dr; i = nx[i]) {
    if (OK[st][i] && OK[dr][i]) {
      D[st][dr] += solve(st, i) * solve(i, dr) % 1000000007;
      if (D[st][dr] >= 1000000007) D[st][dr] -= 1000000007;
    }
  }
  return D[st][dr];
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> v[i].first >> v[i].second;
  for (int i = 1; i <= n; ++i) nx[i] = i + 1;
  nx[n] = 1;
  O.first = -1000000007;
  O.second = -1000000009;
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j) {
      K = 1;
      OK[i][j] = OK[j][i] = 1;
      if (j == i + 1) continue;
      if (i == 1 && j == n) continue;
      for (int k = 1; k <= n; ++k) {
        if (i == k || j == k) continue;
        if (det(v[i], v[j], v[k]) == 0 &&
            v[k].first >= min(v[i].first, v[j].first) &&
            v[k].first <= max(v[i].first, v[j].first) &&
            v[k].second >= min(v[i].second, v[j].second) &&
            v[k].second <= max(v[i].second, v[j].second)) {
          K = 0;
          break;
        }
      }
      if (!K) {
        OK[i][j] = OK[j][i] = 0;
        continue;
      }
      for (int k = 1; k <= n; ++k) {
        if (intersect(v[i], v[j], v[k], v[nx[k]])) {
          K = 0;
          break;
        }
      }
      if (!K) {
        OK[i][j] = OK[j][i] = 0;
        continue;
      }
      M.first = v[i].first + v[j].first;
      M.second = v[i].second + v[j].second;
      M.first /= 2;
      M.second /= 2;
      O.first -= M.first - 1;
      O.second -= M.second;
      if (!inside(M)) OK[i][j] = OK[j][i] = 0;
      O.first += M.first;
      O.second += M.second;
    }
  cout << solve(1, n);
  return 0;
}
