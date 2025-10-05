#include <bits/stdc++.h>
using namespace std;
int a, b;
int main() {
  cin >> a >> b;
  vector<pair<int, int> > ans;
  {
    map<int, pair<int, int> > mp;
    for (int l = 1, r; l <= a; l = r + 1) {
      r = a / (a / l);
      int k = a / l;
      mp[k] = {l, r};
    }
    for (int l = 1, r; l <= b; l = r + 1) {
      r = b / (b / l);
      int k = b / l;
      if (mp.count(k)) {
        ans.push_back({l + mp[k].first, r + mp[k].second});
      }
    }
  }
  {
    map<int, pair<int, int> > mp;
    for (int l = 1, r; l <= a; l = r + 1) {
      r = a / (a / l);
      int k = a / l;
      mp[k] = {l, r};
    }
    for (int q = 1; q * q <= b; ++q) {
      if (b % q == 0) {
        int k = (b - 1) / q;
        if (mp.count(k)) {
          ans.push_back({q + mp[k].first, q + mp[k].second});
        }
        if (q * q != b) {
          k = (b - 1) / (b / q);
          if (mp.count(k)) {
            ans.push_back({b / q + mp[k].first, b / q + mp[k].second});
          }
        }
      }
    }
  }
  {
    map<int, pair<int, int> > mp;
    for (int l = 1, r; l <= b; l = r + 1) {
      r = b / (b / l);
      int k = b / l;
      mp[k] = {l, r};
    }
    for (int p = 1; p * p <= a; ++p) {
      if (a % p == 0) {
        int k = (a - 1) / p;
        if (mp.count(k)) {
          ans.push_back({p + mp[k].first, p + mp[k].second});
        }
        if (p * p != a) {
          k = (a - 1) / (a / p);
          if (mp.count(k)) {
            ans.push_back({a / p + mp[k].first, a / p + mp[k].second});
          }
        }
      }
    }
  }
  sort(ans.begin(), ans.end());
  int siz = 0;
  for (int i = 1; i <= ans.size() - 1; ++i) {
    if (ans[i].first > ans[siz].second)
      ans[++siz] = ans[i];
    else
      ans[siz].second = ans[i].second;
  }
  int sum = 0;
  for (int i = 0; i <= siz; ++i) {
    sum += ans[i].second - ans[i].first + 1;
  }
  cout << sum;
}
