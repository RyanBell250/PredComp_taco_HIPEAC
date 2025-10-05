#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
const int MOD = 1e9 + 7;
const int INF = 1e9 + 9;
const int MX = 1e5 + 5;
long long n, k;
long long arr[MX];
long long getSum(long long BITree[], long long index) {
  long long sum = 0;
  while (index > 0) {
    sum += BITree[index];
    index -= index & (-index);
  }
  return sum;
}
void updateBIT(long long BITree[], long long n, long long index,
               long long val) {
  while (index <= n) {
    BITree[index] += val;
    index += index & (-index);
  }
}
void convert(long long arr[], long long n) {
  long long temp[n];
  for (long long i = 0; i < n; i++) temp[i] = arr[i];
  sort(temp, temp + n);
  for (long long i = 0; i < n; i++) {
    arr[i] = lower_bound(temp, temp + n, arr[i]) - temp + 1;
  }
}
long long getInvCount(long long arr[], long long n) {
  long long invcount = 0;
  convert(arr, n);
  long long BIT[n + 1];
  for (long long i = 1; i <= n; i++) BIT[i] = 0;
  for (long long i = n - 1; i >= 0; i--) {
    invcount += getSum(BIT, arr[i] - 1);
    updateBIT(BIT, n, arr[i], 1);
  }
  return invcount;
}
int main() {
  cin >> n >> k;
  for (long long i = 0; i < n; i++) arr[i] = i;
  long long op = n / 2;
  long long st = 0;
  long long en = n - 1;
  for (long long i = 0; i < min(op, k); i++) {
    swap(arr[st], arr[en]);
    st++;
    en--;
  }
  long long ans = getInvCount(arr, n);
  cout << ans << endl;
  return 0;
}
