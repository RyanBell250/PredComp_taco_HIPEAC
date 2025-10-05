#include <bits/stdc++.h>
using namespace std;
long long M[20];
long long R[20];
long long CONTEST_TOP_1(long long a, long long b) {
  if (a < b) swap(a, b);
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}
int main() {
  cout.precision(10);
  int n;
  cin >> n;
  long long mx = 1;
  for (int i = 1; i <= n; ++i) {
    cin >> M[i];
    mx = mx * M[i] / CONTEST_TOP_1(mx, M[i]);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> R[i];
  }
  long long db = 0;
  for (int i = 0; i < mx; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i % M[j] == R[j]) {
        ++db;
        break;
      }
    }
  }
  cout << (long double)(db) / mx;
  return 0;
}
