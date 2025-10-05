#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:20000000")
using namespace std;
int ri() {
  int x;
  scanf("%d", &x);
  return x;
}
long long rll() {
  long long x;
  scanf("%lld", &x);
  return x;
}
int tin[100000];
void solve() {
  int n = ri(), m = ri(), t = ri();
  for (int i = (int)(1); i <= (int)(n); i++) {
    int h, m, s;
    scanf("%d:%d:%d", &h, &m, &s);
    tin[h * 3600 + m * 60 + s]++;
  }
  set<int> st;
  for (int j = (int)(1); j <= (int)(n); j++) st.insert(j);
  vector<int> res;
  multimap<int, int> index;
  bool yes = false;
  for (int i = (int)(0); i <= (int)(86400); i++) {
    while (!index.empty() && index.begin()->first == i) {
      index.erase(index.begin());
    }
    int cnt = tin[i];
    for (int j = 1; j <= cnt; j++) {
      if (index.size() < m) {
        index.insert(make_pair(i + t, *st.begin()));
        res.push_back(*st.begin());
        st.erase(st.begin());
        if (index.size() == m) yes = true;
      } else {
        int q = (--index.end())->second;
        index.erase(--index.end());
        index.insert(make_pair(i + t, q));
        res.push_back(q);
      }
    }
  }
  if (!yes) {
    cout << "No solution" << endl;
    return;
  }
  sort(res.begin(), res.end());
  int l = 0;
  for (int i = (int)(0); i <= (int)((int)res.size() - 1); i++)
    l = max(l, res[i]);
  cout << l << endl;
  for (int i = 0; i < res.size(); i++) printf("%d\n", res[i]);
}
int main() {
  solve();
  return 0;
}
