#include <bits/stdc++.h>
using namespace std;
int n;
void read() { cin >> n; }
void solve() {
  int l = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      int x = sqrt(i * i + j * j);
      if (x <= n && x * x == (i * i + j * j)) l++;
    }
  }
  cout << l;
}
int main() {
  read();
  solve();
}
