#include <bits/stdc++.h>
using namespace std;
ifstream inp("inp.txt");
ofstream out("out.txt");
const int N = 1e5 + 5;
const long long B = 73;
int builtin_popcount(int &mask) {
  int kol = 0;
  for (int bit = 0; bit < 20; bit++) kol += int(bool(mask & (1 << bit)));
  return kol;
}
signed main() {
  ios::sync_with_stdio(0);
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  string a;
  cin >> a;
  int up = (1 << 20);
  vector<int> dp(up, 0);
  vector<int> masks;
  for (int i = 0; i < ((int)a.size()); i++) {
    int mask = 0;
    for (int j = i; j < min(((int)a.size()), i + 20); j++) {
      int bit = a[j] - 'a';
      if (mask & (1 << bit)) break;
      mask |= (1 << bit);
      masks.push_back(mask);
      dp[mask] = builtin_popcount(mask);
    }
  }
  for (int mask = 1; mask < up; mask++)
    for (int bit = 0; bit < 20; bit++)
      if (mask & (1 << bit)) dp[mask] = max(dp[mask], dp[mask ^ (1 << bit)]);
  int ans = 0;
  for (auto &mask : masks)
    ans = max(ans, builtin_popcount(mask) + dp[mask ^ (up - 1)]);
  cout << ans;
  return 0;
}
