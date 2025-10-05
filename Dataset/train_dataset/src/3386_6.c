#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
using matrix = vector<vector<int> >;
matrix identity_matrix;
int multiply(int a, int b, int MOD) { return (a * 1LL * b) % MOD; }
int add(int a, int b, int MOD) {
  int ans = a + b;
  if (ans >= MOD) ans -= MOD;
  return ans;
}
matrix multiply(matrix a, matrix b) {
  int n = (int)a.size();
  matrix ans(n, vector<int>(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        ans[i][j] =
            add(ans[i][j], multiply(a[i][k], b[k][j], MOD - 1), MOD - 1);
      }
    }
  }
  return ans;
}
matrix power(matrix a, int n) {
  matrix ans = identity_matrix;
  for (; n; n >>= 1) {
    if (n & 1) ans = multiply(ans, a);
    a = multiply(a, a);
  }
  return ans;
}
int power(int a, int b) {
  int ans = 1;
  for (; b; b >>= 1) {
    if (b & 1) ans = (ans * 1LL * a) % MOD;
    a = (a * 1LL * a) % MOD;
  }
  return ans;
}
struct BabyStepGiantStep {
  int prime;
  int generator;
  unordered_map<int, int> table;
  int middle;
  int inverse_prime;
  int multiply(int a, int b) { return (a * 1LL * b) % prime; }
  int power(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1) {
      if (b & 1) ans = multiply(ans, a);
      a = multiply(a, a);
    }
    return ans;
  }
  BabyStepGiantStep(int _prime, int _generator)
      : prime(_prime), generator(_generator) {
    for (middle = 1; middle * 1LL * middle <= prime; ++middle)
      ;
    createTable();
    inverse_prime = power(generator, prime - 2);
    inverse_prime = power(inverse_prime, middle);
  }
  void createTable() {
    for (int i = 0, value = 1; i <= middle; ++i) {
      table[value] = i;
      value = multiply(value, generator);
    }
  }
  int find_discrete_log(int x) {
    for (int i = 0; i <= middle; ++i) {
      if (table.count(x)) {
        return (table.find(x)->second) + middle * i;
      }
      x = multiply(x, inverse_prime);
    }
    return -1;
  }
};
namespace ExtendedEuclid {
template <typename T>
T gcd(T a, T b) {
  return (a ? gcd(b % a, a) : b);
}
template <typename T>
pair<T, T> extend_euclid(T a, T b) {
  pair<T, T> a_one = {1, 0}, b_one = {0, 1};
  if (!b) return a_one;
  while (a) {
    T q = b / a;
    T r = b % a;
    T dx = b_one.first - q * a_one.first;
    T dy = b_one.second - q * a_one.second;
    b = a;
    a = r;
    b_one = a_one;
    a_one = {dx, dy};
  }
  return b_one;
}
template <typename T>
T solver(T a, T b, T m) {
  T g = gcd(a, m);
  if (b % g != 0) {
    return -1;
  }
  auto coefficients = extend_euclid(a / g, m / g);
  auto ans = (coefficients.first + (m / g)) % (m / g);
  ans = (ans * 1LL * (b / g)) % m;
  return ans;
}
};  // namespace ExtendedEuclid
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int k;
  cin >> k;
  identity_matrix.assign(k, vector<int>(k, 0));
  for (int i = 0; i < k; ++i) identity_matrix[i][i] = 1;
  vector<int> b(k);
  matrix recur(k, vector<int>(k, 0));
  for (int i = 0; i < k; ++i) {
    cin >> b[i];
    b[i] %= (MOD - 1);
    recur[0][i] = b[i];
    if (i) recur[i][i - 1] = 1;
  }
  int n, m;
  cin >> n >> m;
  auto ans = power(recur, n - k);
  int ans_power = ans[0][0];
  int generator = 492294761;
  int phi = MOD - 1;
  BabyStepGiantStep bsgs(MOD, generator);
  int value_m = bsgs.find_discrete_log(m);
  int value_power = ExtendedEuclid::solver(ans_power, value_m, phi);
  if (value_power == -1) {
    cout << -1 << '\n';
    return 0;
  }
  cout << power(generator, value_power) << '\n';
  return 0;
}
