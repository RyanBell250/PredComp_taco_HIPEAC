#include <bits/stdc++.h>
using namespace std;
void norm(long long &x) {
  while (x < 0) x += (long long)(1e9 + 7);
  if (x >= (long long)(1e9 + 7)) x %= (long long)(1e9 + 7);
}
long long power(long long a, long long b) {
  long long ans = 1;
  while (b) {
    if (b % 2) ans = (ans * a);
    norm(ans);
    a = (a * a);
    norm(a);
    b /= 2;
  }
  return ans % (long long)(1e9 + 7);
}
long long inv(long long a) { return power(a, (long long)(1e9 + 7) - 2); }
struct BIT {
  vector<long long> ar;
  int sz;
  BIT(int n) {
    ar.resize(n + 1);
    sz = n;
    for (int i = 1; i <= n; i++) ar[i] = 1;
  }
  void update(int idx, int k) {
    for (int i = idx; i <= sz; i += (i & -i)) {
      ar[i] = ar[i] * k;
      norm(ar[i]);
    }
  }
  long long query(int idx) {
    long long ans = 1;
    for (int i = idx; i > 0; i -= (i & -i)) {
      ans *= ar[i];
      norm(ans);
    }
    return ans;
  }
};
vector<int> is_prime((int)(1000000) + 9, 0);
vector<int> small_p((int)(1000000) + 9, 0);
void sieve() {
  is_prime[1] = 1;
  small_p[1] = 1;
  for (int i = 2; i <= (int)(1000000); i++) {
    if (is_prime[i] == 0) {
      small_p[i] = i;
      if (i <= sqrt((int)(1000000)) + 5)
        for (int j = i * i; j <= (int)(1000000); j += i) {
          is_prime[j] = 1;
          small_p[j] = i;
        }
    }
  }
}
vector<int> factorize(int n) {
  vector<int> vec;
  while (n != 1) {
    int x = small_p[n];
    vec.push_back(x);
    while (n % x == 0) n /= x;
  }
  return vec;
}
int main() {
  int n;
  cin >> n;
  BIT bit1(n);
  BIT bit2(n);
  sieve();
  vector<int> ar(n + 1);
  for (int i = 1; i <= n; i++) scanf("%d", &ar[i]);
  int q;
  scanf("%d", &q);
  vector<pair<int, int> > query(q + 1);
  vector<long long> ans(q + 1);
  vector<vector<int> > vec(n + 1);
  for (int i = 1; i <= q; i++) {
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);
    query[i] = {x, y};
    vec[x].push_back(i);
  }
  vector<int> last((int)(1000000) + 1);
  for (int i = 1; i <= (int)(1000000); i++) last[i] = n + 1;
  for (int i = n; i > 0; i--) {
    int x = ar[i];
    vector<int> pri = factorize(x);
    bit1.update(i, x);
    for (int j = 0; j < pri.size(); j++) {
      int num = pri[j];
      if (last[num] <= n) {
        long long k = num * inv(num - 1);
        norm(k);
        bit2.update(last[num], k);
      }
      last[num] = i;
      long long tmp = (num - 1) * inv(num);
      norm(tmp);
      bit2.update(i, tmp);
    }
    for (int j = 0; j < vec[i].size(); j++) {
      int idx = vec[i][j];
      int R = query[idx].second;
      long long res = bit1.query(R) * bit2.query(R);
      norm(res);
      ans[idx] = res;
    }
  }
  for (int i = 1; i <= q; i++) printf("%d\n", (int)ans[i]);
  return 0;
}
