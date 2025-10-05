#include <bits/stdc++.h>
using namespace std;
const int N = 18003000 + 10, M = 6000 + 10;
inline int rd() {
  int x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 3) + (x << 1) + (ch ^ 48);
    ch = getchar();
  }
  return x * w;
}
int prm[N], tt;
bool v[N];
int n, s, a[M];
int main() {
  n = rd();
  s = n * (n + 1) / 2;
  for (int i = 2; i <= s; ++i) {
    if (!v[i]) prm[++tt] = i;
    for (int j = 1; j <= tt && i * prm[j] <= s; ++j) {
      v[i * prm[j]] = 1;
      if (i % prm[j] == 0) break;
    }
  }
  if (n == 1)
    puts("-1");
  else if (!v[s]) {
    for (int i = 1; i <= n; ++i) printf("%d ", 1);
  } else if ((s & 1) ^ 1) {
    for (int j = 1; j <= tt; ++j)
      if (!v[s - prm[j]]) {
        int x = prm[j];
        while (x) a[x & (-x)] = 1, x ^= x & (-x);
        for (int i = 1; i <= n; ++i) printf("%d ", a[i] + 1);
        break;
      }
  } else if (!v[s - 2]) {
    printf("1 2 ");
    for (int i = 3; i <= n; ++i) printf("%d ", 1);
  } else {
    a[3] = 2, s -= 3;
    for (int j = 1; j <= tt; ++j)
      if (!v[s - prm[j]]) {
        int x = prm[j];
        while (x) a[x & (-x)] = 1, x ^= x & (-x);
        for (int i = 1; i <= n; ++i) printf("%d ", a[i] + 1);
        break;
      }
  }
  return 0;
}
