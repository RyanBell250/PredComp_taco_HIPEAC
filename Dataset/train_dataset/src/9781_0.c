#include <bits/stdc++.h>
const long long inf = std::numeric_limits<long long>::max();
const long long mod = 1e9 + 7;
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
char ans[2000100];
int a[2000100];
int nxt[2000100];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  for (int i = 0; i < 2000100; i++) ans[i] = 'a';
  for (int i = 0; i < 2000100; i++) nxt[i] = i;
  int mx = 0;
  for (int i = 0; i < n; i++) {
    string st;
    cin >> st;
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
      cin >> a[i];
      int tt = st.size();
      mx = max(mx, tt + a[i] - 1);
      int j = nxt[a[i] - 1];
      while (j < a[i] + tt - 1) {
        while (nxt[j] != j) {
          nxt[j] = nxt[nxt[j]];
          j = nxt[j];
        }
        if (j >= a[i] + tt - 1) break;
        ans[j] = st[j - a[i] + 1];
        nxt[j] = nxt[a[i] + tt - 1];
        j++;
      }
    }
  }
  for (int i = 0; i < mx; i++) cout << ans[i];
  return 0;
}
