#include <bits/stdc++.h>
using namespace std;
void run();
int main() {
  ios::sync_with_stdio(0);
  run();
}
long long grundy[1000000];
long long grount[1000000];
long long val[1000000];
set<int> mex;
int most = 0;
void add(int x) {
  if (not(grount[x]++)) mex.erase(x);
  if (mex.empty()) mex.insert(++most);
}
void remove(int x) {
  if (not(--grount[x])) mex.insert(x);
}
void run() {
  long long n, res = 0;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> val[i];
  sort(val, val + n);
  add(0);
  long long l = 2, r = 2;
  for (long long dst = 4; dst < 900000; dst++) {
    while ((r + 1) * (r + 1) <= dst) add(grundy[++r]);
    while (l * l * l * l < dst) remove(grundy[l++]);
    grundy[dst] = *mex.begin();
  }
  for (int i = 0; i < n; i++) {
    if (val[i] < 900000) {
      res ^= grundy[val[i]];
    } else {
      while ((r + 1) * (r + 1) <= val[i]) add(grundy[++r]);
      while (l * l * l * l < val[i]) remove(grundy[l++]);
      res ^= *mex.begin();
    }
  }
  cout << (res ? "Furlo" : "Rublo") << endl;
}
