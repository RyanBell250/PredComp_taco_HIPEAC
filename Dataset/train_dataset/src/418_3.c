#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  string s[n + 1];
  if (n % 2 == 0)
    cout << n * n / 2 << endl;
  else
    cout << ((n * n) + 1) / 2 << endl;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i % 2 != 0 && j % 2 != 0)
        cout << 'C';
      else if (i % 2 != 0 && j % 2 == 0)
        cout << '.';
      else if (i % 2 == 0 && j % 2 != 0)
        cout << '.';
      else
        cout << 'C';
    }
    cout << endl;
  }
  return 0;
}
