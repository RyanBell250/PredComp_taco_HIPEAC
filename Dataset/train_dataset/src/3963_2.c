#include <bits/stdc++.h>
using namespace std;
const int inf = int(1e9);
const double eps = 0.0000000001, pi = 3.14159265358979323;
const int maxn = int(2e5 + 100);
vector<vector<int> > g;
bool visited[maxn];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int a[5], o = -1, I = -1, sum = 0;
  for (int i = 1; i <= 4; ++i) cin >> a[i];
  for (int i = -1; i <= int(1e6); ++i) {
    if (i * (i + 1) / 2 == a[1]) o = i + 1, sum += o;
    if (i * (i + 1) / 2 == a[4]) I = i + 1, sum += I;
  }
  if (I == -1 || o == -1) {
    cout << "Impossible";
    return 0;
  }
  long long all = o + I - 1;
  all = 1LL * all * (all + 1) / 2;
  if (a[1] && a[4] && all - a[1] - a[4] != a[2] + a[3]) {
    cout << "Impossible";
    return 0;
  }
  if (!a[2] && !a[3] && !a[4]) I = 0;
  if (!a[1] && !a[2] && !a[3]) o = 0;
  if (!o && !I) {
    cout << 0;
    return 0;
  }
  all = o + I - 1;
  all = 1LL * all * (all + 1) / 2;
  if (all - a[1] - a[4] != a[2] + a[3]) {
    cout << "Impossible";
    return 0;
  }
  int val1 = 0, val2 = 0;
  for (int i = 1; i <= sum; ++i) {
    if (val1 + I <= a[2] && o > 0) {
      cout << "0";
      val1 += I;
      o--;
    } else if (I > 0 && val2 + o <= a[3]) {
      cout << "1";
      val2 += o;
      I--;
    }
  }
  return 0;
}
