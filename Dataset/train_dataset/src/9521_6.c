#include <bits/stdc++.h>
using namespace std;
int fix(char x) {
  if (x == '^') return 0;
  if (x == '>') return 1;
  if (x == 'v') return 2;
  return 3;
}
int main() {
  char ch1, ch2;
  int n;
  cin >> ch1 >> ch2 >> n;
  int res = ((fix(ch2) - fix(ch1)) % 4 + 4) % 4;
  if (res % 2 == 0)
    cout << "undefined" << endl;
  else if (n % 4 == res)
    cout << "cw" << endl;
  else
    cout << "ccw" << endl;
  return 0;
}
