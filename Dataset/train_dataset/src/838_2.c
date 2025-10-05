#include <bits/stdc++.h>
using namespace std;
const int modulo = 1e9 + 7;
template <class __Ty>
bool mini(__Ty& a, __Ty b) {
  return a > b ? ((a = b) | 1) : (0);
}
template <class __Ty>
bool maxi(__Ty& a, __Ty b) {
  return a < b ? ((a = b) | 1) : (0);
}
template <class __Ty>
__Ty add(__Ty a, __Ty b) {
  return (a + b) % (__Ty(modulo));
}
template <class __Ty>
__Ty sub(__Ty a, __Ty b) {
  __Ty m(modulo);
  return ((a - b) % m + m) % m;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, k, cnt[31] = {0}, c = 0;
  cin >> n >> k;
  for (int i = 0; i <= 30; ++i)
    if (n & (1 << i)) {
      cnt[i]++;
      c++;
    }
  int st = 30;
  while (c < k && st >= 1) {
    if (cnt[st] > 0) {
      cnt[st] -= 1;
      cnt[st - 1] += 2;
      c++;
    } else
      st--;
  }
  if (c < k || c > k)
    cout << "NO";
  else {
    cout << "YES\n";
    for (int i = 0; i <= 30; ++i) {
      for (int j = 0; j < cnt[i]; ++j) cout << (1 << i) << ' ';
    }
  }
  return 0;
}
