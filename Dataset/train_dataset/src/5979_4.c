#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1;
const int INF = 1e9 + 9;
const int B = 1e9 + 7;
int q;
int len, n;
long long f[N], rf[N];
long long pwr(long long a, long long b) {
  long long res = 1;
  for (; b; a = (a * a) % B, b >>= 1)
    if (b & 1) res = res * a % B;
  return res;
}
long long Cnk(int n, int k) {
  if (k < 0 || n < k) return 0;
  return f[n] * rf[k] % B * rf[n - k] % B;
}
int l2i[N], sz;
vector<int> v[N];
long long pwr25[N];
void add(int len) {
  l2i[len] = ++sz;
  v[sz].resize(1e5 + 1 - len);
  long long cur = 0;
  for (int n = int(len); n <= int(1e5); ++n) {
    int k = 0;
    cur = (cur * 26 % B + pwr25[n - len] * Cnk(n - k - 1, len - 1) % B) % B;
    v[sz][n - len] = cur;
  }
}
int main() {
  ios_base ::sync_with_stdio(0);
  cin.tie(0);
  f[0] = rf[0] = pwr25[0] = 1;
  for (int i = int(1); i <= int(N - 1); ++i) {
    f[i] = f[i - 1] * i % B;
    rf[i] = pwr(f[i], B - 2);
    pwr25[i] = pwr25[i - 1] * 25 % B;
  }
  cin >> q;
  string s;
  cin >> s;
  len = s.size();
  add(len);
  for (int _q = int(1); _q <= int(q); ++_q) {
    int tp;
    cin >> tp;
    if (tp == 1) {
      cin >> s;
      len = s.size();
      if (l2i[len] == 0) add(len);
    } else {
      int n;
      cin >> n;
      cout << (n < len ? 0 : v[l2i[len]][n - len]) << "\n";
    }
  }
  return 0;
}
