#include <bits/stdc++.h>
using namespace std;
int n;
int a[30];
int gcd(int a, int b) {
  if (a < b) swap(a, b);
  if (b == 0) return a;
  return gcd(a % b, b);
}
void solve() {
  int count_odd = 0;
  int odd_pointer;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] % 2 == 1) {
      count_odd++;
      odd_pointer = i;
    }
  }
  int nwd = 0;
  for (int i = 0; i < n; i++) nwd = gcd(nwd, a[i]);
  char t;
  if (count_odd > 1) {
    cout << "0" << endl;
    for (int i = 0; i < n; i++) {
      t = 97 + i;
      for (int j = 0; j < a[i]; j++) cout << t;
    }
    return;
  }
  vector<char> block;
  if (count_odd == 1) {
    for (int i = 0; i < n; i++) {
      if (a[i] % 2 == 0) {
        for (int j = 0; j < (a[i] / 2) / nwd; j++) {
          t = 97 + i;
          block.push_back(t);
        }
      }
    }
    for (int i = 0; i < a[odd_pointer] / nwd; i++) {
      t = 97 + odd_pointer;
      block.push_back(t);
    }
    for (int i = n - 1; i >= 0; i--) {
      if (a[i] % 2 == 0) {
        for (int j = 0; j < a[i] / 2 / nwd; j++) {
          t = 97 + i;
          block.push_back(t);
        }
      }
    }
    cout << nwd << endl;
    for (int i = 0; i < nwd; i++) {
      for (int j = 0; j < block.size(); j++) {
        cout << block[j];
      }
    }
  }
  if (count_odd == 0) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < a[i] / nwd; j++) {
        t = 97 + i;
        block.push_back(t);
      }
    }
    cout << nwd << endl;
    bool rev = 0;
    for (int i = 0; i < nwd; i++) {
      if (rev == 0) {
        for (int j = 0; j < block.size(); j++) cout << block[j];
      } else {
        for (int j = 0; j < block.size(); j++)
          cout << block[block.size() - j - 1];
      }
      rev ^= 1;
    }
    return;
  }
}
int main() { solve(); }
