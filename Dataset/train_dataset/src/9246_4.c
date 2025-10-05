#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, w, h;
int g[maxn], p[maxn], t[maxn];
vector<int> x[maxn], y[maxn];
int cmp(int x, int y) { return p[x] < p[y]; }
pair<int, int> ans[maxn];
int main() {
  cin >> n >> w >> h;
  for (int i = 0; i < n; i++) {
    cin >> g[i] >> p[i] >> t[i];
    int temp = p[i] - t[i] + 100000;
    if (g[i] == 1) {
      x[temp].push_back(i);
    } else
      y[temp].push_back(i);
  }
  for (int i = 0; i <= 200000; i++) {
    sort(x[i].begin(), x[i].end(), cmp);
    sort(y[i].begin(), y[i].end(), cmp);
    int cntx = x[i].size();
    int cnty = y[i].size();
    for (int j = 0; j < cntx; j++) {
      int id = x[i][j];
      int num = cntx - j - 1;
      if (num >= cnty) {
        ans[id] = make_pair(p[x[i][j + cnty]], h);
      } else {
        ans[id] = make_pair(w, p[y[i][num]]);
      }
    }
    for (int j = 0; j < cnty; j++) {
      int id = y[i][j];
      int num = cnty - j - 1;
      if (num >= cntx) {
        ans[id] = make_pair(w, p[y[i][j + cntx]]);
      } else
        ans[id] = make_pair(p[x[i][num]], h);
    }
  }
  for (int i = 0; i < n; i++)
    cout << ans[i].first << " " << ans[i].second << endl;
  return 0;
}
