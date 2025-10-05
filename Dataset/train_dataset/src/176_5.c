#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, pos, l, r;
  scanf("%d%d%d%d", &n, &pos, &l, &r);
  if (l == 1 && r == n) {
    printf("0");
  } else if ((pos == r && l == 1) || (pos == l && r == n)) {
    printf("1");
  } else if (r == n) {
    cout << abs(l - pos) + 1;
  } else if (l == 1) {
    cout << abs(r - pos) + 1;
  } else {
    int nwpos = min(abs(l - pos), abs(r - pos));
    cout << nwpos + (r - l) + 2;
  }
  return 0;
}
