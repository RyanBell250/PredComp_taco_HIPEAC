#include <bits/stdc++.h>
using namespace std;
int n, m;
char s[500][501];
int d[500][26][26];
int pA[500][26][26];
int pB[500][26][26];
int cost(int x, int a, int b) {
  a += 'a';
  b += 'a';
  int res = 0;
  for (int i = 0; i < m; i++)
    if (i & 1)
      res += (s[x][i] != b);
    else
      res += (s[x][i] != a);
  return res;
}
void print(int x, int a, int b) {
  if (x) print(x - 1, pA[x][a][b], pB[x][a][b]);
  a += 'a';
  b += 'a';
  for (int i = 0; i < m; i++)
    if (i & 1)
      putchar(b);
    else
      putchar(a);
  puts("");
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%s", s[i]);
  for (int i = 0; i < 26; i++)
    for (int j = 0; j < 26; j++)
      if (i != j)
        d[0][i][j] = cost(0, i, j);
      else
        d[0][i][j] = -1;
  for (int i = 1; i < n; i++)
    for (int A = 0; A < 26; A++)
      for (int B = 0; B < 26; B++)
        if (A != B) {
          d[i][A][B] = -1;
          int cur_cost = cost(i, A, B);
          for (int a = 0; a < 26; a++)
            if (A != a)
              for (int b = 0; b < 26; b++)
                if (B != b)
                  if (d[i - 1][a][b] != -1 &&
                      (d[i][A][B] == -1 ||
                       d[i][A][B] > d[i - 1][a][b] + cur_cost)) {
                    d[i][A][B] = d[i - 1][a][b] + cur_cost;
                    pA[i][A][B] = a;
                    pB[i][A][B] = b;
                  }
        } else {
          d[i][A][B] = -1;
        }
  int ra = -1, rb = -1;
  for (int i = 0; i < 26; i++)
    for (int j = 0; j < 26; j++)
      if (d[n - 1][i][j] != -1 &&
          (ra == -1 || d[n - 1][ra][rb] > d[n - 1][i][j]))
        ra = i, rb = j;
  printf("%d\n", d[n - 1][ra][rb]);
  print(n - 1, ra, rb);
  return 0;
}
