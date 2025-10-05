#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int ts = 1;
  while (ts--) {
    int n, k, q, a, b, z[200002] = {0}, c = 0;
    cin >> n >> k >> q;
    for (int i = int(0); i < int(n); i++) {
      cin >> a >> b;
      z[a]++;
      z[b + 1]--;
    }
    for (int i = int(1); i < int(200002); i++) {
      z[i] += z[i - 1];
    }
    for (int i = int(0); i < int(200002); i++) {
      if (z[i] >= k) c++;
      z[i] = c;
    }
    for (int i = int(0); i < int(q); i++) {
      cin >> a >> b;
      cout << z[b] - z[a - 1] << "\n";
    }
  }
  return 0;
}
