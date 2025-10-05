#include <bits/stdc++.h>
using namespace std;
const long long mod = 1000000007;
vector<long long> factorial;
vector<long long> inversos;
bool comp(const pair<long long, long long>& a,
          const pair<long long, long long>& b) {
  long long a1 = a.first + a.second;
  long long b1 = b.first + b.second;
  return a1 < b1;
}
long long redueix(long long num) {
  if (num > mod or -num > -mod) return num % mod;
  return num;
}
long long pow(long long base, long long p) {
  if (p == 0) return 1;
  if (p == 1) return base;
  if (p % 2 == 0) return redueix(pow(redueix(base * base), p / 2));
  return redueix((base)*pow(redueix(base * base), (p - 1) / 2));
}
long long inv(long long pos) { return pow(pos, mod - 2); }
long long bin(long long m, long long n) {
  if (m < 0 or n < 0) return 0;
  if (m == 0 or n == 0) return 1;
  long long ans = factorial[m + n];
  ans = redueix(ans);
  ans *= inversos[m];
  ans = redueix(ans);
  ans *= inversos[n];
  ans = redueix(ans);
  return ans;
}
int main() {
  long long h, w, n;
  cin >> h >> w >> n;
  vector<pair<long long, long long> > black(n);
  factorial = vector<long long>(h + w + 5);
  inversos = vector<long long>(h + w + 5);
  factorial[0] = 1;
  for (int i = 1; i < int(factorial.size()); ++i) {
    factorial[i] = (factorial[i - 1] * i) % mod;
    inversos[i] = inv(factorial[i]);
  }
  for (long long i = 0; i < n; ++i) cin >> black[i].first >> black[i].second;
  sort(black.begin(), black.end(), comp);
  vector<long long> ways(n, 0);
  long long ans = bin(h - 1, w - 1);
  for (long long i = 0; i < n; ++i) {
    ways[i] = bin(black[i].first - 1, black[i].second - 1);
    for (long long j = 0; j < i; ++j) {
      ways[i] -= redueix((ways[j] * bin(black[i].first - black[j].first,
                                        black[i].second - black[j].second)));
      ways[i] = redueix(ways[i]);
    }
    ans -= redueix(ways[i] * bin(h - black[i].first, w - black[i].second));
    ans = redueix(ans);
  }
  if (ans < 0) ans += mod;
  ans = redueix(ans);
  cout << ans << endl;
}
