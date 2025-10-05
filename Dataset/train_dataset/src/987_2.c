#include <bits/stdc++.h>
using namespace std;
struct Naturals {
  vector<int> spd;
  Naturals(int n) : spd(n + 1, -1) {
    for (int p = 2; p <= n; p++) {
      if (spd[p] != -1) {
        continue;
      }
      for (int j = p; j <= n; j += p) {
        if (spd[j] == -1) {
          spd[j] = p;
        }
      }
    }
  }
  void get_primes(int num, vector<int>& res) {
    while (num != 1) {
      int p = spd[num];
      res.push_back(p);
      while (num % p == 0) {
        num /= p;
      }
    }
  }
};
Naturals N(1000000);
int get_val(int limit, int n) {
  if (limit > n) {
    return (limit / n) * get_val(n, n) + get_val(limit % n, n);
  }
  vector<int> pd;
  N.get_primes(n, pd);
  int n_pd = pd.size();
  int res = 0;
  for (int i = 0; i < (1 << n_pd); i++) {
    int denominator = 1;
    int count = 0;
    int curr = i;
    for (int j = 0; j < n_pd; j++) {
      if (curr % 2) {
        denominator *= pd[j];
        count++;
      }
      curr /= 2;
    }
    res += (count % 2 ? -1 : 1) * (limit / denominator);
  }
  return res;
}
long long solve(int x, int p, int k) {
  k += get_val(x, p);
  long long l = -1;
  long long r = 1023456789ll;
  while (r - l > 1) {
    long long s = (l + r) / 2;
    if (get_val(s, p) < k) {
      l = s;
    } else {
      r = s;
    }
  }
  return r;
}
int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int x, p, k;
    cin >> x >> p >> k;
    cout << solve(x, p, k) << "\n";
  }
  return 0;
}
