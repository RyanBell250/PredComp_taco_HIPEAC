#include <bits/stdc++.h>
using namespace std;
int ask(int n) {
  cout << "? ";
  printf("%d\n", n);
  fflush(stdout);
  int x;
  scanf("%d", &x);
  return x;
}
int main() {
  int n;
  scanf("%d", &n);
  int hn = n >> 1;
  if (hn & 1) {
    cout << "! " << -1 << endl;
    exit(0);
  }
  int x = ask(1);
  int y = ask(1 + hn);
  if (x == y) {
    cout << "! " << 1 << endl;
    exit(0);
  }
  int l = 1;
  int r = n / 2;
  while (l <= r) {
    int mid = (l + r) >> 1;
    int xl = ask(mid);
    int xr = ask(mid + hn);
    if (xl == xr) {
      cout << "! " << mid << endl;
      exit(0);
    }
    if (x < y) {
      if (xl < xr) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    } else {
      if (xl > xr) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
  }
  cout << "! " << -1 << endl;
  exit(0);
  return 0;
}
