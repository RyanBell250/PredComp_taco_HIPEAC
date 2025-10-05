#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 100;
int n, k;
vector<pair<int, int> > a[MAXN];
int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(15);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    int l, r;
    cin >> l >> r;
    a[l].push_back({r, i});
  }
  set<pair<int, int> > st;
  vector<int> res;
  for (int i = 1; i < MAXN; i++) {
    while (st.size() > 0 and st.begin()->first < i) st.erase(st.begin());
    for (auto& p : a[i]) st.insert(p);
    while (st.size() > k) {
      auto last = --st.end();
      res.push_back(last->second);
      st.erase(last);
    }
  }
  sort(res.begin(), res.end());
  cout << res.size() << "\n";
  for (int x : res) cout << x << " ";
  cout << "\n";
  return 0;
}
