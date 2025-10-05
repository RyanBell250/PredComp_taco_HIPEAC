#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    int answer = -1;
    sort(a.begin(), a.end());
    for (int i = 1; i <= 1024; i++) {
      for (int j = 0; j < n; j++) {
        b[j] = a[j] ^ i;
      }
      sort(b.begin(), b.end());
      bool good = true;
      for (int k = 0; k < n; k++) {
        if (a[k] != b[k]) {
          good = false;
          break;
        }
      }
      if (good) {
        answer = i;
        break;
      }
    }
    cout << answer << endl;
  }
}
