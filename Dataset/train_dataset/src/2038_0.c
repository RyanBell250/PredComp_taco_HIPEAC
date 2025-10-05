#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, s, f;
  cin >> n >> m >> s >> f;
  map<long long int, pair<long long int, long long int> > hash;
  int i;
  long long int mx = INT_MIN;
  for (i = 0; i < m; i++) {
    long long int x, y, z;
    cin >> x >> y >> z;
    hash[x] = {y, z};
  }
  int step = 1;
  while (s != f) {
    if (hash.find(step) != hash.end()) {
      long long int l = hash[step].first;
      long long int r = hash[step].second;
      if (s >= l && s <= r) {
        cout << "X";
      } else {
        if (f > s && !(s + 1 >= l && s + 1 <= r)) {
          cout << "R";
          s++;
        } else if (f < s && !(s - 1 >= l && s - 1 <= r)) {
          cout << "L";
          s--;
        } else {
          cout << "X";
        }
      }
    } else {
      if (f > s) {
        cout << "R";
        s++;
      } else if (f < s) {
        cout << "L";
        s--;
      }
    }
    step++;
  }
  cout << "\n";
  return 0;
}
