#include <bits/stdc++.h>
using namespace std;
map<set<int>, int> mem;
int calc(set<int>& s) {
  if (s.size() == 0) return 0;
  if (mem.find(s) != mem.end()) return mem[s];
  set<int> tmp = s;
  int i = 1;
  vector<int> rs;
  for (set<int>::iterator it = s.begin(); it != s.end(); ++it) {
    for (; i <= *it; ++i) {
      for (set<int>::iterator it2 = s.find(*it); it2 != s.end(); ++it2) {
        int val = *it2 - i;
        tmp.erase(*it2);
        if (val) tmp.insert(val);
      }
      rs.push_back(calc(tmp));
      tmp = s;
    }
  }
  sort(rs.begin(), rs.end());
  int ans = 0;
  for (int i = 0; i < rs.size(); ++i) {
    if (rs[i] == ans) ans++;
  }
  mem[s] = ans;
  return ans;
}
int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  long long int ans = 0;
  map<int, set<int> > ar;
  for (int i = 0; i < n; ++i) {
    long long int a;
    cin >> a;
    for (long long int j = 2; j * j <= a; ++j) {
      if (a % j == 0) {
        int cur = 0;
        while (a % j == 0) {
          cur++;
          a /= j;
        }
        ar[j].insert(cur);
      }
    }
    if (a > 1) ar[a].insert(1);
  }
  for (map<int, set<int> >::iterator it = ar.begin(); it != ar.end(); ++it) {
    if (mem.find(it->second) == mem.end()) {
      int rs = calc(it->second);
      mem[it->second] = rs;
    }
    ans ^= mem[it->second];
  }
  if (ans) {
    cout << "Mojtaba" << endl;
  } else {
    cout << "Arpa" << endl;
  }
}
