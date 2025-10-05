#include <bits/stdc++.h>
using namespace std;
vector<long long int> v;
void solve(long long int n) {
  if (n % 2 == 0) v.push_back(2);
  while (n % 2 == 0) n /= 2;
  for (int i = 3; i <= sqrt(n); i += 2) {
    if (n % i == 0) v.push_back(i);
    while (n % i == 0) n /= i;
  }
  if (n > 2) v.push_back(n);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  long long int t, n, i;
  cin >> n;
  solve(n);
  if (v.size() == 1)
    cout << v[0] << endl;
  else
    cout << "1" << endl;
}
