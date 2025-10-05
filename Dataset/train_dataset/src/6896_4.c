#include <bits/stdc++.h>
using namespace std;
double po(double a, int n) {
  if (n == 0)
    return 1;
  else if (n == 1)
    return a;
  else if (n & 1)
    return a * po(a * a, n / 2);
  else
    return po(a * a, n / 2);
}
int main() {
  double a, s = 0, b;
  int n;
  cin >> a >> n;
  for (int i = 1; i < a; i++) s += i * (po((i + 1) / a, n) - po(i / a, n));
  printf("%.9f", s + 1);
}
