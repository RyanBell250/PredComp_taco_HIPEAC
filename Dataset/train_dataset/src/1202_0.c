#include <bits/stdc++.h>
using namespace std;
const int N = 505, M = 105;
int n, m, k, top;
int a[N], id[N], e[N][N], deg[N];
double d[N][N], v[N * N], prob[N];
int x[N * N], y[N * N], type[N * N];
struct mat {
  double a[M][M];
  mat() { memset(a, 0, sizeof(a)); }
} tr, ans;
mat operator*(mat a, mat b) {
  mat ans;
  for (int i = (int)(1); i <= (int)(*id); i++)
    for (int j = (int)(1); j <= (int)(*id); j++)
      for (int k = (int)(1); k <= (int)(*id); k++)
        ans.a[i][j] += a.a[i][k] * b.a[k][j];
  return ans;
}
void gauss() {
  for (int i = (int)(1); i <= (int)(n); i++) {
    int p = -1;
    for (int j = (int)(i); j <= (int)(n); j++)
      if (fabs(d[j][i]) > 1e-6) {
        p = j;
        break;
      }
    if (p != i) {
      for (int k = (int)(1); k <= (int)(n); k++) swap(d[i][k], d[p][k]);
      type[++top] = 1;
      x[top] = i;
      y[top] = p;
    }
    for (int j = (int)(1); j <= (int)(n); j++)
      if (j != i) {
        double tmp = -d[j][i] / d[i][i];
        type[++top] = 2;
        x[top] = j;
        y[top] = i;
        v[top] = tmp;
        for (int k = (int)(i); k <= (int)(n); k++) d[j][k] += tmp * d[i][k];
      }
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = (int)(1); i <= (int)(n); i++) scanf("%d", &a[i]);
  for (int i = (int)(1); i <= (int)(n); i++)
    if (a[i]) id[i] = ++*id;
  for (int i = (int)(1); i <= (int)(m); i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    ++deg[x];
    ++deg[y];
    ++e[x][y];
    ++e[y][x];
  }
  for (int i = (int)(1); i <= (int)(n); i++)
    for (int j = (int)(1); j <= (int)(n); j++)
      if (!a[i]) d[j][i] = 1.0 * e[j][i] / deg[j];
  for (int i = (int)(1); i <= (int)(n); i++) d[i][i]--;
  gauss();
  for (int i = (int)(1); i <= (int)(n); i++)
    if (id[i]) {
      for (int j = (int)(1); j <= (int)(n); j++)
        prob[j] = -1.0 * e[j][i] / deg[j];
      for (int j = (int)(1); j <= (int)(top); j++) {
        if (type[j] == 1)
          swap(prob[x[j]], prob[y[j]]);
        else
          prob[x[j]] += v[j] * prob[y[j]];
      }
      for (int j = (int)(1); j <= (int)(n); j++) prob[j] /= d[j][j];
      ans.a[1][id[i]] = prob[1];
      for (int j = (int)(1); j <= (int)(n); j++)
        if (id[j]) tr.a[id[j]][id[i]] = prob[j];
    }
  for (k -= 2; k; k /= 2, tr = tr * tr)
    if (k & 1) ans = ans * tr;
  printf("%.15lf\n", ans.a[1][id[n]]);
}
