#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, m;
  cin >> n >> m;
  vector<pair<long long, long long>> a;
  long long x, y;
  long long v[n];
  for (int i = 0; i < n; i++) {
    cin >> x;
    a.push_back(make_pair(x, i));
  }
  sort(a.begin(), a.end());
  long long l = 0;
  for (int i = 0; i < n; i++) {
    if (i % 2)
      v[a[i].second] = 1;
    else
      v[a[i].second] = 0;
  }
  for (int i = 0; i < m; i++) cin >> x >> y;
  for (int i = 0; i < n; i++) cout << v[i] << " ";
  return 0;
}
