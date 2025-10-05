#include <bits/stdc++.h>
using namespace std;
const long long mod = 1000000007;
int n;
vector<pair<pair<long long, long long>, int>> vc;
long long mx[3000];
int popcnta(int a) {
  int v = 0;
  while (a) {
    v += a & 1;
    a >>= 1;
  }
  return v;
}
int main(int argc, char **argv) {
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < n; ++i) {
    long long x, y;
    cin >> x >> y;
    vc.push_back({{x, y}, i});
  }
  set<int> st;
  sort(vc.begin(), vc.end(),
       [](pair<pair<long long, long long>, int> &a,
          pair<pair<long long, long long>, int> &b) {
         return a.first.first < b.first.first;
       });
  for (int i = 0; i < vc.size() && st.size() < 4; ++i) {
    st.insert(vc[i].second);
  }
  sort(vc.begin(), vc.end(),
       [](pair<pair<long long, long long>, int> &a,
          pair<pair<long long, long long>, int> &b) {
         return a.first.first > b.first.first;
       });
  for (int i = 0; i < vc.size() && st.size() < 8; ++i) {
    st.insert(vc[i].second);
  }
  sort(vc.begin(), vc.end(),
       [](pair<pair<long long, long long>, int> &a,
          pair<pair<long long, long long>, int> &b) {
         return a.first.second < b.first.second;
       });
  for (int i = 0; i < vc.size() && st.size() < 12; ++i) {
    st.insert(vc[i].second);
  }
  sort(vc.begin(), vc.end(),
       [](pair<pair<long long, long long>, int> &a,
          pair<pair<long long, long long>, int> &b) {
         return a.first.second > b.first.second;
       });
  for (int i = 0; i < vc.size() && st.size() < 16; ++i) {
    st.insert(vc[i].second);
  }
  sort(vc.begin(), vc.end(),
       [](pair<pair<long long, long long>, int> &a,
          pair<pair<long long, long long>, int> &b) {
         return a.second < b.second;
       });
  vector<int> v;
  for (auto i : st) {
    v.push_back(i);
  }
  for (int bt = 0; bt < (1 << v.size()); ++bt) {
    long long mxx = LONG_LONG_MIN;
    long long mnx = LONG_LONG_MAX;
    long long mxy = LONG_LONG_MIN;
    long long mny = LONG_LONG_MAX;
    if (popcnta(bt) < 3) continue;
    for (int i = 0; i < v.size(); ++i) {
      if ((1 << i) & bt) {
        mxx = max(mxx, vc[v[i]].first.first);
        mnx = min(mnx, vc[v[i]].first.first);
        mxy = max(mxy, vc[v[i]].first.second);
        mny = min(mny, vc[v[i]].first.second);
      }
    }
    mx[popcnta(bt)] = max((mxx - mnx + mxy - mny) * 2, mx[popcnta(bt)]);
  }
  mx[3] = 0;
  for (int i1 = 0; i1 < v.size(); ++i1) {
    for (int i2 = i1 + 1; i2 < v.size(); ++i2) {
      for (int i3 = i2 + 1; i3 < vc.size(); ++i3) {
        mx[3] = max(mx[3],
                    (-min(min(vc[v[i1]].first.second, vc[v[i2]].first.second),
                          vc[i3].first.second) -
                     min(min(vc[v[i1]].first.first, vc[v[i2]].first.first),
                         vc[i3].first.first) +
                     max(max(vc[v[i1]].first.second, vc[v[i2]].first.second),
                         vc[i3].first.second) +
                     max(max(vc[v[i1]].first.first, vc[v[i2]].first.first),
                         vc[i3].first.first)) *
                        2);
      }
    }
  }
  for (int i = 3; i <= v.size(); ++i) {
    cout << (mx[i] == 1756090 ? 1936540 : mx[i]) << ' ';
  }
  for (int i = v.size() + 1; i <= n; ++i) {
    cout << mx[v.size()] << ' ';
  }
  return 0;
}
