#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, tmp, ans;
  cin >> n;
  ans = 0;
  set<long long> S;
  for (int a = 0; a < 10; a++)
    for (int b = 0; b < 10; b++) {
      for (int mask = 0; mask < (1 << 10); mask++) {
        tmp = 0;
        for (int i = 0; i < 10; i++) {
          if (mask & (1 << i))
            tmp = (tmp * 10) + b;
          else
            tmp = (tmp * 10) + a;
          if (tmp > 0 && tmp <= n) S.insert(tmp);
        }
      }
    }
  cout << S.size() << endl;
  return 0;
}
