#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;
const long long INF = 4e18;
const int inf = 2e9;
const int N = 5e5 + 5;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a / gcd(a, b) * b; }
vector<int> pos;
bool ada[N];
int ans, day;
int main(void) {
  int d, i, j, n, x;
  scanf("%d %d", &n, &d);
  pos.push_back(0);
  for (i = 0; i < n; ++i) {
    scanf("%d", &x);
    int len = (int)pos.size();
    for (j = 0; j < len; ++j)
      if (!ada[pos[j] + x]) {
        pos.push_back(pos[j] + x);
        ada[pos[j] + x] = 1;
      }
  }
  sort(pos.begin(), pos.end());
  i = 0;
  while (i < pos.size()) {
    while (i < pos.size() && ans + d >= pos[i]) i++;
    if (ans != pos[i - 1]) {
      ans = pos[i - 1];
      day++;
    } else
      break;
  }
  printf("%d %d\n", ans, day);
  return 0;
}
