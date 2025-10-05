#include <bits/stdc++.h>
using namespace std;
const long long N = 200 * 1000 + 9;
const long long inf = 1e18;
const long long mod = 1e9 + 7;
vector<long long> hello(100005, -1);
void HakunaMatata() {
  long long n;
  cin >> n;
  long long A;
  cin >> A;
  vector<long long> c(n);
  for (long long i = 0; i < n; i++) {
    cin >> c[i];
  }
  set<long long> s1, s2;
  long long cnt = 0;
  map<long long, long long> make_pair;
  for (long long i = 0; i < n; i++) {
    if (c[i] != A) {
      if (s2.empty())
        s1.insert(c[i]), make_pair[c[i]]++;
      else {
        auto it = s2.find(c[i]);
        if (it != s2.end()) s1.insert(c[i]), make_pair[c[i]]++;
      }
    } else {
      cnt++;
      if (!s2.empty()) {
        for (auto it1 = s2.begin(); it1 != s2.end(); it1++) {
          if (make_pair[(*it1)] >= cnt) s1.insert((*it1));
        }
      }
      if (s1.empty()) {
        cout << -1 << '\n';
        return;
      }
      s2 = s1;
      s1.clear();
    }
  }
  if (s1.empty() and s2.empty()) {
    cout << -1 << '\n';
  }
  if (s1.empty()) {
    auto it = s2.begin();
    cout << (*it) << '\n';
    return;
  }
  auto it = s1.begin();
  cout << (*it) << '\n';
  return;
  return;
}
signed main() {
  HakunaMatata();
  return 0;
}
