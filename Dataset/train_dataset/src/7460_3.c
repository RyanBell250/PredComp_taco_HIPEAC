#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  long long int t, n, i, j, k, x, y, tmp, ans, mini, maxi;
  bool flag;
  string s;
  t = 1;
  while (t--) {
    cin >> n >> k;
    vector<long long int> v(n);
    for (auto &z : v) cin >> z;
    sort(v.begin(), v.end());
    maxi = v[n - 1];
    ans = 1e17;
    for (i = 0; i <= maxi; i++) {
      x = 0;
      tmp = 0;
      for (j = 0; j < n; j++) {
        if (v[j] == i)
          x++;
        else {
          y = 0;
          long long int val = v[j];
          while (val > i) val /= 2, y++;
          if (val == i) tmp += y, x++;
        }
        if (x == k) break;
      }
      if (x == k) ans = min(ans, tmp);
    }
    cout << ans << "\n";
  }
}
