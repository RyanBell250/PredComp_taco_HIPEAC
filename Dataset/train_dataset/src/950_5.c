#include <bits/stdc++.h>
using namespace std;
const int inf = (int)1e9 + 7;
const long long linf = (long long)1e18;
const double pi = (double)3.14159265358979323846;
template <class T>
T abs(T k) {
  return k >= 0 ? k : -k;
}
template <class T>
T sqr(T n) {
  return n * n;
}
template <class T>
T gcd(T a, T b) {
  return b ? gcd(b, a % b) : a;
}
template <class T>
T mod(T a, T b) {
  return (a % b + b) % b;
}
template <class T>
void mode(T &a, T b) {
  a = mod(a, b);
}
template <class T>
void maxe(T &a, T b) {
  a = max(a, b);
}
template <class T>
void mine(T &a, T b) {
  a = min(a, b);
}
void fileio_in_out() {
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
}
void fileio_txt() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
}
int n, m, ans;
int a[3];
int f[333][333];
int dfs(int x, int y) {
  if (f[x][y] != -1) return f[x][y];
  for (int i = 1; i <= max(x, y); i++) {
    if (x >= i && !dfs(x - i, y)) return f[x][y] = 1;
    if (y >= i && !dfs(x, y - i)) return f[x][y] = 1;
    if (x >= i && y >= i && !dfs(x - i, y - i)) return f[x][y] = 1;
  }
  return f[x][y] = 0;
}
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  memset(f, -1, sizeof(f));
  ans = (n == 1) ? (a[0] > 0)
                 : ((n == 3) ? ((a[0] ^ a[1] ^ a[2]) != 0) : dfs(a[0], a[1]));
  printf("Bit%s\n", ans ? "LGM" : "Aryo");
  return 0;
}
