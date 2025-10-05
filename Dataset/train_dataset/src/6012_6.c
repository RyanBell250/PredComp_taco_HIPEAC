#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:60777216")
using namespace std;
long long solve(long long n, long long i, long long m) {
  n -= i;
  if (n < 0) return 0;
  return n / m + 1;
}
int main() {
  int n, m;
  cin >> n >> m;
  long long res = 0;
  for (int i = (1); i < (m + 1); i++)
    for (int j = (1); j < (m + 1); j++)
      if ((i * i + j * j) % m == 0) {
        res += solve(n, i, m) * solve(n, j, m);
      }
  cout << res << endl;
  return 0;
}
