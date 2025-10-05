#include <bits/stdc++.h>
using namespace std;
const int N = 100, yzh = 1e9 + 7;
void read(int &x) {
  char ch;
  bool flag = 0;
  for (ch = getchar(); !isdigit(ch) && ((flag |= (ch == '-')) || 1);
       ch = getchar())
    ;
  for (x = 0; isdigit(ch); x = (x << 1) + (x << 3) + ch - 48, ch = getchar())
    ;
  x *= 1 - 2 * flag;
}
void print(long long x) {
  if (x > 9) print(x / 10);
  putchar(x % 10 + 48);
}
void write(long long x) {
  if (x < 0) putchar('-');
  print(((x) < 0 ? (-(x)) : (x)));
}
int n, x, g[N + 5];
int f[N + 5][N + 5][N + 5];
char ch[N + 5];
int quick_pow(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = 1ll * ans * a % yzh;
    b >>= 1, a = 1ll * a * a % yzh;
  }
  return ans;
}
void work() {
  read(n), read(x);
  scanf("%s", ch + 1);
  g[0] = g[1] = 1;
  for (int i = 2; i <= x; i++) g[i] = (g[i - 1] + g[i - 2]) % (yzh - 1);
  for (int i = 0; i <= x; i++) g[i] = quick_pow(2, g[i]);
  for (int i = 1; i <= n; i++)
    if (ch[i] == '0')
      f[i][i][0] = 1;
    else
      f[i][i][1] = 1;
  for (int i = 2; i <= x; i++) {
    for (int l = 1; l <= n; l++)
      for (int r = l; r <= n; r++) {
        if (r == n)
          (f[l][r][i] += 1ll * f[l][r][i - 1] * g[i - 2] % yzh) %= yzh;
        else
          (f[l][r][i] += f[l][r][i - 1]) %= yzh;
        if (l == 1)
          (f[l][r][i] += 1ll * f[l][r][i - 2] * g[i - 1] % yzh) %= yzh;
        else
          (f[l][r][i] += f[l][r][i - 2]) %= yzh;
        for (int k = l; k < r; k++)
          (f[l][r][i] += 1ll * f[l][k][i - 1] * f[k + 1][r][i - 2] % yzh) %=
              yzh;
      }
  }
  (write(f[1][n][x]), putchar('\n'));
}
int main() {
  work();
  return 0;
}
