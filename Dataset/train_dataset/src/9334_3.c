#include <bits/stdc++.h>
using namespace std;
int N, M;
int A[303030];
const signed long long mo = 998244353;
signed long long F[303030];
signed long long modpow(signed long long a, signed long long n = mo - 2) {
  signed long long r = 1;
  a %= mo;
  while (n) r = r * ((n % 2) ? a : 1) % mo, a = a * a % mo, n >>= 1;
  return r;
}
void solve() {
  int i, j, k, l, r, x, y;
  string s;
  cin >> N;
  for (i = 0; i < (N); i++) {
    cin >> A[i];
    M += A[i];
  }
  F[0] = N - 1;
  for (x = 1; x < M; x++) {
    signed long long a = (M - x) * modpow(M) % mo * modpow(N - 1) % mo;
    signed long long b = 1 + x * F[x - 1] % mo * modpow(M) % mo;
    F[x] = b * modpow(a) % mo;
  }
  for (i = M - 1; i >= 0; i--) F[i] = (F[i] + F[i + 1]) % mo;
  signed long long ret = 0;
  for (i = 0; i < (N); i++) ret += F[A[i]];
  ret = (ret % mo - F[0] * (N - 1) % mo + mo) % mo;
  cout << ret * modpow(N) % mo << endl;
}
int main(int argc, char** argv) {
  string s;
  int i;
  if (argc == 1) ios::sync_with_stdio(false), cin.tie(0);
  for (i = 0; i < (argc - 1); i++) s += argv[i + 1], s += '\n';
  for (i = 0; i < (s.size()); i++) ungetc(s[s.size() - 1 - i], stdin);
  cout.tie(0);
  solve();
  return 0;
}
