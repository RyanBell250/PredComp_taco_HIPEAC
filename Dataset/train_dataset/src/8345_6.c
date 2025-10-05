#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
long long a[maxn];
int main() {
  int n, m;
  cin >> n >> m;
  long long sum = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum += 1LL * a[i];
  }
  if (sum + n - 1 == m)
    cout << "YES";
  else
    cout << "NO";
}
