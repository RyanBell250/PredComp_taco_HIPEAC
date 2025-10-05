#include <bits/stdc++.h>
using namespace std;
int g[5];
string s[5];
int a[5][1010], b[5][5];
int dp[1010][(1 << 12) + 10];
int inf = 1000 * 1000 * 1000;
vector<pair<int, int> > v, v1;
bool mark[5][5] = {};
int tiv[5][5] = {};
void avelacnel(int x1, int y1, int x2, int y2) {
  for (int i = x1; i <= x2; i++)
    for (int j = y1; j <= y2; j++) mark[i][j] = true;
}
void sarqelv() {
  for (int i1 = 0; i1 <= 4; i1++) {
    for (int i2 = 0; i2 <= 3; i2++) {
      for (int i3 = 0; i3 <= 2; i3++) {
        for (int i4 = 0; i4 <= 1; i4++) {
          for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++) mark[i][j] = false;
          avelacnel(0, 4 - i1, i1 - 1, 3);
          avelacnel(1, 4 - i2, i2, 3);
          avelacnel(2, 4 - i3, i3 + 1, 3);
          avelacnel(3, 4 - i4, i4 + 2, 3);
          int hgin = g[i1] + g[i2] + g[i3] + g[i4];
          int hmask = 0;
          for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
              if (mark[i][j]) hmask += (1 << tiv[i][j]);
          v1.push_back(make_pair(hmask, hgin));
        }
      }
    }
  }
  sort(v1.begin(), v1.end());
  for (int i = 0; i < v1.size(); i++)
    if (i == 0 || v1[i].first != v1[i - 1].first) v.push_back(v1[i]);
}
int main() {
  int n;
  cin >> n;
  cin >> g[1] >> g[2] >> g[3] >> g[4] >> s[1] >> s[2] >> s[3] >> s[4];
  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= n; j++) a[i][3 + j] = (s[i][j - 1] == '.' ? 0 : 1);
  for (int i = 0; i < (1 << 12); i++)
    for (int j = 0; j <= n + 7; j++) dp[j][i] = inf;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) tiv[i][j] = j * 4 + i;
  sarqelv();
  dp[4][0] = 0;
  for (int i = 4; i <= n + 6; i++) {
    for (int mask = 0; mask < (1 << 12); mask++) {
      for (int j = 0; j < v.size(); j++) {
        int vmask = v[j].first;
        int vgin = v[j].second;
        int avelmask = (a[1][i] << 12) + (a[2][i] << 13) + (a[3][i] << 14) +
                       (a[4][i] << 15);
        avelmask = mask + avelmask;
        int hmask = (avelmask & vmask) ^ avelmask;
        if (hmask % 16 != 0) continue;
        hmask = hmask >> 4;
        dp[i + 1][hmask] = min(dp[i + 1][hmask], dp[i][mask] + vgin);
      }
    }
  }
  cout << dp[n + 7][0] << endl;
  return 0;
}
