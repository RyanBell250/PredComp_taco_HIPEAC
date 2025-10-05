#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010, mod = 998244353;
inline int read() {
  int x = 0, f = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
  while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
  return f ? -x : x;
}
int n, k;
int main() {
  n = read();
  k = read();
  int a = (n - k) / 2, cnt = n;
  while (cnt >= a + 1) {
    for (int i = (1); i <= (a); i++) putchar('0');
    putchar('1');
    cnt -= a + 1;
  }
  for (int i = (1); i <= (cnt); i++) putchar('0');
}
