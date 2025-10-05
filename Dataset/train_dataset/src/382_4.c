#include <bits/stdc++.h>
using namespace std;
const int nm = 1e5 + 10;
int n;
char ans[600][600];
void go() {
  ans[0][0] = '+';
  int res = 1, rec = 1;
  for (int k = 1; k < 10; k++) {
    rec = res << 1;
    int i = 0;
    for (; i < res; i++) {
      for (int j = res; j < rec; j++) ans[i][j] = ans[i][j - res];
    }
    for (; i < rec; i++) {
      for (int j = 0; j < res; j++) ans[i][j] = ans[i - res][j];
      for (int j = res; j < rec; j++) {
        if (ans[i][j - res] == '+')
          ans[i][j] = '*';
        else
          ans[i][j] = '+';
      }
    }
    res = rec;
  }
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  go();
  while (cin >> n) {
    int m = 1 << n;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        cout << ans[i][j];
      }
      cout << endl;
    }
  }
  return 0;
}
