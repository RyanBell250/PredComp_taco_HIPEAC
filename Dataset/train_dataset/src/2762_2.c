#include <bits/stdc++.h>
using namespace std;
int solve(int *arr, int val, int n) {
  int c = 0;
  int B[n], i, j;
  for (i = 0; i < n; i++) {
    B[i] = arr[i];
  }
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (B[i] + B[j] == val) {
        c++;
        B[i] = INT_MIN, B[j] = INT_MIN;
      }
    }
  }
  return c;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int arr[n], i, j;
    for (i = 0; i < n; i++) {
      cin >> arr[i];
    }
    int max = 0;
    sort(arr, arr + n);
    for (i = 0; i < n; i++) {
      for (j = i + 1; j < n; j++) {
        int c = solve(arr, arr[i] + arr[j], n);
        if (c > max) max = c;
      }
    }
    cout << max << endl;
  }
}
