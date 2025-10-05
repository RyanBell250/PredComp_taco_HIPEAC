#include <bits/stdc++.h>
using namespace std;
const long long MAX1 = 3e5 + 10;
long long a, b, c, d, e, cnt, x, y, z, l, r, flag, num[MAX1], p[2];
string s, t, st[MAX1];
char ch1, ch2;
vector<long long> vec;
long long top(long long n, long long m) {
  if (n % m == 0) return n / m;
  return n / m + 1;
}
long long fact(long long n) {
  if (n == 0) return 1;
  return n * fact(n - 1);
}
int main() {
  cin >> a;
  for (int i = 0; i < a; ++i) cin >> num[i];
  for (int i = a - 1; i > -1; --i) {
    flag = 0;
    for (long long j : vec) {
      if (j == num[i]) flag = 1;
    }
    if (!flag) vec.push_back(num[i]);
  }
  cout << vec.size() << '\n';
  for (long long i = vec.size() - 1; i > -1; --i) cout << vec[i] << ' ';
  return 0;
}
