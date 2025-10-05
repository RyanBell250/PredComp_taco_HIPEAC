#include <bits/stdc++.h>
using namespace std;
const long long int modulo = 1000 * 1000 * 1000 + 7;
int mn[50];
int c[50];
long long int* factors = new long long int[1000 * 1000 + 1000];
long long int* pows2 = new long long int[1000 * 1000 + 1000];
long long int reverseElem(long long int a, long long int m) {
  long long int q, r, x1, x2, y1, y2, x, d, y, b;
  b = m;
  if (b == 0) {
    d = a;
    x = 1;
    y = 0;
  } else {
    x2 = 1, x1 = 0, y2 = 0, y1 = 1;
    while (b > 0) {
      q = a / b;
      r = a - q * b;
      x = x2 - q * x1;
      y = y2 - q * y1;
      a = b;
      b = r;
      x2 = x1;
      x1 = x;
      y2 = y1;
      y1 = y;
    }
    d = a;
    x = x2;
    y = y2;
  }
  if (d != 1) return -1;
  return (x % m + m) % m;
}
long long int pow2(long long int k) {
  if (pows2[k] != -1) return pows2[k];
  pows2[k] = (pow2(k - 1) * 2) % modulo;
  return pows2[k];
}
long long int power(long long int a, long long int p) {
  long long int ans = 1;
  long long int s = a;
  for (long long int k = p; k > 0; k /= 2) {
    if (k % 2) {
      ans *= s;
      ans %= modulo;
    }
    s *= s;
    s %= modulo;
  }
  return ans;
}
long long int fact(long long int k) {
  if (factors[k] != -1) return factors[k];
  factors[k] = (fact(k - 1) * k) % modulo;
  return factors[k];
}
long long int cnk(long long int n, long long int k) {
  return (fact(n) * reverseElem((fact(n - k) * fact(k)) % modulo, modulo)) %
         modulo;
}
long long int k, pa, pb;
long long int kk;
long long int** Gmem;
long long int G(long long int k, long long int s) {
  if ((k == 1) && (s == 0)) return 1;
  if (k == 0) return 0;
  if (s < 0) return 0;
  if (Gmem[k][s] != -1) return Gmem[k][s];
  long long int res =
      (G(k - 1, s) * pa % modulo + G(k, s - k) * pb % modulo) % modulo;
  if (k - 1 + s >= kk) res = G(k, s - k) * pb % modulo;
  Gmem[k][s] = res;
  return res;
}
int main() {
  for (int i = 0; i < 1000 * 1000 + 1000; i++) factors[i] = -1;
  factors[0] = 1;
  factors[1] = 1;
  for (int i = 0; i < 1000 * 1000 + 1000; i++) pows2[i] = -1;
  pows2[0] = 1;
  Gmem = new long long int*[1001];
  for (int i = 0; i < 1001; i++) Gmem[i] = new long long int[1001];
  for (int i = 0; i < 1001; i++)
    for (int j = 0; j < 1001; j++) Gmem[i][j] = -1;
  cin >> k >> pa >> pb;
  long long int ta, tb;
  ta = pa;
  tb = pb;
  kk = k;
  pa = pa * reverseElem((ta + tb) % modulo, modulo) % modulo;
  pb = pb * reverseElem((ta + tb) % modulo, modulo) % modulo;
  for (int i = 0; i < 1001; i++)
    for (int j = 0; j < 1001; j++) G(i, j);
  long long int ans = 0;
  for (int i = 0; i <= k; i++)
    for (int j = 0; j < k; j++) {
      if (i + j >= k) ans = (ans + G(i, j) * (i + j)) % modulo;
    }
  long long int f = reverseElem((modulo + 1 - pa) % modulo, modulo) % modulo;
  long long int g =
      f * reverseElem((modulo + 1 - pa) % modulo, modulo) % modulo;
  long long int tmp = g * pa % modulo;
  tmp = tmp * pb % modulo;
  ans = (ans + tmp) % modulo;
  cout << ans;
  return 0;
}
