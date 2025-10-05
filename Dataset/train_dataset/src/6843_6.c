#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int Mod = 1e9 + 7;
const int SQ = 333;
const int sn = 555;
bool np[N + 5];
int ps[N + 5], pn = 0;
int cs[N + 5][3];
void xs() {
  np[1] = cs[1][0] = cs[1][1] = cs[1][2] = 1;
  for (int i = 2; i <= N; i++) {
    if (!np[i]) {
      cs[i][0] = cs[i][1] = 1;
      cs[i][2] = i;
      ps[++pn] = i;
    }
    for (int j = 1; j <= pn && i * ps[j] <= N; j++) {
      np[i * ps[j]] = 1;
      int cm = cs[i][0] * ps[j];
      if (cm < cs[i][1]) {
        cs[i * ps[j]][0] = cm;
        cs[i * ps[j]][1] = cs[i][1];
        cs[i * ps[j]][2] = cs[i][2];
      } else if (cm < cs[i][2]) {
        cs[i * ps[j]][0] = cs[i][1];
        cs[i * ps[j]][1] = cm;
        cs[i * ps[j]][2] = cs[i][2];
      } else {
        cs[i * ps[j]][0] = cs[i][1];
        cs[i * ps[j]][1] = cs[i][2];
        cs[i * ps[j]][2] = cm;
      }
      if (i % ps[j])
        ;
      else
        break;
    }
  }
}
int gcdd[sn + 3][sn + 3];
void smgcd() {
  for (int i = 0; i <= sn; i++) gcdd[i][0] = gcdd[0][i] = i;
  for (int i = 1; i <= sn; i++) {
    for (int j = 1; j <= i; j++) gcdd[i][j] = gcdd[j][i] = gcdd[i - j][j];
  }
}
void pre_gcd() {
  xs();
  smgcd();
}
int gcd(int a, int b) {
  int *x = cs[a], g = 1;
  for (int i = 0; i < 3; i++) {
    int d;
    if (x[i] <= sn)
      d = gcdd[x[i]][b % x[i]];
    else if (b % x[i])
      d = 1;
    else
      d = x[i];
    g *= d;
    b /= d;
  }
  return g;
}
vector<int> G[N];
int F[N];
int x[N];
int vs[N];
int cnt[N];
int solve(const vector<int> &dd) {
  int mx = 0;
  for (int x : dd) {
    vs[x] += 1;
    mx = max(x, mx);
  }
  int ans = 0;
  for (int i = mx; i >= 1; i--) {
    cnt[i] = 0;
    for (int k = i; k <= mx; k += i) {
      cnt[i] += vs[k];
    }
    cnt[i] = 1ll * cnt[i] * cnt[i] % Mod;
    for (int k = i + i; k <= mx; k += i) {
      cnt[i] -= cnt[k];
      if (cnt[i] >= Mod) cnt[i] -= Mod;
      if (cnt[i] < 0) cnt[i] += Mod;
    }
    ans += 1ll * cnt[i] * i % Mod;
    if (ans >= Mod) ans -= Mod;
  }
  for (int x : dd) {
    vs[x] = 0;
  }
  return ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  pre_gcd();
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      G[i].push_back(x[j]);
    }
  }
  int sum = 0;
  for (int i = N - 1; i >= 1; i--) {
    F[i] = 0;
    if (i > SQ) {
      for (int j = 0; j < G[i].size(); j++) {
        for (int d = 0; d < G[i].size(); d++) {
          F[i] += gcd(G[i][j], G[i][d]);
          if (F[i] >= Mod) F[i] -= Mod;
        }
      }
    } else {
      F[i] += solve(G[i]);
      if (F[i] >= Mod) F[i] -= Mod;
    }
    for (int j = i * 2; j < N; j += i) {
      F[i] -= F[j];
      if (F[i] >= Mod) F[i] -= Mod;
      if (F[i] < 0) F[i] += Mod;
    }
    sum += 1ll * F[i] * i % Mod;
    if (sum >= Mod) sum -= Mod;
  }
  cout << sum << endl;
}
