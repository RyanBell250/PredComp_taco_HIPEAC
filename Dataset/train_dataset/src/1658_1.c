#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int a, b, c = 0;
  cin >> a;
  b = 1;
  while (c < a) {
    c = (b * (b + 1)) / 2;
    b++;
  }
  b--;
  if (c == a)
    cout << b << endl;
  else {
    cout << b - c + a << endl;
  }
}
