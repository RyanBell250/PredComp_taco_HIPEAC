#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n;
  while (cin >> n) {
    vector<long long int> factor;
    for (long long int i = 1; i * i <= n; ++i) {
      if (n % i == 0) {
        factor.push_back(i);
        if (i != n / i) factor.push_back(n / i);
      }
    }
    sort(factor.begin(), factor.end());
    long long int mx = 0, mm = 1LL << 60;
    for (unsigned int i = 0; i < factor.size(); ++i) {
      long long int A = factor[i];
      for (unsigned int j = 0; j < factor.size(); ++j) {
        long long int B = factor[j];
        if (n % (A * B) == 0 &&
            binary_search(factor.begin(), factor.end(), n / A / B)) {
          mx = max(mx, (A + 1) * (B + 2) * (n / A / B + 2));
          mm = min(mm, (A + 1) * (B + 2) * (n / A / B + 2));
        }
      }
    }
    cout << mm - n << " " << mx - n << endl;
  }
  return 0;
}
