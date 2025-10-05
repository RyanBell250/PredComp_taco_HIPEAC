#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, INF = 1e9 + 7;
long long i, j, n, m, ans;
long long a[N], d[N];
vector<pair<int, int> > v;
string st;
int main() {
  ios_base::sync_with_stdio(0);
  string s1, s2;
  cin >> n;
  for (i = 0; i < n; i++)
    for (j = i + 1; j <= n; j++) {
      v.push_back(make_pair(i, j));
    }
  sort(v.begin(), v.end());
  for (i = 0; i < v.size(); i++) {
    if (d[i]) continue;
    ans++;
    d[i] = 1;
    int t = v[i].second;
    for (j = i + 1; j < v.size(); j++) {
      if (d[j]) continue;
      if (t <= v[j].first) {
        d[j] = 1;
        t = v[j].second;
      }
    }
  }
  cout << ans;
}
