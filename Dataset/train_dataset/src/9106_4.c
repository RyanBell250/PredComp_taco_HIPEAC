#include <bits/stdc++.h>
using namespace std;
void solve(std::istream &in, std::ostream &out);
int main() {
#ifdef LOCAL
  freopen("../IO/e.in", "r", stdin);

#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#endif
  solve(std::cin, std::cout);
  return 0;
}
int mp[1 << 11][1 << 11];
void solve(std::istream &in, std::ostream &out) {
  int n, m;
  in >> n >> m;
  bool swapped = false;
  if (n < m) swap(n, m), swapped = true;
  mp[1][1] = 1;
  for (int len = 1; len < n; ++len) {
    int L = 1 << len;
    mp[L][L] = 1;
    for (int i = 1; i < L; ++i) {
      for (int j = 1; j < L; ++j) {
        mp[i + L][j + L] = mp[i + L][j] = mp[i][j + L] = mp[i][j];
      }
    }
  }
  if (swapped) swap(n, m);
  for (int i = 1; i < 1 << n; ++i) {
    for (int j = 1; j < 1 << m; ++j) {
      out << char('0' + (!swapped ? mp[i][j] : mp[j][i]));
    }
    out << '\n';
  }
}
