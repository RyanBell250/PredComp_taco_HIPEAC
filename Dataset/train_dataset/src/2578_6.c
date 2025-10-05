#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n;
  cin >> n;
  long long b[n];
  pair<long long, long long> arr[n];
  for (long long i = 0; i < n; i++) {
    cin >> b[i];
    arr[i].first = b[i] - i + 200000;
    arr[i].second = b[i];
  }
  sort(arr, arr + n);
  long long maxi = 0;
  long long i = -1;
  while (i < (n - 1)) {
    i++;
    long long c = 0;
    c += arr[i].second;
    while (arr[i].first == arr[i + 1].first) {
      c += arr[i + 1].second;
      i++;
    }
    maxi = max(c, maxi);
  }
  if (n == 1) {
    cout << b[0];
  } else {
    cout << maxi;
  }
}
