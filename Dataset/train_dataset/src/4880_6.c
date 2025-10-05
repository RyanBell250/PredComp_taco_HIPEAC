#include <bits/stdc++.h>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");
const long long MAXL = 1e18;
const int N = 10005000;
const int MAXN = 1e9 + 7;
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  srand(time(NULL));
  vector<vector<int> > v(1000, vector<int>(1000));
  vector<pair<int, int> > a(4), b(4);
  for (int i = 0; i < 4; ++i) {
    cin >> a[i].first >> a[i].second;
    a[i].first += 100;
    a[i].second += 100;
  }
  for (int i = 0; i < 4; ++i) {
    cin >> b[i].first >> b[i].second;
    b[i].first += 100;
    b[i].second += 100;
  }
  sort(a.begin(), a.end());
  swap(a[2], a[3]);
  sort(b.begin(), b.end());
  swap(b[1], b[2]);
  swap(b[2], b[3]);
  for (int i = a[0].first; i <= a[3].first; ++i) {
    for (int j = a[0].second; j <= a[1].second; ++j) {
      v[i][j]++;
    }
  }
  int j = b[3].second;
  for (int i = b[3].first; i > b[0].first; --i) {
    v[i][j] += 2;
    j++;
  }
  j = b[0].second;
  for (int i = b[0].first; i < b[1].first; ++i) {
    v[i][j] += 2;
    j++;
  }
  j = b[1].second;
  for (int i = b[1].first; i < b[2].first; ++i) {
    v[i][j] += 2;
    j--;
  }
  j = b[2].second;
  for (int i = b[2].first; i > b[3].first; --i) {
    v[i][j] += 2;
    j--;
  }
  bool crossed = false;
  for (int i = 0; i < 1000; ++i) {
    for (int j = 0; j < 1000; ++j) {
      if (i == b[0].first && j == b[0].second) continue;
      if (i == b[2].first && j == b[2].second) continue;
      if (v[i][j] > 1)
        crossed = !crossed;
      else if (crossed)
        v[i][j] += 2;
    }
  }
  for (int i = 0; i < 1000; ++i) {
    for (int j = 0; j < 1000; ++j) {
      if (v[i][j] > 2) {
        cout << "YES\n";
        return 0;
      }
    }
  }
  cout << "NO\n";
  return 0;
}
