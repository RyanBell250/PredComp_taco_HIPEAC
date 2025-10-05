#include <bits/stdc++.h>
using namespace std;
long long int Pow(long long int B, long long int P) {
  long long int R = 1;
  while (P > 0) {
    if (P % 2 == 1) R = (R * B);
    P /= 2;
    B = (B * B);
  }
  return R;
}
int BigMod(long long int B, long long int P, long long int M) {
  long long int R = 1;
  while (P > 0) {
    if (P % 2 == 1) {
      R = (R * B) % M;
    }
    P /= 2;
    B = (B * B) % M;
  }
  return (int)R;
}
int prime[90000];
bool flag[1010];
int sieve() {
  int i, j, total = 0, val;
  val = sqrt(1010) + 1;
  flag[0] = flag[1] = 1;
  for (i = 2; i < val; i++)
    if (!flag[i])
      for (j = i; j * i <= 1010; j++) flag[i * j] = 1;
  for (i = 2; i <= 1010; i++)
    if (!flag[i]) prime[total++] = i;
  return total;
}
template <class T>
inline T lcm(T a, T b) {
  if (a < 0) return lcm(-a, b);
  if (b < 0) return lcm(a, -b);
  return a * (b / (gcd(a, b)));
}
template <class T>
inline T gcd(T a, T b) {
  if (a < 0) return gcd(-a, b);
  if (b < 0) return gcd(a, -b);
  return (b == 0) ? a : gcd(b, a % b);
}
int main() {
  int i, j, t, n, m, take, p, v;
  cin >> n >> m;
  p = max(n, m) - 1;
  v = min(n, m);
  cout << p << " " << v << endl;
  return 0;
}
