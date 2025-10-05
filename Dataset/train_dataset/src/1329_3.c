#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using row = vector<ll>;
using mat = vector<row>;
const int maxk = 10;
const ll mod = 1e6 + 3;
ll modpow(ll a, ll b) {
  ll ans = 1;
  for (; b; b /= 2) {
    if (b & 1) ans = ans * a % mod;
    a = a * a % mod;
  }
  return ans;
}
ll modinv(ll a) { return modpow(a, mod - 2); }
mat identity(int n) {
  mat I(n, row(n));
  for (int i = 0; i < int(n); i++) I[i][i] = 1;
  return I;
}
void mul_row(ll c, row& r) {
  int n = r.size();
  for (int i = 0; i < int(n); i++) r[i] = r[i] * c % mod;
}
void sub_row(int n, mat& A, int i, ll c, int j) {
  for (int k = 0; k < int(n); k++) {
    A[i][k] -= c * A[j][k];
    A[i][k] %= mod;
    if (A[i][k] < 0) A[i][k] += mod;
  }
}
mat inverse(int n, mat A) {
  mat B = identity(n);
  for (int j = 0; j < int(n); j++) {
    for (int i = j; i < n; i++) {
      if (A[i][j] != 0) {
        swap(A[i], A[j]);
        swap(B[i], B[j]);
        break;
      }
    }
    ll c = modinv(A[j][j]);
    mul_row(c, A[j]);
    mul_row(c, B[j]);
    for (int i = 0; i < int(n); i++) {
      if (i == j) continue;
      c = A[i][j];
      sub_row(n, A, i, c, j);
      sub_row(n, B, i, c, j);
    }
  }
  return B;
}
mat operator*(const mat& A, const mat& B) {
  int n = A.size();
  mat C(n, row(n));
  for (int i = 0; i < int(n); i++)
    for (int j = 0; j < int(n); j++)
      for (int k = 0; k < int(n); k++)
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
  return C;
}
vector<ll> matvec(int n, const mat& A, vector<ll>& x) {
  vector<ll> b(n);
  for (int i = 0; i < int(n); i++)
    for (int k = 0; k < int(n); k++) b[i] = (b[i] + A[i][k] * x[k]) % mod;
  return b;
}
ll eval(vector<ll>& a, ll x) {
  int n = a.size();
  ll ans = 0;
  for (int i = 0; i < int(n); i++) ans = (ans + a[i] * modpow(x, i)) % mod;
  return ans;
}
int main() {
  ios_base::sync_with_stdio(false);
  cout << setprecision(12);
  cin.tie(nullptr);
  mat A(maxk + 1, row(maxk + 1));
  for (int x = 0; x <= maxk; x++) {
    for (int k = 0; k <= maxk; k++) A[x][k] = modpow(x, k);
  }
  mat B = inverse(maxk + 1, A);
  vector<ll> b(maxk + 1);
  for (int x = 0; x <= maxk; x++) {
    cout << "? " << x << endl;
    cin >> b[x];
  }
  vector<ll> a = matvec(maxk + 1, B, b);
  for (int x = 0; x < int(mod); x++) {
    if (eval(a, x) == 0) {
      cout << "! " << x << endl;
      return 0;
    }
  }
  cout << "! -1" << endl;
}
