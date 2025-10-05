#include <bits/stdc++.h>
using namespace std;
int a[600005], n, k, mu[600], t, l;
int main() {
  cin >> n >> k;
  mu[0] = 1;
  for (int i = 1; i <= 30; i++) mu[i] = mu[i - 1] * 2;
  for (int i = 30; i >= 0; i--)
    if (n >= mu[i]) {
      n -= mu[i];
      t++;
      a[t] = mu[i];
    }
  if (t > k)
    cout << "NO";
  else {
    l = 0;
    while (t < k) {
      l++;
      while (a[l] != 1) {
        a[l] = a[l] / 2;
        t++;
        a[t] = a[l];
        if (a[l] == 0) {
          cout << "NO";
          return (0);
        }
        if (t == k) break;
      }
    }
    cout << "YES" << endl;
    for (int i = 1; i <= t; i++) cout << a[i] << ' ';
  }
}
