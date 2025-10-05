#include <bits/stdc++.h>
using namespace std;
bool desc(int a, int b) { return a > b; }
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, o;
    cin >> n;
    if (n % 4 == 0) {
      o = n / 4;
    } else {
      o = n / 4;
      o++;
    }
    for (int i = 0; i < n - o; i++) {
      cout << '9';
    }
    for (int i = 0; i < o; i++) {
      cout << '8';
    }
    cout << '\n';
  }
  return 0;
}
