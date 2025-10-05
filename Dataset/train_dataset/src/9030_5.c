#include <bits/stdc++.h>
using namespace std;
int gcd(int gran, int petit) {
  if (petit == 0)
    return gran;
  else
    return gcd(petit, gran % petit);
}
int main() {
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> beads(n);
  int odds = 0, posodd;
  for (int i = 0; i < n; i++) {
    cin >> beads[i];
    if (beads[i] % 2 != 0) {
      odds++, posodd = i;
    }
  }
  if (odds > 1) {
    cout << "0" << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < beads[i]; j++) cout << char(i + 'a');
    }
    cout << endl;
    return 0;
  }
  long long prod = beads[0];
  int previ = beads[0];
  for (int i = 1; i < n; i++) {
    prod *= beads[i];
    previ = gcd(previ, beads[i]);
  }
  cout << previ << endl;
  if (odds == 1) {
    for (int j = 0; j < previ; j++) {
      for (int i = 0; i < n; i++) {
        if (i == posodd) continue;
        for (int j = 0; j < beads[i] / (2 * previ); j++) cout << char(i + 'a');
      }
      for (int j = 0; j < beads[posodd] / previ; j++)
        cout << char(posodd + 'a');
      for (int i = n - 1; i >= 0; i--) {
        if (i == posodd) continue;
        for (int j = 0; j < beads[i] / (2 * previ); j++) cout << char(i + 'a');
      }
    }
    cout << endl;
    return 0;
  }
  for (int j = 0; j < previ; j += 2) {
    for (int i = 0; i < n; i++)
      for (int k = 0; k < beads[i] / previ; k++) cout << char(i + 'a');
    for (int i = n - 1; i >= 0; i--)
      for (int k = 0; k < beads[i] / previ; k++) cout << char(i + 'a');
  }
  cout << endl;
  return 0;
}
