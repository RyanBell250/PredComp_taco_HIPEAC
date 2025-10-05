#include <bits/stdc++.h>
using namespace std;
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
const int MOD = 1e9 + 7;
const int inf = 1e9;
int add(int x, int y) {
  x += y;
  if (x >= MOD) {
    x -= MOD;
  }
  return x;
}
int del(int x, int y) {
  x -= y;
  if (x < 0) {
    x += MOD;
  }
  return x;
}
const int N = 3e5 + 5;
int t, x;
string s, tmp;
int main() {
  cin.tie(0), ios_base::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    int l = 0;
    string c;
    cin >> x;
    cin >> s;
    s = "+" + s;
    int lim = 0;
    bool ok = 0;
    while (l != x) {
      l++;
      tmp = "";
      int ad = s.length() - 1 - l, num = 0;
      if (!ok && s[l] - '0' - 1 >= 1) {
        tmp = s.substr(l + 1);
      } else
        num = del(lim, l);
      int times = s[l] - '0' - 1;
      while (times > 0) {
        if (!ok) {
          s += tmp;
        } else
          lim = add(lim, num);
        times--;
      }
      if (!ok && s.length() - 1 > x) {
        ok = 1;
        lim = s.length() - 1;
      }
    }
    int n = s.length();
    n--;
    if (ok)
      cout << lim << "\n";
    else
      cout << s.length() - 1 << "\n";
  }
}
