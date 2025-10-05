#include <bits/stdc++.h>
using namespace std;
template <class T>
inline T min(T &a, T &b) {
  return a < b ? a : b;
}
template <class T>
inline T max(T &a, T &b) {
  return a > b ? a : b;
}
template <class T>
void read(T &x) {
  char ch;
  while ((ch = getchar()) && !isdigit(ch))
    ;
  x = ch - '0';
  while ((ch = getchar()) && isdigit(ch)) x = x * 10 + ch - '0';
}
struct point {
  int x, y;
  point() {}
  point(int _x, int _y) : x(_x), y(_y) {}
};
int dp[33][33][50010], ans[100], al, whe[100], nn, p;
void g_ans(int n) {
  puts("Yes");
  int j = 0, k = 0;
  while (1) {
    int jj = dp[n][j][k] / 1000000, kk = (dp[n][j][k] - jj * 1000000) / 10,
        t = dp[n][j][k] % 10;
    if (t) ans[++al] = whe[n];
    if (jj == 0 && kk == 0) break;
    n--;
    j = jj;
    k = kk;
  }
  printf("%d\n", al);
  for (int i = al; i >= 1; i--) printf("%d ", ans[i]);
  puts("");
}
int main() {
  scanf("%d%d", &nn, &p);
  int x, K, n = 0;
  dp[0][0][0] = 1;
  for (int i = 1; i <= nn; i++) {
    scanf("%d", &x);
    if (x > 31) continue;
    whe[n + 1] = i;
    for (int j = 0; j <= 31; j++)
      for (int k = 0; k <= p - 1; k++)
        if (dp[n][j][k]) {
          if (x < 10)
            K = (k * 10 + x) % p;
          else
            K = (k * 100 + x) % p;
          dp[n + 1][j ^ x][K] = j * 1000000 + k * 10 + 1;
          if ((j ^ x) == 0 && K == 0) {
            g_ans(n + 1);
            return 0;
          }
          dp[n + 1][j][k] = j * 1000000 + k * 10;
        }
    n++;
  }
  puts("No");
}
