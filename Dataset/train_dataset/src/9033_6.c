#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n;
int a[N], now, l, r;
char op[N];
int cntop;
int main() {
  scanf("%d", &n);
  l = 1;
  r = n;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  while (l <= r) {
    if (a[l] > now && a[r] > now) {
      if (a[l] == a[r]) {
        for (int i = l + 1, j = r - 1;; i++, j--) {
          if (a[i] <= a[i - 1]) {
            while (a[r] > now) {
              op[++cntop] = 'R';
              now = a[r];
              r--;
            }
            break;
          } else if (a[j] <= a[j + 1]) {
            while (a[l] > now) {
              op[++cntop] = 'L';
              now = a[l];
              l++;
            }
            break;
          }
        }
      } else if (a[l] < a[r]) {
        op[++cntop] = 'L';
        now = a[l];
        l++;
      } else {
        op[++cntop] = 'R';
        now = a[r];
        r--;
      }
    } else if (a[l] > now) {
      op[++cntop] = 'L';
      now = a[l];
      l++;
    } else if (a[r] > now) {
      op[++cntop] = 'R';
      now = a[r];
      r--;
    } else {
      break;
    }
  }
  printf("%d\n%s\n", cntop, op + 1);
  return 0;
}
