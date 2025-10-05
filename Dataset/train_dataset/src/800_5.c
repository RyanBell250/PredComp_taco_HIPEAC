#include <bits/stdc++.h>
using namespace std;
struct pyt {
  int lev, l, p, x;
};
int main() {
  ios_base::sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vector<int> ile(200000);
  ile[0] = 0;
  ile[1] = 2;
  for (int i = 2; i < 200000; ++i) {
    ile[i] = i;
    for (int j = 1; j <= i; j *= 2) ++ile[i];
  }
  vector<pyt> p;
  for (int i = 0; i < m; ++i) {
    int op;
    cin >> op;
    if (op == 1) {
      int t, l, r, x;
      cin >> t >> l >> r >> x;
      p.push_back({t - 1, l, r, x});
    } else {
      int t, v;
      cin >> t >> v;
      --t;
      vector<int> L(n), P(n);
      L[t] = v;
      for (int level = t + 1; level < n; ++level)
        L[level] = ile[L[level - 1] - 1] + 1;
      P[t] = v;
      for (int level = t + 1; level < n; ++level) {
        if (__builtin_popcount(P[level - 1]) == 1)
          P[level] = ile[P[level - 1] - 1] + 2;
        else
          P[level] = ile[P[level - 1] - 1] + 1;
      }
      set<int> S;
      for (int j = 0; j < p.size(); ++j) {
        if (p[j].lev >= t) {
          int x = max(p[j].l, L[p[j].lev]);
          int y = min(p[j].p, P[p[j].lev]);
          if (x <= y) S.insert(p[j].x);
        }
      }
      cout << S.size() << endl;
    }
  }
  return 0;
}
