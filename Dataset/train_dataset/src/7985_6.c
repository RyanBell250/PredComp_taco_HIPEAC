#include <bits/stdc++.h>
using namespace std;
const int Inf = 1e9 + 7;
const long long LInf = 1LL * Inf * Inf;
namespace contest {
const int N = 1e6;
void solve() {
  int n, x;
  cin >> n >> x;
  if (n == 1) {
    cout << "YES" << '\n';
    cout << x << '\n';
    return;
  }
  if (n == 2 && x == 0) {
    cout << "NO" << '\n';
    return;
  }
  int s = 0;
  vector<int> res;
  for (int i = 1; i <= n - 2; i++) {
    res.push_back(i);
    s ^= i;
  }
  int t = x ^ s;
  if (t == 0) {
    s = s ^ (n - 2);
    s = s ^ (n - 1);
    t = x ^ s;
    if (n > 2) res.resize(n - 3);
    res.push_back(n - 1);
  }
  int nv = res.empty() ? 1 : res.back() + 1;
  vector<int> ac;
  for (int a = nv; a <= N; a++) ac.push_back(a);
  ac.insert(ac.begin(), 0);
  for (auto a : ac) {
    int b = t ^ a;
    if (b != a && ((nv <= b && b <= N) || b == 0)) {
      cout << "YES" << '\n';
      for (auto v : res) cout << v << " ";
      cout << a << " " << b << '\n';
      return;
    }
  }
  cout << "NO" << '\n';
}
};  
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout.precision(9);
  cout << fixed;
  contest::solve();
  return 0;
}
