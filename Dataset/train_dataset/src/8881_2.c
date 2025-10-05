#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int y1, y2, y3, m1, m2, m3, c1, c2, c3;
  cin >> y1 >> y2 >> y3;
  cin >> m1 >> m2 >> m3;
  cin >> c1 >> c2 >> c3;
  long maxx = 1000000;
  for (int i = y1; i <= 1000; i++)
    for (int j = y2; j <= 200; j++)
      for (int k = y3; k <= 100; k++) {
        int kt = 0, t1 = i, t2 = k, t3 = m1, t4 = m3, dem = 0;
        while (true) {
          if (j <= t4) break;
          if (m2 > t2) {
            t1 = t1 + t2 - m2;
          }
          if (j > t4) {
            t3 = t3 + t4 - j;
          }
          if (t1 > 0 && t3 <= 0) {
            kt = 1;
            break;
          }
          if (t1 < 0) break;
        }
        if (kt == 1) {
          long tam = (i - y1) * c1 + (j - y2) * c2 + (k - y3) * c3;
          if (maxx > tam) {
            maxx = tam;
          }
        }
      }
  cout << maxx << endl;
}
