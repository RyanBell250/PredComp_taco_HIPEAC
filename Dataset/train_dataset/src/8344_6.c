#include <bits/stdc++.h>
using namespace std;
vector<int> d;
void find(int x) {
  for (int i = 1; i * i <= x; i++) {
    if (x % i) continue;
    if (x / i == i)
      d.push_back(x / i);
    else
      d.push_back(x / i), d.push_back(i);
  }
}
int main(void) {
  int p, k;
  cin >> p >> k;
  int ans = -1;
  while (k > p) {
    d.clear();
    find(k);
    ans = k;
    for (int j = 0; j < d.size(); j++)
      if (d[j] != 1 && d[j] <= p) ans = -1;
    if (ans != -1) break;
    k--;
  }
  cout << ans << "\n";
}
