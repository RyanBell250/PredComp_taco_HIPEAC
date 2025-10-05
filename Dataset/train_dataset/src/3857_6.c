#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1.);
const long long mod = 1000000007;
inline void prep() {
  cin.tie(0);
  cin.sync_with_stdio(0);
};
int main() {
  prep();
  int n, m;
  cin >> n >> m;
  vector<int> arr[n + 1];
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    arr[a].push_back(b);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < arr[i].size(); j++) {
      if (arr[i][j] < i) {
        arr[i][j] = arr[i][j] + n - i;
      } else {
        arr[i][j] = arr[i][j] - i;
      }
    }
    sort(arr[i].rbegin(), arr[i].rend());
  }
  int manys[n + 1];
  for (int i = 1; i <= n; i++) {
    vector<int> curr = arr[i];
    if (curr.size() == 0) {
      manys[i] = 0;
      continue;
    }
    int lst = curr[curr.size() - 1];
    int sofar = (curr.size() - 1) * n;
    manys[i] = sofar + lst;
  }
  for (int i = 1; i <= n; i++) {
    int maxx2 = 0;
    for (int j = 1; j <= n; j++) {
      if (manys[j] == 0) {
        continue;
      }
      int newdist;
      if (i <= j) {
        newdist = j - i;
      } else {
        newdist = n - i + j;
      }
      if (newdist + manys[j] > maxx2) {
        maxx2 = newdist + manys[j];
      }
    }
    cout << maxx2 << " ";
  }
  return 0;
}
