#include <bits/stdc++.h>
using namespace std;
int main() {
  const int maxn = 100000;
  int n, k;
  int mas[maxn];
  cin >> n >> k;
  if (k == n) {
    cout << -1;
    return 0;
  }
  for (int i = 0; i < n; i++) mas[i] = i + 1;
  int i = n - 1 - k;
  for (int it = 0; it < (n - k) / 2; it++, i -= 2) swap(mas[i], mas[i - 1]);
  for (int i = 0; i < n; i++) cout << mas[i] << ' ';
  cout << endl;
  return 0;
}
