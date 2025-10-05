#include <bits/stdc++.h>
using namespace std;
const int M = 1 << 20, INF = 2e9;
int dp[M], n, m, cost[25][25];
char s[25][25];
void Min(int &a, int b) {
  if (a > b) a = b;
}
void rd(int &res) {
  char c;
  res = 0;
  while (c = getchar(), !isdigit(c))
    ;
  do res = (res << 3) + (res << 1) + (c ^ 48);
  while (c = getchar(), isdigit(c));
}
int find(int string) {
  for (int i = 0; i < n; i++)
    if (!(string & (1 << i))) return i;
  return n - 1;
}
int main() {
  rd(n);
  rd(m);
  for (int i = 0; i < n; i++) scanf("%s", s[i]);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) rd(cost[i][j]);
  for (int string = 1; string < 1 << n; string++) dp[string] = INF;
  for (int string = 0; string + 1 < 1 << n; string++) {
    int had = find(string);
    for (int c = 0; c < m; c++) {
      Min(dp[string | (1 << had)], dp[string] + cost[had][c]);
      int sum = 0, mx = 0, nw = 0;
      for (int r = 0; r < n; r++)
        if (s[had][c] == s[r][c]) {
          sum += cost[r][c];
          mx = max(mx, cost[r][c]);
          nw |= 1 << r;
        }
      Min(dp[string | nw], dp[string] + sum - mx);
    }
  }
  printf("%d", dp[(1 << n) - 1]);
  return 0;
}
