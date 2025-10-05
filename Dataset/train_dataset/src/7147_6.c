#include <bits/stdc++.h>
using namespace std;
template <class T>
T min3(T a, T b, T c) {
  return min(a, min(b, c));
};
template <class T>
T max3(T a, T b, T c) {
  return max(a, max(b, c));
};
void openFile() {
  freopen("/home/khaihanhdk/MyWorkplace/cpp file/a.inp", "r", stdin);
}
const int m = 20;
const int kk = (1 << 20) - 1;
const long long e9 = 1e9 + 7;
void computeS(long long* f) {
  for (int i = 0; i < m; i++)
    for (int j = 0; j < (1 << m); j++)
      if ((j >> i) & 1) f[j] += f[j ^ (1 << i)];
}
int powm(int k) {
  if (k % 2 == m % 2) return 1;
  return -1;
}
int countbit(int x) {
  int res = 0;
  for (int i = 0; i < m; i++)
    if ((x >> i) & 1) res++;
  return res;
}
long long cc[(1 << 20) + 100];
long long pow2[(1 << 20) + 100];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int a;
    scanf("%d", &a);
    cc[(~a) & kk]++;
  }
  computeS(cc);
  pow2[0] = 1LL;
  for (int i = 1; i < (1 << m); i++) pow2[i] = (pow2[i - 1] * 2) % e9;
  long long res = 0;
  for (int i = 0; i < (1 << m); i++)
    res = (res + pow2[cc[i]] * powm(countbit(i)) + e9) % e9;
  cout << res;
}
