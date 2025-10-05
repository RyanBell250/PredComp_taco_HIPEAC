#include <bits/stdc++.h>
using namespace std;
map<int, pair<int, int> > Map;
int n, m, i, s, f, t, l, r;
bool Check(int a) { return ((l <= a) && (a <= r)); }
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m >> s >> f;
  for (i = 1; i <= m; i++) {
    cin >> t >> l >> r;
    Map[t] = make_pair(l, r);
  }
  t = 0;
  while (true) {
    t++;
    l = Map[t].first;
    r = Map[t].second;
    if (s < f) {
      if ((!Check(s)) && (!Check(s + 1))) {
        cout << "R";
        s++;
      } else
        cout << "X";
    } else if (s > f) {
      if ((!Check(s - 1)) && (!Check(s))) {
        cout << "L";
        s--;
      } else
        cout << "X";
    } else
      break;
  }
  cout << '\n';
  return 0;
}
