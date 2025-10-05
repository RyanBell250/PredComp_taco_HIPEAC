#include <bits/stdc++.h>
using namespace std;
const long long sze = 3e5 + 50, INF = 1e18 + 500, mod = 998244353;
const long double eps = 5e-10, PI = 2 * acos(0.0);
template <class T>
void show(const vector<T> &a) {
  for (T x : a) cout << x << " ";
  cout << '\n';
}
vector<long long> vertices[sze];
vector<char> visit(sze, false);
vector<long long> arr(sze, 0);
long long n, m, k, t;
long long d = 0;
long long cnt = 0;
string s;
vector<long long> col(sze, 0);
vector<long long> sum(sze, INF);
long long x, y;
long long dp[2][2][210];
inline long long mode(long long val) {
  if (val < 0) {
    val %= mod;
    if (val < 0) val += mod;
    return val;
  }
  return val % mod;
}
void add(long long p, long long type, long long val, long long l, long long r) {
  if (r < l) return;
  val = mode(val);
  dp[p][type][l] = mode(dp[p][type][l] + val);
  dp[p][type][r + 1] = mode(dp[p][type][r + 1] - val);
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin >> n;
  for (long long i = 0; i < n; i++) {
    cin >> arr[i];
  }
  long long c = 0, p = 1;
  if (arr[0] == -1) {
    for (long long i = 1; i < 201; i++) {
      dp[c][0][i]++;
    }
  } else {
    dp[c][0][arr[0]]++;
  }
  for (long long i = 1; i < n; i++) {
    if (arr[i] == -1) {
      for (long long j = 1; j < 201; j++) {
        add(p, 1, dp[c][0][j] + dp[c][1][j], j, j);
        add(p, 0, dp[c][0][j] + dp[c][1][j], j + 1, 200);
        add(p, 1, dp[c][1][j], 1, j - 1);
      }
    } else {
      for (long long j = 1; j < 201; j++) {
        if (j == arr[i]) {
          add(p, 1, dp[c][0][j], j, j);
          add(p, 1, dp[c][1][j], j, j);
          continue;
        }
        if (j < arr[i]) {
          add(p, 0, dp[c][1][j] + dp[c][0][j], arr[i], arr[i]);
        } else {
          add(p, 1, dp[c][1][j], arr[i], arr[i]);
        }
      }
    }
    for (long long j = 1; j < 201; j++) {
      dp[p][0][j] = mode(dp[p][0][j] + dp[p][0][j - 1]);
      dp[p][1][j] = mode(dp[p][1][j] + dp[p][1][j - 1]);
    }
    for (long long j = 0; j < 201; j++) {
      dp[c][0][j] = 0;
      dp[c][1][j] = 0;
    }
    swap(c, p);
  }
  cnt = 0;
  for (long long j = 1; j < 201; j++) {
    cnt = mode(cnt + dp[c][1][j]);
  }
  cout << cnt;
  return 0;
}
