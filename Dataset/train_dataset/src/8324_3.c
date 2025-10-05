#include <bits/stdc++.h>
using namespace std;
long long int visited[51];
long long int Fact(long long int x) {
  long long int y = 1;
  for (long long int i = 1; i <= x; i++) {
    y = ((y % 998244353) * (i % 998244353)) % 998244353;
  }
  return y;
}
long long int dfs(long long int parent, vector<long long int> v[]) {
  long long int y = 1;
  visited[parent] = 1;
  for (long long int i = 0; i < v[parent].size(); i++) {
    if (visited[v[parent][i]] == 0) {
      y += dfs(v[parent][i], v);
    }
  }
  return y;
}
long long int modularExponentiation(long long int x, long long int n,
                                    long long int M) {
  long long int result = 1;
  while (n > 0) {
    if (n % 2 == 1) result = ((result % M) * (x % M)) % M;
    x = ((x % M) * (x % M)) % M;
    n = n / 2;
  }
  return result;
}
long long int binaryExponentiation(long long int x, long long int n) {
  long long int result = 1;
  while (n > 0) {
    if (n % 2 == 1) result = result * x;
    x = x * x;
    n = n / 2;
  }
  return result;
}
long long int pow1(long long int x, long long int y) {
  long long int z = 1;
  while (y--) {
    z = z * x;
  }
  return z;
}
bool isprime(long long int n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (int i = 5; i * i <= n; i = i + 6)
    if (n % i == 0 || n % (i + 2) == 0) return false;
  return true;
}
long long int check(long long int x) {
  long long int y = 1, z = 0;
  while (x > y) {
    y *= 2;
    z++;
  }
  if (x != y) {
    z--;
  }
  return z;
}
unsigned long long modInverse(unsigned long long n, int p) {
  return modularExponentiation(n, p - 2, p);
}
unsigned long long nCrModPFermat(unsigned long long n, int r, int p) {
  if (r == 0) return 1;
  unsigned long long fac[n + 1];
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = (fac[i - 1] * i) % p;
  return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) %
         p;
}
long long int modInverse(long long int A, long long int M) {
  return modularExponentiation(A, M - 2, M);
}
bool cmp(pair<long long int, long long int> a,
         pair<long long int, long long int> b) {
  if (a.first == b.first)
    return a.second < b.second;
  else
    return a.first < b.first;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  long long int n;
  cin >> n;
  for (long long int i = 0; i < n; i++) {
    if ((i % 4) < 2)
      cout << 'a';
    else
      cout << 'b';
  }
}
