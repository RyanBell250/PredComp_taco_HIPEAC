#include <bits/stdc++.h>
using namespace std;
int n, m, k;
int main() {
  scanf("%d%d%d", &n, &m, &k);
  if (n % 2 == 0)
    printf("Marsel\n");
  else {
    int flag = 0;
    for (int i = 1; i <= m; i++) {
      if (m % i == 0) {
        if (i >= k && m / i > 1 || m / i >= k && i > 1) {
          flag = 1;
          printf("Timur\n");
          break;
        }
      }
      if (i > sqrt(m)) break;
    }
    if (!flag) printf("Marsel\n");
  }
  return 0;
}
