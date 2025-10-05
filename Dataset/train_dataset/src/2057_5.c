#include <bits/stdc++.h>
using namespace std;
unsigned long long one = 1;
struct mybtset {
  unsigned long long a[80];
  mybtset() { memset(a, 0, sizeof a); }
  void st(int i) { a[i >> 6] |= (one << (i & 63)); }
  bool is(int i) { return a[i >> 6] & (one << (i & 63)); }
};
bool check(mybtset &x, mybtset &y, int i) {
  i >>= 6;
  for (; i < 80; ++i) {
    if (x.a[i] & y.a[i]) return 1;
  }
  return 0;
}
mybtset adj[5005], readj[5005];
int main() {
  int n;
  cin >> n;
  char a[5005];
  for (int i = 0; i < n; ++i) {
    scanf("%s", a);
    for (int j = 0; j < n; ++j) {
      if (a[j] == '1') {
        adj[i].st(j);
        readj[j].st(i);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (!adj[i].is(j)) continue;
      if (check(adj[j], readj[i], i)) {
        for (int k = 0; k < n; ++k) {
          if (adj[j].is(k) && readj[i].is(k)) {
            cout << i + 1 << " " << j + 1 << " " << k + 1 << endl;
            return 0;
          }
        }
      }
    }
  }
  cout << -1 << endl;
}
