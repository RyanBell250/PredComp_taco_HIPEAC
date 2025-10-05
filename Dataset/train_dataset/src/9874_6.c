#include <bits/stdc++.h>
using namespace std;
int n;
int cnt[1000002];
class Combination {
  long long int ppow(long long int i, long long int j) {
    long long int res = 1LL;
    while (j) {
      if ((j & 1LL)) {
        res *= i;
        if (res >= 1000000007) {
          res %= 1000000007;
        }
      }
      j >>= 1;
      i *= i;
      if (i >= 1000000007) {
        i %= 1000000007;
      }
    }
    return res;
  }
 public:
  vector<long long int> k;
  vector<long long int> r;
  void resize(int N) {
    k.resize(N + 2);
    r.resize(N + 2);
    k[0] = 1;
    for (int i = 1; i < N + 2; i++) {
      k[i] = k[i - 1];
      k[i] *= i;
      if (k[i] >= 1000000007) k[i] %= 1000000007;
    }
    long long int al = k[k.size() - 1];
    long long int iv = ppow(k[k.size() - 1], 1000000007 - 2);
    r[k.size() - 1] = iv;
    for (int i = (int)(r.size()) - 2; i >= 0; i--) {
      r[i] = r[i + 1] * (i + 1);
      if (r[i] >= 1000000007) {
        r[i] %= 1000000007;
      }
    }
  }
  long long int C(int a, int b) {
    if (a < b) return 0;
    long long int up = k[a];
    long long int dw = r[b] * r[a - b];
    dw %= 1000000007;
    up *= dw;
    up %= 1000000007;
    return up;
  }
  long long int H(int a, int b) { return C(a + b - 1, b); }
  long long int catalan_number(int n) {
    return (C(2 * n, n) + 1000000007 - C(2 * n, n - 1)) % 1000000007;
  }
};
Combination C;
int mark[1000002];
vector<int> primes;
vector<int> smallestPrimeFactor;
void linearSieve(int n) {
  if (n < 1) n = 1;
  if ((int)smallestPrimeFactor.size() >= n + 1) return;
  int primePiBound = n < 20 ? n - 1 : (int)(n / (log(n * 1.) - 2) + 2);
  primes.assign(primePiBound + 1, numeric_limits<int>::max());
  int P = 0;
  smallestPrimeFactor.assign(n + 1, 0);
  smallestPrimeFactor[1] = 1;
  int n2 = n / 2, n3 = n / 3, n5 = n / 5;
  if (n >= 2) primes[P++] = 2;
  if (n >= 3) primes[P++] = 3;
  for (int q = 2; q <= n; q += 2) smallestPrimeFactor[q] = 2;
  for (int q = 3; q <= n; q += 6) smallestPrimeFactor[q] = 3;
  for (int q = 5; q <= n5; q += 2) {
    if (smallestPrimeFactor[q] == 0) primes[P++] = smallestPrimeFactor[q] = q;
    int bound = smallestPrimeFactor[q];
    for (int i = 2;; ++i) {
      int p = primes[i];
      if (p > bound) break;
      int pq = p * q;
      if (pq > n) break;
      smallestPrimeFactor[pq] = p;
    }
  }
  for (int q = (n5 + 1) | 1; q <= n; q += 2) {
    if (smallestPrimeFactor[q] == 0) primes[P++] = smallestPrimeFactor[q] = q;
  }
  primes.resize(P);
}
void primeFactors(int x, vector<pair<int, int> > &out_v) {
  linearSieve(x);
  out_v.clear();
  while (x != 1) {
    int p = smallestPrimeFactor[x], k = 0;
    x /= p, k++;
    while (x % p == 0) x /= p, k++;
    out_v.push_back(make_pair(p, k));
  }
}
void divisors(int num, vector<int> &v) {
  vector<pair<int, int> > pf;
  primeFactors(num, pf);
  queue<pair<int, int> > stk;
  stk.push(make_pair(1, 0));
  while (!stk.empty()) {
    pair<int, int> f = stk.front();
    stk.pop();
    if (f.second == pf.size()) {
      continue;
    }
    int cur = f.first;
    stk.push(make_pair(f.first, f.second + 1));
    for (int i = 1; i <= pf[f.second].second; i++) {
      cur *= pf[f.second].first;
      v.push_back(cur);
      stk.push(make_pair(cur, f.second + 1));
    }
  }
}
int cc[1000002];
int main() {
  C.resize(2000002);
  linearSieve(1000002);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int a;
    scanf("%d", &a);
    cnt[a]++;
  }
  for (int i = 2; i <= 1000000; i++) {
    int w = 0;
    for (int j = i; j <= 1000000; j += i) {
      w += cnt[j];
    }
    cc[i] = w;
  }
  long long int way2 = 0;
  for (int i = 1000000; i >= 2; i--) {
    long long int num = i;
    int w = cc[i];
    if (w == 0) continue;
    vector<int> er;
    divisors(i, er);
    long long int sum = 0;
    for (int j = 1; j <= w; j++) {
      sum += (long long int)(C.C(w, j)) * j;
      if (sum >= 1000000007) {
        sum %= 1000000007;
      }
    }
    sum += 1000000007 - mark[i];
    sum %= 1000000007;
    for (int k : er) {
      mark[k] += sum;
      if (mark[k] >= 1000000007) {
        mark[k] -= 1000000007;
      }
    }
    way2 += sum * i;
    if (way2 >= 1000000007) {
      way2 %= 1000000007;
    }
  }
  way2 %= 1000000007;
  printf("%lld\n", way2);
  return 0;
}
