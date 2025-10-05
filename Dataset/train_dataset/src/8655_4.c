#include <bits/stdc++.h>
using namespace std;
const int M = 100005;
const int mod = 1e9 + 7;
string ans;
long long n, k;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  if (n * (n - 1) / 2 < k) return cout << "Impossible", 0;
  while (k) {
    int cur = 0;
    while (k >= cur) {
      cout << '(';
      --n;
      k -= cur;
      ++cur;
    }
    for (; cur; --cur) {
      if (k >= cur) {
        k -= cur;
        --n;
        cout << "()";
      }
      cout << ')';
    }
  }
  while (n--) cout << "()";
  return 0;
}
