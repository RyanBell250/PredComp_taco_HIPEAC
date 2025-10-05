#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b) {
  while (a != 0 && b != 0) {
    if (a > b)
      a = a % b;
    else
      b = b % a;
  }
  return a + b;
}
int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  string s;
  string left, right;
  string result;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    s.push_back(i + 'a');
  }
  int c = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] % 2 == 1) c++;
  }
  if (n == 1) {
    cout << a[0] << endl;
    for (int i = 0; i < a[0]; i++) cout << s[0];
    return 0;
  }
  int x = gcd(a[0], a[1]);
  for (int i = 2; i < n; i++) x = gcd(x, a[i]);
  if (c == 0) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < a[i] / x; j++) result.push_back(s[i]);
    }
    cout << x << endl;
    for (int i = 0; i < x; i++) {
      if (i % 2 == 0) {
        reverse(result.begin(), result.end());
        cout << result;
      } else {
        reverse(result.begin(), result.end());
        cout << result;
      }
    }
  } else if (c == 1) {
    for (int i = 0; i < n; i++) {
      if (a[i] % 2 == 0) {
        for (int j = 0; j < a[i] / (x * 2); j++) {
          left.push_back(s[i]);
        }
      }
    }
    right = left;
    reverse(right.begin(), right.end());
    for (int i = 0; i < n; i++) {
      if (a[i] % 2 == 1) {
        for (int j = 0; j < a[i] / x; j++) left.push_back(s[i]);
      }
    }
    result = left + right;
    cout << x << endl;
    for (int i = 0; i < x; i++) cout << result;
  } else {
    cout << 0 << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < a[i]; j++) cout << s[i];
    }
  }
  return 0;
}
