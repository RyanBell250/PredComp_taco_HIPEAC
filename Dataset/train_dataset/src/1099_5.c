#include <bits/stdc++.h>
using namespace std;
const int N = 30;
bool comp(int first, int second) { return (first > second); }
int f, first, second, n, i, a[N], b[N];
void dfs(int v) {
  f++;
  if (f > 10000000) {
    cout << "NO";
    exit(0);
  }
  if (n - v < max(first, second))
    return;
  else if (v == n) {
    cout << "YES" << endl;
    exit(0);
  }
  for (int i = 0; i < v; i++)
    if (a[v] < a[i]) {
      if (b[i] == 1) second--;
      b[i]++;
      if (b[i] == 1) second++;
      a[i] -= a[v];
      if (a[i] == 1) first--;
      dfs(v + 1);
      if (a[i] == 1) first++;
      if (b[i] == 1) second--;
      b[i]--;
      if (b[i] == 1) second++;
      a[i] += a[v];
    }
}
int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> a[i];
    first += (a[i] != 1);
  }
  sort(a, a + n, comp);
  dfs(1);
  cout << "NO";
}
