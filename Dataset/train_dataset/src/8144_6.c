#include <bits/stdc++.h>
using namespace std;
int min(int a, int b) {
  if (a < b) return a;
  return b;
}
int main() {
  int n;
  cin >> n;
  int guards[4][4];
  for (int i = 0; i < 4; i++)
    cin >> guards[i][0] >> guards[i][1] >> guards[i][2] >> guards[i][3];
  int i = 0;
  bool bribed = false;
  while (i < 4 && !bribed) {
    int g1 = min(guards[i][0], guards[i][1]);
    int g2 = min(guards[i][2], guards[i][3]);
    if (g1 + g2 <= n) {
      cout << (i + 1) << " " << g1 << " " << (n - g1);
      bribed = true;
    }
    i++;
  }
  if (!bribed) cout << -1;
}
