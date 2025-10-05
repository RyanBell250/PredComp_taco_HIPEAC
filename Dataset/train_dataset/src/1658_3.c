#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n;
  cin >> n;
  int num = n, i = 1;
  while (n > 0) {
    num = n;
    n -= i;
    i++;
  }
  cout << num << endl;
  return 0;
}
