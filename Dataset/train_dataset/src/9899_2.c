#include <bits/stdc++.h>
using namespace std;
void cpgod() {}
long long int gcd(long long int a, long long int b) {
  if (a % b == 0) return b;
  return gcd(b, a % b);
}
int main() {
  cpgod();
  int n;
  cin >> n;
  long long int a[n];
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  long long int gc = gcd(a[0], a[1]);
  long long int temp;
  for (int i = 2; i < n; i++) {
    temp = gcd(gc, a[i]);
    gc = temp;
  }
  if (n == 1) gc = a[0];
  int sum;
  set<int> sat;
  for (int i = 1; i <= sqrt(gc); i++)
    if (gc % i == 0) {
      sat.insert(i);
      sat.insert(gc / i);
    }
  cout << sat.size();
  return 0;
}
