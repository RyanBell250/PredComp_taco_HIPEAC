#include <bits/stdc++.h>
const long long mod = 1000000007;
using namespace std;
vector<long long> child0, child1, claw;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long n;
  cin >> n;
  vector<long long> a(n);
  long long max = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] > max) max = a[i];
  }
  child0.resize(max + 1);
  child1.resize(max + 1);
  claw.resize(max + 1);
  child0[0] = 1;
  child0[1] = 1;
  child0[2] = 3;
  child1[0] = 0;
  child1[1] = 1;
  child1[2] = 1;
  claw[0] = 0;
  claw[1] = 0;
  claw[2] = 1;
  for (int i = 3; i < max; i++) {
    claw[i] = (child1[i - 1] + claw[i - 3]) % mod;
    child0[i] = (child0[i - 1] + 2 * child1[i - 1]) % mod;
    child1[i] = (child0[i - 1]) % mod;
  }
  for (int i = 0; i < n; i++) {
    cout << (4 * claw[a[i] - 1]) % mod << "\n";
  }
  return 0;
}
