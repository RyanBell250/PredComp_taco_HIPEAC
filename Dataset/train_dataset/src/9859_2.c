#include <bits/stdc++.h>
using namespace std;
const int C = 200001;
vector<vector<int> > tab(C);
vector<vector<int> > e(C);
int ij[C], a, b, n, v[C], s[C], es[C], ve[C], is = 0, par[C], m, i;
bool check[C];
int main() {
  scanf("%d", &n);
  for (i = 1; i <= n; i++) scanf("%d", &v[i]);
  scanf("%d", &m);
  for (int z = 1; z <= m; z++)
    scanf("%d %d", &a, &b), tab[a].push_back(b), tab[b].push_back(a),
        e[a].push_back(z), e[b].push_back(-z), ij[a]++, ij[b]++;
  for (i = 1; i <= n; i++) {
    if (check[i] == 0) {
      check[i] = 1;
      s[0] = i, is = 1;
      while (is > 0) {
        a = s[is - 1];
        if (ij[a] > 0 && check[tab[a][ij[a] - 1]] == 1)
          ij[a]--;
        else if (ij[a] > 0)
          s[is] = tab[a][ij[a] - 1], es[is] = e[a][ij[a] - 1], check[s[is]] = 1,
          par[s[is]] = a, is++, ij[a]--;
        else {
          if (is > 1 && es[is - 1] > 0)
            ve[es[is - 1]] = v[a], v[par[a]] += v[a], v[a] = 0;
          else if (is > 1)
            ve[-es[is - 1]] = -v[a], v[par[a]] += v[a], v[a] = 0;
          is--;
        }
      }
    }
  }
  for (i = 1; i <= n; i++) {
    if (v[i] != 0) {
      printf("Impossible\n");
      return 0;
    }
  }
  printf("Possible\n");
  for (i = 1; i <= m; i++) printf("%d\n", ve[i]);
  return 0;
}
