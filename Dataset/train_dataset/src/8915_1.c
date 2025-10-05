#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m, s;
  scanf("%d%d%d", &n, &m, &s);
  long long sol = 0;
  for (int a = 1; 2 * a - 1 <= n; a++)
    for (int c = 1; 2 * c - 1 <= n; c++) {
      int minAC = min(a, c);
      for (int minBD = 1; 2 * minBD - 1 <= m; minBD++) {
        int L = (2 * minBD - 1) * (2 * minAC - 1) + s;
        if ((L - (2 * a - 1) * (2 * minBD - 1)) % (2 * c - 1) == 0) {
          int b = minBD;
          int d = (L - (2 * a - 1) * (2 * b - 1)) / (2 * c - 1);
          if (d % 2) {
            d = (d + 1) / 2;
            if (d >= b) {
              int sizeX = -1 + 2 * max(a, c);
              int sizeY = -1 + 2 * max(b, d);
              if (sizeX <= n && sizeY <= m)
                sol += (long long)((n - sizeX + 1) * (m - sizeY + 1));
            }
          }
        }
        if ((L - (2 * c - 1) * (2 * minBD - 1)) % (2 * a - 1) == 0) {
          int d = minBD;
          int b = (L - (2 * c - 1) * (2 * d - 1)) / (2 * a - 1);
          if (b % 2) {
            b = (b + 1) / 2;
            if (b > d) {
              int sizeX = -1 + 2 * max(a, c);
              int sizeY = -1 + 2 * max(b, d);
              if (sizeX <= n && sizeY <= m)
                sol += (long long)((n - sizeX + 1) * (m - sizeY + 1));
            }
          }
        }
      }
    }
  printf("%I64d\n", sol);
  return 0;
}
