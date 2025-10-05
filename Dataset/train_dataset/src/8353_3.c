#include <bits/stdc++.h>
const int maxn = 51, mod = 1e9 + 7;
const int twoinv = (mod + 1) / 2;
template <int MOD>
struct ModInt {
  static const int Mod = MOD;
  unsigned x;
  ModInt() : x(0) {}
  ModInt(signed sig) {
    int sigt = sig % MOD;
    if (sigt < 0) sigt += MOD;
    x = sigt;
  }
  ModInt(signed long long sig) {
    int sigt = sig % MOD;
    if (sigt < 0) sigt += MOD;
    x = sigt;
  }
  int get() const { return (int)x; }
  ModInt &operator+=(ModInt that) {
    if ((x += that.x) >= MOD) x -= MOD;
    return *this;
  }
  ModInt &operator-=(ModInt that) {
    if ((x += MOD - that.x) >= MOD) x -= MOD;
    return *this;
  }
  ModInt &operator*=(ModInt that) {
    x = (unsigned long long)x * that.x % MOD;
    return *this;
  }
  ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
  ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
  ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
};
int n, d[maxn];
ModInt<mod> dp[2][maxn][maxn][maxn][maxn];
int ncr2(int x) { return (x * (x - 1)) / 2; }
int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cin >> n;
  for (int i = 0; i < n; i++) std::cin >> d[i];
  dp[0][d[0] == 2][d[0] == 3][d[1] == 2][d[1] == 3] = 1;
  for (int i = 2; i < n; i++)
    for (int a1 = 0; a1 <= n; a1++)
      for (int a2 = 0; a2 <= n - a1; a2++)
        for (int b1 = 0; b1 <= n - a1 - a2; b1++)
          for (int b2 = 0; b2 <= n - a1 - a2 - b1; b2++) {
            ModInt<mod> &cur = dp[i & 1][a1][a2][b1][b2];
            if (cur.get() == 0) continue;
            if (d[i] == 2) {
              if (a1) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 - 1][a2][b1 + 1][b2];
                nxt += cur * a1;
              }
              if (a2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 + 1][a2 - 1][b1 + 1][b2];
                nxt += cur * a2;
              }
              if (b1 && !a1 && !a2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][b1 - 1][b2][1][0];
                nxt += cur * b1;
              }
              if (b2 && !a1 && !a2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][b1 + 1][b2 - 1][1][0];
                nxt += cur * b2;
              }
              if (a1 && b1) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 - 1][a2][b1 - 1][b2];
                nxt += cur * a1 * b1;
              }
              if (a1 && b2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 - 1][a2][b1 + 1][b2 - 1];
                nxt += cur * a1 * b2;
              }
              if (a2 && b1) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 + 1][a2 - 1][b1 - 1][b2];
                nxt += cur * a2 * b1;
              }
              if (a2 && b2) {
                ModInt<mod> &nxt =
                    dp[(i + 1) & 1][a1 + 1][a2 - 1][b1 + 1][b2 - 1];
                nxt += cur * a2 * b2;
              }
            } else {
              if (a1) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 - 1][a2][b1][b2 + 1];
                nxt += cur * a1;
              }
              if (a2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 + 1][a2 - 1][b1][b2 + 1];
                nxt += cur * a2;
              }
              if (b1 && !a1 && !a2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][b1 - 1][b2][0][1];
                nxt += cur * b1;
              }
              if (b2 && !a1 && !a2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][b1 + 1][b2 - 1][0][1];
                nxt += cur * b2;
              }
              if (a1 && b1) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 - 1][a2][b1][b2];
                nxt += cur * a1 * b1;
              }
              if (a1 && b2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 - 1][a2][b1 + 2][b2 - 1];
                nxt += cur * a1 * b2;
              }
              if (a2 && b1) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 + 1][a2 - 1][b1][b2];
                nxt += cur * a2 * b1;
              }
              if (a2 && b2) {
                ModInt<mod> &nxt =
                    dp[(i + 1) & 1][a1 + 1][a2 - 1][b1 + 2][b2 - 1];
                nxt += cur * a2 * b2;
              }
              if (a1 && b1 && b2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 - 1][a2][b1][b2 - 1];
                nxt += cur * a1 * b1 * b2;
              }
              if (a1 && b1 >= 2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 - 1][a2][b1 - 2][b2];
                nxt += cur * a1 * ncr2(b1);
              }
              if (a1 && b2 >= 2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 - 1][a2][b1 + 2][b2 - 2];
                nxt += cur * a1 * ncr2(b2);
              }
              if (a2 && b1 && b2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 + 1][a2 - 1][b1][b2 - 1];
                nxt += cur * a2 * b1 * b2;
              }
              if (a2 && b1 >= 2) {
                ModInt<mod> &nxt = dp[(i + 1) & 1][a1 + 1][a2 - 1][b1 - 2][b2];
                nxt += cur * a2 * ncr2(b1);
              }
              if (a2 && b2 >= 2) {
                ModInt<mod> &nxt =
                    dp[(i + 1) & 1][a1 + 1][a2 - 1][b1 + 2][b2 - 2];
                nxt += cur * a2 * ncr2(b2);
              }
            }
            cur = 0;
          }
  std::cout << dp[n & 1][0][0][0][0].get() << std::endl;
  return 0;
}
