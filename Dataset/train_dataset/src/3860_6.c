#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
const int N = 2750132;
const long long INF = 1e9;
const long long MOD = 228228227;
inline int get_max_divisor(int x) {
  int result = 1;
  for (int i = 2; i < sqrt(x) + 1; i++) {
    if (x % i == 0 && x != i) {
      result = max({result, i, x / i});
    }
  }
  return result;
}
inline void solve() {
  int n;
  cin >> n;
  multiset<int> unused;
  vector<int> b(2 * n);
  for (int &x : b) {
    cin >> x;
    unused.insert(x);
  }
  vector<bool> is_prime(N, true);
  for (int i = 2; 1ll * i * i < N; i++) {
    if (!is_prime[i]) continue;
    for (int j = i * i; j < N; j += i) {
      is_prime[j] = false;
    }
  }
  vector<int> primes;
  for (int i = 2; i < N; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }
  sort(b.begin(), b.end());
  vector<int> answer;
  answer.reserve(n);
  for (int i = 2 * n - 1; i > -1; i--) {
    auto it = unused.find(b[i]);
    if (it == unused.end()) continue;
    if (is_prime[b[i]]) {
      auto prime_it = lower_bound(primes.begin(), primes.end(), b[i]);
      int prime_index = distance(primes.begin(), prime_it) + 1;
      auto b_it = unused.find(prime_index);
      unused.erase(b_it);
      answer.push_back(prime_index);
    } else {
      int divisor = get_max_divisor(b[i]);
      auto b_it = unused.find(divisor);
      unused.erase(b_it);
      answer.push_back(b[i]);
    }
    unused.erase(it);
  }
  for (int x : answer) cout << x << ' ';
  cout << '\n';
}
signed main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  solve();
}
