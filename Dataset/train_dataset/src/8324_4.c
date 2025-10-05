#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  char H1 = 'a', H2 = 'b';
  int c = 0, cA = 0, cB = 0;
  vector<char> v;
  while (c != n) {
    if (cA == 2) {
      swap(H1, H2);
      cA = 0;
    }
    cA++;
    c++;
    v.push_back(H1);
  }
  for (int i = 0; i < v.size(); i++) cout << v[i];
}
