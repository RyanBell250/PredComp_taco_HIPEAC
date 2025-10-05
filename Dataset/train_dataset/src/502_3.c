#include <bits/stdc++.h>
using namespace std;
bool valid(int n, int mark) {
  bool higher = false;
  int eq = 0;
  for (int i = 0; i < n; ++i) {
    int k = mark % 3;
    if (k == 1) eq++;
    if (k == 2) {
      if (higher == true) return false;
      higher = true;
      eq++;
    }
    mark /= 3;
  }
  return eq >= 2;
}
int main() {
  int n;
  cin >> n;
  vector<pair<int, int> > v;
  long double denom = 1;
  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    v.push_back({l, r});
  }
  int high = 1;
  long double exp = 0;
  for (int i = 0; i < n; ++i) high *= 3;
  for (int nd = 10000; nd >= 1; nd--) {
    long double sum = 0;
    for (int mark = 0; mark < high; ++mark) {
      if (valid(n, mark)) {
        long double cnt = 1;
        int l = mark;
        for (int j = 0; j < n; ++j) {
          int k = l % 3;
          l /= 3;
          if (k == 0) {
            cnt *= max(0, min(nd - 1, v[j].second) - v[j].first + 1);
            cnt /= (v[j].second - v[j].first + 1);
          } else if (k == 1) {
            if (v[j].first <= nd && v[j].second >= nd)
              cnt /= (v[j].second - v[j].first + 1);
            else
              cnt = 0;
          } else {
            cnt *= max(0, v[j].second - max(nd + 1, v[j].first) + 1);
            cnt /= (v[j].second - v[j].first + 1);
          }
        }
        sum += cnt;
      }
    }
    exp += sum * nd;
  }
  cout << setprecision(20) << fixed << exp << endl;
}
