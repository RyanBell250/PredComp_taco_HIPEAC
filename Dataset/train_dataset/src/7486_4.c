#include <bits/stdc++.h>
using namespace std;
int spf[2000005];
void sieve() {
  spf[1] = 1;
  for (int i = 2; i <= 2e6; i++) spf[i] = i;
  for (int i = 4; i <= 2e6; i += 2) spf[i] = 2;
  for (int i = 3; i * i <= 2e6; i += 2) {
    if (spf[i] == i) {
      for (int j = i * i; j <= 2e6; j += i)
        if (spf[j] == j) spf[j] = i;
    }
  }
}
int main() {
  sieve();
  int n;
  cin >> n;
  int arr[n];
  for (int i = 0; i < n; i++) cin >> arr[i];
  sort(arr, arr + n);
  vector<int> ans;
  if (arr[0] == 1) {
    for (int i = 0; i < n; i++)
      if (arr[i] == 1) ans.push_back(1);
    for (int j = 0; j < n; j++) {
      if (arr[j] != 1 && spf[arr[j] + 1] == arr[j] + 1) {
        ans.push_back(arr[j]);
        break;
      }
    }
  }
  if (ans.size() <= 1) {
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (spf[arr[i] + arr[j]] == arr[i] + arr[j])
          return cout << 2 << endl << arr[i] << ' ' << arr[j], 0;
      }
    }
  }
  if (ans.size() == 0) return cout << 1 << endl << arr[0], 0;
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++) cout << ans[i] << ' ';
  return 0;
}
