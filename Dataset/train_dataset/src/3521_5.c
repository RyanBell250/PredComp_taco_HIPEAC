#include <bits/stdc++.h>
using namespace std;
bool b[424], good[424];
int g[424], kd[424], d[424][424], mask[424], q[424], aw[4444444], ax[4444444],
    ay[4444444], az[4444444];
int main() {
  int cnt;
  cin >> cnt;
  int need = 0;
  for (int i = 0; i < cnt; i++) {
    int foo;
    cin >> foo;
    need |= (1 << foo);
    b[foo] = 1;
  }
  if (cnt > 6) {
    cout << 0 << endl;
    return 0;
  }
  int kg = 0;
  for (int i = 0; i < 256; i++) {
    good[i] = 1;
    int x = i;
    mask[i] = 0;
    kd[i] = 0;
    while (x > 0) {
      d[i][kd[i]++] = x % 10;
      if (!b[x % 10]) good[i] = 0;
      mask[i] |= (1 << (x % 10));
      x /= 10;
    }
    if (i == 0 && !b[0]) good[i] = 0;
    if (i == 0) {
      d[i][kd[i]++] = 0;
      mask[i] |= 1;
    }
    if (good[i]) g[kg++] = i;
  }
  int ka = 0;
  for (int w = 0; w < 256; w++)
    if (good[w])
      for (int x = 0; x < 256; x++)
        if (good[x])
          for (int y = 0; y < 256; y++)
            if (good[y]) {
              if ((mask[w] | mask[x] | mask[y]) != need) continue;
              for (int z = 0; z < 256; z++)
                if (good[z]) {
                  int u = 0;
                  for (int i = kd[w] - 1; i >= 0; i--) q[u++] = d[w][i];
                  for (int i = kd[x] - 1; i >= 0; i--) q[u++] = d[x][i];
                  for (int i = kd[y] - 1; i >= 0; i--) q[u++] = d[y][i];
                  for (int i = kd[z] - 1; i >= 0; i--) q[u++] = d[z][i];
                  int ok = 1;
                  for (int i = 0; i < u - i - 1; i++)
                    if (q[i] != q[u - i - 1]) {
                      ok = 0;
                      break;
                    }
                  if (ok) {
                    aw[ka] = w;
                    ax[ka] = x;
                    ay[ka] = y;
                    az[ka] = z;
                    ka++;
                  }
                }
            }
  cout << ka << endl;
  for (int i = 0; i < ka; i++)
    cout << aw[i] << "." << ax[i] << "." << ay[i] << "." << az[i] << endl;
  return 0;
}
