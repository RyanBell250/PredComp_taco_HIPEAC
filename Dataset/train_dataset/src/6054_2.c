#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  int count(int n) {
    long long res = 0;
    init(n);
    res +=
        (2LL * ((1LL * pow(3, 1LL * n * n)) % M - pow(-3 + pow(3, n), n) + M)) %
        M;
    for (int i = 0; i < n; ++i) {
      res = (res +
             (3LL * (C(n, i) * ((i + 1) % 2 == 0 ? 1 : -1)) *
              (pow(1 - pow(3, i), n) - pow(-pow(3, i), n) + M) % M) %
                 M +
             M) %
            M;
    }
    return res;
  }

 private:
  const static int M = 998244353;
  vector<long long> fac;
  vector<long long> ifac;
  void init(int n) {
    fac.resize(n + 1);
    fac[0] = 1;
    ifac.resize(n + 1);
    ifac[0] = 1;
    for (int i = 1; i <= n; ++i) {
      fac[i] = (fac[i - 1] * i) % M;
    }
    ifac[n] = pow(fac[n], M - 2);
    for (int i = n - 1; i > 0; --i) {
      ifac[i] = (ifac[i + 1] * (i + 1)) % M;
    }
  }
  int C(int n, int k) {
    return (((1LL * fac[n] * ifac[k]) % M) * ifac[n - k]) % M;
  }
  int pow(long long a, long long e) {
    long long p = a;
    int res = 1;
    while (e != 0) {
      if (e & 0x1) {
        res = (res * p) % M;
      }
      p = (1LL * p * p) % M;
      e >>= 1;
    }
    return res;
  }
};
int main(int argc, char** argv) {
  int n;
  cin >> n;
  Solution sol;
  cout << sol.count(n) << endl;
  return 0;
}
