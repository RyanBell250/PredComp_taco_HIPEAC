#include <bits/stdc++.h>
using namespace std;
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target( \
    "sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("-ffloat-store")
const long long INF = 0xFFFFFFFFFFFFFFFL;
const long long N = 1e9 + 7;
vector<long long> f(500007);
void solve() {
  long long n;
  cin >> n;
  f[1] = 0;
  for (long long i = 3; i < 500000; i += 2) {
    long long l = (i - 1) / 2;
    f[i] = f[i - 2] + l * (i - 1) * 4;
  }
  cout << f[n] << "\n";
}
int32_t main(int32_t argc, char **argv) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long t;
  cin >> t;
  while (t--) solve();
  cerr << "\n"
       << "Time : " << 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC
       << "ms\n";
  return 0;
}
