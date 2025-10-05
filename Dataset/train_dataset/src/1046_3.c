#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:1000000000")
using namespace std;
const int maxn = (int)5e5 + 10;
long long v[maxn];
int g[1 << 16];
int getbit(int x) {
  if (x == 0) {
    return -1;
  }
  int pos = 0;
  while ((x & 1) == 0) {
    x >>= 1;
    pos++;
  }
  return pos;
}
int mask = (1 << 16) - 1;
int get(long long x) {
  if (x == 0) {
    return -1;
  }
  if (g[mask & x] != -1) {
    return g[mask & x];
  }
  x >>= 16;
  if (g[mask & x] != -1) {
    return 16 + g[mask & x];
  }
  x >>= 16;
  if (g[mask & x] != -1) {
    return 32 + g[mask & x];
  }
  x >>= 16;
  return 48 + g[mask & x];
}
int main() {
  int n;
  cin >> n;
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    long long a, b;
    scanf("%I64d %I64d", &a, &b);
    ans ^= a;
    v[i] = a ^ b;
  }
  for (int i = 0; i < (1 << 16); i++) {
    g[i] = getbit(i);
  }
  vector<long long> now;
  for (int j = 0; j <= 63; j++) {
    bool st = false;
    for (int i = 0; i < n; i++) {
      if (get(v[i]) == j) {
        now.push_back(v[i]);
        st = true;
        break;
      }
    }
    if (!st) {
      continue;
    }
    for (int i = 0; i < n; i++) {
      if (get(v[i]) == j) {
        v[i] ^= now.back();
      }
    }
  }
  for (int i = 0; i < (int)now.size(); i++) {
    if (get(now[i]) == get(ans)) {
      ans ^= now[i];
    }
  }
  if (ans != 0) {
    cout << "1/1" << endl;
  } else if (now.empty()) {
    cout << "0/1" << endl;
  } else {
    cout << ((long long)1 << now.size()) - 1 << '/'
         << ((long long)1 << now.size()) << endl;
  }
  return 0;
}
