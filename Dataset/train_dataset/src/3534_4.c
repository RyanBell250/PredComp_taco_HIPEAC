#include <bits/stdc++.h>
using namespace std;
const int maxsize = 100;
int a[3][maxsize] = {0};
int b[maxsize] = {0};
int n;
int calc(int x) {
  int res = 0;
  res += b[x];
  for (int i = 1; i < x; i++) res += a[1][i];
  for (int i = x; i < n; i++) res += a[2][i];
  return res;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= 2; i++) {
    for (int j = 1; j <= n - 1; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int j = 1; j <= n; j++) {
    scanf("%d", &b[j]);
  }
  int ans = 2100000000;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      ans = min(ans, calc(i) + calc(j));
    }
  }
  printf("%d\n", ans);
  return 0;
}
