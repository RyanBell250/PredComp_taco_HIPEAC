#include <bits/stdc++.h>
using namespace std;
const int N = 60 + 5;
const int mod = 1e9 + 7;
int n, a[N];
int fact[N];
bool mark[N];
int sum;
int k;
int dp[(1 << 15) + 5][N];
int graph[N];
int tmp;
vector<int> vec;
vector<int> prime;
vector<int> other;
void pre() {
  fact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = fact[i - 1] * i;
    fact[i] %= mod;
  }
}
long long power(int a, int b) {
  if (!b) {
    return 1;
  }
  long long ans = power(a, b / 2);
  ans = ans * ans;
  ans = ans % mod;
  if (b % 2) {
    ans = ans * a;
    ans = ans % mod;
  }
  return ans;
}
int choose(int a, int b) {
  long long ans = fact[b];
  ans = ans * power(fact[a], mod - 2);
  ans = ans % mod;
  ans = ans * power(fact[b - a], mod - 2);
  ans = ans % mod;
  return ans;
}
void dfs(int v) {
  mark[v] = 1;
  vec.push_back(v);
  for (int i = 0; i < n; i++) {
    if (!mark[a[i]] && (a[i] % v == 0 || v % a[i] == 0)) {
      dfs(a[i]);
    }
  }
}
void input() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
}
void fnd() {
  int n = vec.size();
  for (int i = 0; i < n; i++) {
    bool isPrime = false;
    for (int j = 0; j < i; j++) {
      if (vec[i] % vec[j] == 0) {
        isPrime = 1;
      }
    }
    if (!isPrime) {
      prime.push_back(vec[i]);
    } else {
      other.push_back(vec[i]);
    }
  }
}
int solver() {
  prime.clear();
  other.clear();
  sort(vec.begin(), vec.end());
  fnd();
  k = other.size();
  if (other.empty()) {
    return 1;
  }
  for (int i = 0; i < other.size(); i++) {
    graph[i] = 0;
    for (int j = 0; j < prime.size(); j++) {
      if (other[i] % prime[j] == 0) {
        graph[i] |= (1 << j);
      }
    }
  }
  memset(dp, 0, sizeof dp);
  for (int i = 0; i < other.size(); i++) {
    dp[graph[i]][1]++;
  }
  for (int mask = 0; mask < (1 << prime.size()); mask++) {
    for (int i = 0; i < k; i++) {
      int cnt = 0;
      for (int j = 0; j < other.size(); j++) {
        if ((mask | graph[j]) == mask) {
          cnt++;
        } else {
          if (graph[j] & mask) {
            dp[mask | graph[j]][i + 1] += dp[mask][i];
            dp[mask | graph[j]][i + 1] %= mod;
          }
        }
      }
      if (cnt > i) {
        dp[mask][i + 1] =
            (dp[mask][i + 1] + 1ll * dp[mask][i] * (cnt - i)) % mod;
      }
    }
  }
  return dp[(1 << (prime.size())) - 1][k];
}
int main() {
  pre();
  input();
  long long ans = 1;
  for (int i = 0; i < n; i++) {
    if (mark[a[i]]) {
      continue;
    }
    vec.clear();
    dfs(a[i]);
    int tmp = solver();
    k = max(k - 1, 0);
    sum += k;
    ans = ans * choose(k, sum);
    ans = ans % mod;
    ans = ans * tmp;
    ans = ans % mod;
  }
  cout << ans << endl;
}
