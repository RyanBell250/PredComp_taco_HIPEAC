#include <bits/stdc++.h>
const double pi = acos(-1.0), eps = 1e-9;
const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[8] = {0, 0, 1, -1, 1, -1, -1, 1};
const int MO = (int)(1e9 + 7);
using namespace std;
int a[101][101];
int num[10001];
bool vis[10001];
int n, sum, tot;
int tnum[20], backt[20], who[10001];
map<int, int> M;
bool calc(int x, int y) {
  int t = 0;
  for (int i = 1; i < n; i++) t += a[x][i];
  t = sum - t;
  a[x][y] = t;
  if (tnum[M[t]] == 0) return false;
  tnum[M[t]]--;
  return true;
}
bool calc2(int x, int y) {
  int t = 0;
  for (int i = 1; i < n; i++) t += a[i][y];
  t = sum - t;
  a[x][y] = t;
  if (tnum[M[t]] == 0) return false;
  tnum[M[t]]--;
  return true;
}
bool calc3(int x, int y) {
  int t = 0;
  for (int i = 1; i < n; i++) t += a[i][i];
  t = sum - t;
  a[x][y] = t;
  if (tnum[M[t]] == 0) return false;
  tnum[M[t]]--;
  return true;
}
void back() { memcpy(backt, tnum, sizeof(tnum)); }
void restore() { memcpy(tnum, backt, sizeof(tnum)); }
void check() {
  back();
  for (int i = 1; i < n; i++) {
    if (!calc2(n, i)) {
      restore();
      return;
    }
  }
  if (!calc3(n, n)) {
    restore();
    return;
  }
  int ns = 0;
  for (int i = 1; i <= n; i++) ns = ns += a[n - i + 1][i];
  if (ns != sum) {
    restore();
    return;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      printf("%d", a[i][j]);
      if (j == n)
        putchar('\n');
      else
        putchar(' ');
    }
  }
  exit(0);
}
bool calc4(int x, int y) {
  int t = a[1][1] + a[2][1] + a[3][1] - a[1][4] - a[2][3];
  a[x][y] = t;
  if (tnum[M[t]] == 0) return false;
  tnum[M[t]]--;
  return true;
}
void dfs(int x, int y) {
  if (x == n) {
    check();
    return;
  }
  if (y == n) {
    if (calc(x, y)) {
      dfs(x + 1, 1);
      ++tnum[M[a[x][y]]];
    }
    return;
  }
  if (x == 3 && y == 2) {
    if (calc4(x, y)) {
      dfs(x, y + 1);
      ++tnum[M[a[x][y]]];
    }
    return;
  }
  for (int i = tot; i >= 1; i--)
    if (tnum[i]) {
      --tnum[i];
      a[x][y] = who[i];
      dfs(x, y + 1);
      ++tnum[i];
    }
}
int main() {
  scanf("%d", &n);
  sum = 0;
  for (int i = 1; i <= n * n; i++) {
    scanf("%d", &num[i]), sum += num[i];
    if (!M.count(num[i])) {
      M[num[i]] = ++tot;
      who[tot] = num[i];
    }
    tnum[M[num[i]]]++;
  }
  sum /= n;
  printf("%d\n", sum);
  if (n == 1) {
    printf("%d\n", sum);
    return 0;
  }
  dfs(1, 1);
}
