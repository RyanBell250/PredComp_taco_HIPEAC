#include <bits/stdc++.h>
using namespace std;
const int Mod = 998244353;
int add(int a, int b) { return a + b >= Mod ? a + b - Mod : a + b; }
int dec(int a, int b) { return a - b < 0 ? a - b + Mod : a - b; }
int mul(int a, int b) { return 1ll * a * b % Mod; }
void Add(int &a, int b) { a = add(a, b); }
void Mul(int &a, int b) { a = mul(a, b); }
void Dec(int &a, int b) { a = dec(a, b); }
int ksm(int a, int b) {
  int as = 1;
  for (; b; b >>= 1, Mul(a, a))
    if (b & 1) Mul(as, a);
  return as;
}
const int N = 5e3 + 50;
int n, fc[N], ifc[N], f[N][N];
void Main() {
  fc[0] = fc[1] = ifc[0] = ifc[1] = 1;
  for (int i = 2; i <= n; i++) fc[i] = mul(fc[i - 1], i);
  ifc[n] = ksm(fc[n], Mod - 2);
  for (int i = n - 1; i >= 2; i--) ifc[i] = mul(ifc[i + 1], i + 1);
  f[1][1] = 1;
  for (int i = 2; i <= n; i++)
    for (int j = 1; j <= i; j++)
      f[i][j] = add(mul(i - j + 1, f[i - 1][j - 1]), mul(j, f[i - 1][j]));
  for (int i = 1; i <= n; i++) {
    int as = 0;
    for (int j = i; j <= n; j++) Add(as, mul(f[j][i], ifc[j]));
    cout << mul(as, fc[n]) << " ";
  }
}
int main() {
  scanf("%d", &n);
  Main();
  return 0;
}
