#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n, g;
  cin >> n;
  g = n;
  bool flag = false;
  int c = 0, count = 0;
  while (g != 0) {
    int b = g % 10;
    if (b == 4 || b == 7) {
      count++;
    }
    g = g / 10;
    c++;
  }
  int m = c;
  for (int i = 0; i < (1 << m); i++) {
    int res = 0;
    for (int j = 0; j < m; j++) {
      if ((i & (1 << j)) > 0) {
        res = res * 10 + 7;
        if (res == count) {
          flag = true;
        }
      } else {
        res = res * 10 + 4;
        if (res == count) {
          flag = true;
        }
      }
    }
  }
  if (flag) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}
