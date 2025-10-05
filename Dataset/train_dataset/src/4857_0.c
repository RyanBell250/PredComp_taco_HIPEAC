#include <bits/stdc++.h>
using namespace std;
const long long int N = 1000001;
const long long int M = 1;
vector<int> v[N];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int _ = 1;
  while (_--) {
    long long int n, x = 0, y = 0, ans = 0, z;
    cin >> n;
    long long int a[n];
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      if (v[a[i]].size() == 0) {
        v[a[i]].push_back(0);
      }
      v[a[i]].push_back(i + 1);
    }
    for (auto s : v) {
      if (s.size() > 0) {
        s.push_back(n + 1);
        x = 0;
        for (int i = s.size() - 2; i > 0; i--) {
          y = s[i + 1] - s[i];
          ans += y - 1;
          z = s[i] - s[i - 1];
          ans += z - 1;
          ans += (z - 1) * (y - 1);
          ans += x * z;
          x += y;
        }
      }
    }
    ans = 2 * ans;
    long double sol = 1L / (long double)n;
    sol = sol + (long double)ans / (long double)(n * n);
    cout << sol << '\n';
  }
  return 0;
}
