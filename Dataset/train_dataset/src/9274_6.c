#include <bits/stdc++.h>
using namespace std;
const long long inf = 1e9 + 7;
const long long linf = 1e18 + 1;
template <typename T>
using V = vector<T>;
template <typename T = long long>
T nxt() {
  T x;
  cin >> x;
  return x;
}
template <typename T = long long>
void read(vector<T>& x) {
  for (T& i : x) cin >> i;
}
template <typename T = long long>
void print(vector<T>& x) {
  for (T v : x) {
    cout << v << " ";
  }
}
template <typename T = long long>
void printset(set<T>& x) {
  for (auto v : x) cout << v << " ";
  cout << endl;
}
void print(map<char, long long>& cnt) {
  for (auto [ch, count] : cnt) {
    for (long long i = 0; i < count; ++i) {
      cout << ch;
    }
  }
}
long long gcd(long long a, long long b) {
  if (a == 0) {
    return b;
  }
  return gcd(b % a, a);
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  long long TT = 1;
  while (TT--) {
    long long n;
    cin >> n;
    vector<long long> a(n);
    read(a);
    long long ans = 0;
    for (long long l = 0; l < n; l += 2) {
      long long fp = a[l];
      long long lp = 0;
      for (long long r = l + 1; r < n; ++r) {
        if (r % 2 == 0) {
          lp += a[r];
          continue;
        }
        long long v = a[r];
        long long d = min(v, lp);
        v -= d;
        lp -= d;
        if (v == 0) {
          if (lp == 0) {
            ++ans;
          }
          continue;
        }
        if (fp != a[l]) {
          ++ans;
        }
        ans += min(fp, v);
        fp -= v;
        if (fp < 0) {
          break;
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
