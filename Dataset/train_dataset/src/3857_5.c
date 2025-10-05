#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) {
  if (a % b == 0)
    return b;
  else
    return gcd(b, a % b);
}
int sum(long long a) {
  int sum = 0;
  while (a > 0) {
    sum = sum + (a % 10);
    a = a / 10;
  }
  return sum;
}
int count_digit(long long n) {
  int count = 0;
  while (n > 0) {
    n = n / 10;
    count++;
  }
  return count;
}
int binarySearch(int x, int y, long long z, long long v[]) {
  int low = x;
  int high = y;
  int mid = x + (y - x) / 2;
  while (low <= high) {
    if (v[mid] == z) return mid;
    if (v[mid] < z) return binarySearch(mid + 1, high, z, v);
    if (v[mid] > z) return binarySearch(low, mid - 1, z, v);
  }
  return -1;
}
long long modularExponentiation(long long x, long long n, long long M) {
  if (n == 0)
    return 1;
  else if (n % 2 == 0)
    return modularExponentiation((x * x) % M, n / 2, M);
  else
    return (x * modularExponentiation((x * x) % M, (n - 1) / 2, M)) % M;
}
long long binaryExponentiation(long long x, long long n) {
  if (n == 0)
    return 1;
  else if (n % 2 == 0)
    return binaryExponentiation(x * x, n / 2);
  else
    return x * binaryExponentiation(x * x, (n - 1) / 2);
}
int binary(int n) {
  int c = 0;
  while (n > 0) {
    if (n % 2 == 1) {
      return pow(2, c);
    }
    n = n / 2;
    c++;
  }
}
long long ceil1(long long x, long long y) {
  if (x % y == 0)
    return x / y;
  else
    return x / y + 1;
}
set<long long> s;
void genrate(long long n, int len, int max) {
  if (len > max) return;
  s.insert(n);
  genrate(n * 10 + 1, len + 1, max);
  genrate(n * 10 + 0, len + 1, max);
}
int dist(int start, int end, int n) {
  if (end >= start)
    return end - start;
  else
    return n - start + end;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tests = 1;
  while (tests--) {
    int n, m;
    cin >> n >> m;
    vector<int> v[n + 1];
    for (int i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;
      v[x].push_back(y);
    }
    int a[n + 1];
    a[0] = 0;
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= n; i++) {
      if (v[i].size() == 0)
        a[i] = 0;
      else {
        int ans = INT_MAX;
        for (int j = 0; j < v[i].size(); j++) {
          ans = min(ans, dist(i, v[i][j], n));
        }
        a[i] = ans;
      }
    }
    for (int i = 1; i <= n; i++) {
      int ans = 0;
      for (int j = 1; j <= n; j++) {
        if (v[j].size() == 0) continue;
        if (v[j].size() != 0)
          ans = max(ans, dist(i, j, n) + n * (int(v[j].size()) - 1) + a[j]);
      }
      cout << ans << " ";
    }
  }
}
