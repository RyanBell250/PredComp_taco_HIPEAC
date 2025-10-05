#include <bits/stdc++.h>
using namespace std;
int main() {
  int n = 0;
  cin >> n;
  string s = "abba";
  int j = 0;
  for (int i = 1; i <= n / 4; i++) {
    cout << s;
  }
  n = n % 4;
  for (int i = 0; i < n; i++) {
    cout << s[i];
  }
  cout << endl;
}
