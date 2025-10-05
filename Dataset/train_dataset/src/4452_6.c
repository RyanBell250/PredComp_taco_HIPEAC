#include <bits/stdc++.h>
using namespace std;
int a[200005], f[200005], t[2000006], mx, mxbr;
bool bio[2000006], p[2000006];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    p[a[i]] = 1;
    mxbr = max(mxbr, a[i]);
  }
  for (int i = 2; i <= 2 * mxbr; i++) {
    if (p[i - 1])
      t[i] = i - 1;
    else
      t[i] = t[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    if (bio[a[i]]) continue;
    int x = 2 * a[i];
    for (int j = x; j <= 2 * mxbr; j += a[i])
      if (t[j] > a[i]) mx = max(mx, t[j] % a[i]);
    bio[a[i]] = 1;
  }
  cout << mx;
}
