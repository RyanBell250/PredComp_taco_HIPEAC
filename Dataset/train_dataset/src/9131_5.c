#include <bits/stdc++.h>
using namespace std;
int boy[1001];
int girl[1001];
int main() {
  int p, q, a, b;
  cin >> p >> q >> a >> b;
  while (p--) {
    int l, r;
    cin >> l >> r;
    for (int i = l; i <= r; i++) girl[i]++;
  }
  int pd = 0;
  int count = 0;
  while (q--) {
    int l, r;
    cin >> l >> r;
    for (int i = l; i <= r; i++) {
      boy[i + a]++;
      if (girl[i + a] >= 1 && pd == 0) {
        count++;
        pd = 1;
      }
    }
  }
  for (int i = 1; i <= b - a; i++) {
    int sd = 0;
    for (int j = 1000; j >= 0; j--) {
      boy[j] = boy[j - 1];
      if (boy[j] >= 1 && girl[j] >= 1 && sd == 0) {
        count++;
        sd = 1;
      }
    }
  }
  cout << count << endl;
  return 0;
}
