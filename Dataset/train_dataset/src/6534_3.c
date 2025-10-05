#include <bits/stdc++.h>
using namespace std;
struct node {
  int x, y;
} a[100100];
vector<pair<int, int> > p[300100];
int shu[300100];
bool nod[100100];
int ct[100100];
int n, w, h, t;
int main() {
  scanf("%d%d%d", &n, &w, &h);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", &a[i].x, &a[i].y, &t);
    if (a[i].x == 1)
      p[100000 - t + a[i].y].push_back(make_pair(-a[i].y, i)),
          shu[100000 - t + a[i].y]++;
    else
      p[100000 - t + a[i].y].push_back(make_pair(a[i].y, i));
  }
  for (int i = 0; i <= 300000; i++) {
    if (!p[i].empty()) {
      sort(p[i].begin(), p[i].end());
      for (int j = p[i].size() - shu[i]; j < p[i].size(); j++)
        nod[p[i][j].second] = 1;
      for (int j = 0; j < p[i].size(); j++)
        ct[p[i][j].second] = p[i][(j + shu[i]) % p[i].size()].first;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (nod[i]) {
      printf("%d %d\n", -ct[i], h);
    } else {
      printf("%d %d\n", w, ct[i]);
    }
  }
}
