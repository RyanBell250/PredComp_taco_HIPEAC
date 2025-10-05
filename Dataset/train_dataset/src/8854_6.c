#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1.0);
const long long INF = 2e18;
void print(int a[], int n) {
  for (int i = 0; i < n; i++) cout << a[i] << " ";
  cout << "\n";
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int tc = 1;
  while (tc--) {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < (n); i++) cin >> a[i];
    int fromL[n], fromR[n];
    fill(fromL, fromL + n, 1);
    fill(fromR, fromR + n, 1);
    for (int i = (1); i <= (n - 1); i++) {
      if (a[i - 1] < a[i]) fromL[i] = fromL[i - 1] + 1;
    }
    for (int i = (n - 2); i >= (0); i--) {
      if (a[i] < a[i + 1]) fromR[i] = fromR[i + 1] + 1;
    }
    int A, B, C;
    A = B = C = 0;
    for (int i = (0); i <= (n - 2); i++) {
      A = max(fromL[i], A);
    }
    A++;
    for (int i = (n - 2); i >= (1); i--) {
      B = max(fromR[i], B);
    }
    B++;
    for (int i = (1); i <= (n - 2); i++) {
      if (a[i + 1] - a[i - 1] > 1) C = max(C, fromL[i - 1] + fromR[i + 1] + 1);
    }
    cout << max({A, B, C});
  }
}
