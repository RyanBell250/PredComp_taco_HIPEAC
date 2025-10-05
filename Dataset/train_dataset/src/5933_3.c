#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int f1[maxn], f2[maxn];
int find1(int a) {
  if (a != f1[a]) {
    a = f1[a] = find1(f1[a]);
  }
  return a;
}
int find2(int a) {
  if (a != f2[a]) {
    a = f2[a] = find2(f2[a]);
  }
  return a;
}
int main() {
  int n, m1, m2;
  cin >> n >> m1 >> m2;
  for (int i = 0; i <= n; i++) {
    f1[i] = f2[i] = i;
  }
  for (int i = 0; i < m1; i++) {
    int a, b;
    cin >> a >> b;
    f1[find1(b)] = find1(a);
  }
  for (int i = 0; i < m2; i++) {
    int a, b;
    cin >> a >> b;
    f2[find2(b)] = find2(a);
  }
  int cnt = 0;
  int x[maxn];
  int y[maxn];
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      int a = find1(i);
      int b = find1(j);
      if (a != b) {
        int a2 = find2(i);
        int b2 = find2(j);
        if (a2 != b2) {
          f1[b] = a;
          f2[b2] = a2;
          x[cnt] = i;
          y[cnt] = j;
          cnt++;
        }
      }
    }
  }
  cout << cnt << endl;
  for (int i = 0; i < cnt; i++) {
    cout << x[i] << " " << y[i] << endl;
  }
  return 0;
}
