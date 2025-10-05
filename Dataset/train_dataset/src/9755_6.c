#include <bits/stdc++.h>
using namespace std;
const long long inf = LLONG_MAX;
const long long mod = 1000000007;
void solve() {
  long long n, cntz = 0, cntb = 0;
  cin >> n;
  vector<long long> p(n), b(n, 0);
  set<long long> ms;
  for (long long i = 1; i <= n; i++) ms.insert(i);
  for (long long i = 0; i < n; i++) {
    cin >> p[i];
    if (p[i]) ms.erase(ms.find(p[i]));
    if (p[i]) b[i] = p[i] % 2 + 1;
    if (!p[i]) cntz++;
  }
  if (cntz == n) {
    (n == 1) ? cout << 0 << endl : cout << 1 << endl;
    return;
  }
  long long e, o;
  e = o = 0;
  vector<long long> x, y, u, v, z;
  for (auto m : ms) {
    if (m % 2)
      o++;
    else
      e++;
  }
  long long flag1, flag2;
  flag1 = flag2 = -1;
  for (long long i = 1; i < n; i++) {
    if (b[i - 1] != b[i] && !b[i]) {
      (b[i - 1] == 1) ? flag1 = i : flag2 = i;
    } else if (b[i - 1] != b[i] && !b[i - 1]) {
      if (b[i] == 1) {
        if (flag1 >= 0)
          y.push_back(i - flag1);
        else if (flag2 >= 0)
          z.push_back(i - flag2);
      } else {
        if (flag2 >= 0)
          x.push_back(i - flag2);
        else if (flag1 >= 0)
          z.push_back(i - flag1);
      }
      flag1 = flag2 = -1;
    } else if (b[i - 1] != b[i]) {
      cntb++;
    }
  }
  if (!b[0]) {
    long long idx = 0;
    while (idx < n && !b[idx]) idx++;
    (b[idx] == 2) ? u.push_back(idx) : v.push_back(idx);
  }
  if (!b[n - 1]) {
    long long idx = n - 1;
    while (idx >= 0 && !b[idx]) idx--;
    (b[idx] == 2) ? u.push_back(n - 1 - idx) : v.push_back(n - 1 - idx);
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  sort(u.begin(), u.end());
  sort(v.begin(), v.end());
  long long ans = 0;
  for (long long i = 0; i < x.size(); i++) {
    if (o >= x[i])
      o -= x[i];
    else {
      ans += 2;
      e -= x[i];
    }
  }
  for (long long i = 0; i < u.size(); i++) {
    if (o >= u[i])
      o -= u[i];
    else {
      if (o) {
        u[i] -= o;
        o = 0;
      }
      ans += 1;
      e -= u[i];
    }
  }
  for (long long i = 0; i < y.size(); i++) {
    if (e >= y[i])
      e -= y[i];
    else {
      ans += 2;
      o -= y[i];
    }
  }
  for (long long i = 0; i < v.size(); i++) {
    if (e >= v[i])
      e -= v[i];
    else {
      if (e) {
        v[i] -= e;
        e = 0;
      }
      ans += 1;
      o -= v[i];
    }
  }
  ans += z.size();
  ans += cntb;
  cout << ans << endl;
  return;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  solve();
  return 0;
}
