#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:256000000")
using namespace std;
const double PI = acos(-1.0);
int ma[100];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", ma + i);
  sort(ma, ma + n);
  reverse(ma, ma + n);
  int k = 0;
  for (int i = 0; i < 100000; i++) {
    for (int j = 0; j < n - 1; j++)
      if (ma[j] != ma[j + 1]) {
        ma[j] -= (ma[j] / ma[j + 1]) * ma[j + 1];
        ma[j] += (ma[j] == 0) * ma[j + 1];
        sort(ma, ma + n);
        reverse(ma, ma + n);
        break;
      }
  }
  long long s = 0;
  for (int i = 0; i < n; i++) s += ma[i];
  cout << s << endl;
  return 0;
}
