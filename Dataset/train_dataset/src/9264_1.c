#include <bits/stdc++.h>
using namespace std;
vector<int> p(400001, 1);
vector<int> ans;
void sieve() {
  p[1] = 0;
  for (int i = 2; i < 400001; i++) {
    if (p[i] == 0) continue;
    ans.push_back(i);
    for (int j = 2; j * i < 400001; j++) p[i * j] = 0;
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, x = 0, y = 0, a;
  cin >> n;
  vector<int> ho;
  sieve();
  for (int i = 0; i < n; i++) {
    cin >> a;
    if (a == 1)
      x++;
    else
      y++;
  }
  int curr = ans[0], ind = 1, csum = 0, ct = 0, d;
  while (ct < n) {
    if (x == 0) {
      while (y) {
        ho.push_back(2);
        y--;
        ct++;
      }
      continue;
    }
    if (y == 0) {
      while (x) {
        ho.push_back(1);
        x--;
        ct++;
      }
      continue;
    }
    d = curr - csum;
    if (d == 0) {
      curr = ans[ind];
      ind++;
      d = curr - csum;
    }
    if (d % 2 == 0) {
      ho.push_back(2);
      csum += 2;
      ct++;
      y--;
    } else {
      ho.push_back(1);
      csum++;
      ct++;
      x--;
    }
  }
  for (int i = 0; i < n; i++) cout << ho[i] << " ";
  return 0;
}
