#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
signed main() { 
  ios::sync_with_stdio(false); cin.tie(0);
  int h, w, n;
  cin >> h >> w >> n;
  vector<vector<int>> walls(h + 2);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    walls[x].push_back(y);
  }
  for (int i = 1; i <= w; i++) walls[h + 1].push_back(i);
  int right = 1;
  for (int i = 1; i <= h; i++) {
    sort(walls[i + 1].begin(), walls[i + 1].end());
    int ex = 1;
    for (int j : walls[i + 1]) {
      if (j <= right) {
        cout << i << endl;
        return 0;
      }
      if (right + 1 == j) ex = 0;
    }
    right += ex;
  }
  return 0;
}