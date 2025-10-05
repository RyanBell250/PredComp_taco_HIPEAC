#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, c;
int sol[200][200];
char sal[500][500];
char buff[6][2][3] = {{"..", ".."},   {"\\#", ".\\"}, {"#/", "/."},
                      {"\\.", "#\\"}, {"./", "/#"},   {"##", "##"}};
void copiar(int ii, int jj, int k) {
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) sal[2 * ii + i][2 * jj + j] = buff[k][i][j];
}
void black(int i, int j) {
  if (not(i >= 0 and i < n and j >= 0 and j < m)) return;
  if (sol[i][j] != 0) return;
  sol[i][j] = 5;
  black(i + 1, j);
  black(i - 1, j);
  black(i, j + 1);
  black(i, j - 1);
}
void propaga(int i, int j, int val) {
  if (i >= n) return;
  sol[i][j] = val;
  if (val == 1)
    val = 3;
  else if (val == 3)
    val = 1;
  else if (val == 2)
    val = 4;
  else if (val == 4)
    val = 2;
  propaga(i + 1, j, val);
}
int main() {
  cin >> n >> m >> a >> b >> c;
  if (a % m == 0) {
    int i = a / m;
    for (int j = 0; j < m; j++) sol[i][j] = j % 2 == 0 ? 1 : 2;
  } else {
    int i = a / m;
    int posj = a % m;
    for (int j = posj; j < m; j++) sol[i][j] = (j - posj) % 2 == 0 ? 2 : 1;
    for (int j = posj - 1; j >= 0; j--)
      sol[i + 1][j] = (posj - 1 - j) % 2 == 0 ? 2 : 1;
  }
  black(0, 0);
  int q = c - m;
  if (q > 0) {
    if (q / m == 0) {
      int posj = m - q;
      for (int j = posj; j < m; j++)
        sol[n - 1][j] = (j - posj) % 2 == 0 ? 4 : 3;
    } else if (q % m == 0) {
      int i = n - q / m;
      for (int j = 0; j < m; j++)
        if (j % 2 == 0)
          propaga(i, j, 4);
        else
          propaga(i, j, 3);
    } else {
      int i = n - q / m - 1;
      int posj = m - q % m;
      for (int j = posj; j < m; j++) propaga(i, j, (j - posj) % 2 == 0 ? 4 : 3);
      for (int j = posj - 1; j >= 0; j--)
        propaga(i + 1, j, (posj - 1 - j) % 2 == 0 ? 4 : 3);
    }
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) copiar(i, j, sol[i][j]);
  for (int i = 0; i < 2 * n; i++) {
    for (int j = 0; j < 2 * m; j++) cout << sal[i][j];
    cout << endl;
  }
}
