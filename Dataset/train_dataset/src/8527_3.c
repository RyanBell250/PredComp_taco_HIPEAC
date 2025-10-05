#include <bits/stdc++.h>
using namespace std;
int k, len;
string x;
const int T = 550;
const int N = 502;
pair<int, string> arr[N][N];
int memo[N][N];
int dp(int l, int z) {
  if (!z) {
    if (l == len) return 0;
    return T;
  }
  if (l == len) return 0;
  int &ret = memo[l][z];
  if (~ret) return ret;
  ret = T;
  for (int i = l; i < len; ++i) {
    ret = min(ret, dp(i + 1, z - 1) + arr[l][i].first);
  }
  return ret;
}
void slv() {
  string tmp;
  for (int i = 0; i < len; ++i) {
    for (int j = i; j < len; ++j) {
      tmp = x;
      int counter = 0;
      for (int s = i, z = j; s <= z; ++s, --z) {
        if (tmp[s] != tmp[z]) tmp[s] = tmp[z], counter++;
      }
      arr[i][j] = make_pair(counter, tmp);
    }
  }
}
void build(int l, int z) {
  if (z == 0 || l == len) return;
  int res = dp(l, z);
  for (int i = l; i < len; ++i) {
    if (dp(i + 1, z - 1) + arr[l][i].first == res) {
      cout << arr[l][i].second.substr(l, i + 1 - l);
      if (i != len - 1) cout << '+';
      build(i + 1, z - 1);
      return;
    }
  }
}
int main() {
  cin >> x >> k;
  len = x.size();
  memset(memo, -1, sizeof memo);
  slv();
  cout << dp(0, k);
  cout << endl;
  build(0, k);
}
