#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int num_1, num_2;
bool isp[maxn * 2];
int pri[maxn * 2];
int n;
int cnt = 1;
void init() {
  memset(isp, 1, sizeof(isp));
  for (int i = 2; i * i <= maxn * 2; i++) {
    if (isp[i]) {
      for (int j = 2 * i; j <= maxn * 2; j += i) {
        isp[j] = 0;
      }
    }
  }
  for (int i = 2; i <= 2 * maxn; i++) {
    if (isp[i]) pri[cnt++] = i;
  }
}
int res[maxn * 2];
int main() {
  init();
  scanf("%d", &n);
  int x;
  for (int i = 0; i < n; i++) {
    scanf("%d", &x);
    if (x == 1)
      num_1++;
    else
      num_2++;
  }
  pri[0] = 0;
  int num = 0;
  int m;
  for (int i = 1; i <= cnt; i++) {
    x = pri[i] - pri[i - 1];
    if (x & 1) {
      if (num_1 == 0) break;
      if ((x - 1) / 2 > num_2) break;
    } else {
      if (num_1 + num_2 * 2 < x) break;
    }
    m = x / 2;
    if (num_2 >= m) {
      for (int j = 0; j < m; j++) {
        res[num++] = 2;
      }
      num_2 -= m;
      if (x - m * 2) {
        res[num++] = 1;
        num_1--;
      }
    } else {
      int v = x;
      ;
      for (int j = 0; j < num_2; j++) {
        res[num++] = 2;
        v -= 2;
      }
      num_2 = 0;
      for (int j = 0; j < v; j++) {
        res[num++] = 1;
      }
      num_1 -= v;
    }
  }
  for (int i = 0; i < num_2; i++) {
    res[num++] = 2;
  }
  for (int i = 0; i < num_1; i++) res[num++] = 1;
  for (int i = 0; i < num; i++) {
    printf("%d%c", res[i], i == num - 1 ? '\n' : ' ');
  }
  return 0;
}
