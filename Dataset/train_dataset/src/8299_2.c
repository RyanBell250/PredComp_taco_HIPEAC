#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b;
  cin >> a >> b;
  if (b < a * 2) {
    cout << "NO";
    return 0;
  }
  cout << "YES" << '\n';
  for (int i = 0; i < a - 1; i++) cout << 2 << ' ';
  cout << b - 2 * (a - 1) << '\n';
  cout << 1 << '\n';
  return 0;
}
