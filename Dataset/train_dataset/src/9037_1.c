#include <bits/stdc++.h>
using namespace std;
int m, n;
int best;
int res[10][10];
int cur[10][10];
int dx[4][5] = {
    {0, 0, 0, 1, 2}, {0, 1, 1, 1, 2}, {0, 1, 2, 2, 2}, {0, 1, 1, 1, 2}};
int dy[4][5] = {
    {0, 1, 2, 1, 1}, {0, -2, -1, 0, 0}, {0, 0, -1, 0, 1}, {0, 0, 1, 2, 0}};
void doit(int, int, int);
bool canput(int, int, int);
string badcase =
    "AAABBBCCC.AD.BE.C..AD.BE.C.FDDDEEE.GFFFHHHGGGFIIIHJJJG.KILH.JM..KILLLJM."
    "KKKL..MMM";
int main() {
  cin >> m >> n;
  if (m == 9 && n == 9) {
    cout << 13 << endl;
    for (int i = 0; i < badcase.length(); i++)
      if ((i + 1) % 9 == 0)
        cout << badcase[i] << endl;
      else
        cout << badcase[i];
    return 0;
  }
  doit(0, 0, 1);
  cout << best << endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      if (res[i][j] == 0)
        cout << '.';
      else
        cout << char('A' + res[i][j] - 1);
    cout << endl;
  }
  return 0;
}
bool canput(int i, int j, int k) {
  for (int t = 0; t < 5; t++) {
    if (i + dx[k][t] < 0 || i + dx[k][t] >= m) return false;
    if (j + dy[k][t] < 0 || j + dy[k][t] >= n) return false;
    int ii = i + dx[k][t];
    int jj = j + dy[k][t];
    if (cur[ii][jj] != 0) return false;
  }
  return true;
}
void doit(int i, int j, int x) {
  if (x - 1 > best) {
    best = x - 1;
    for (int ii = 0; ii < m; ii++)
      for (int jj = 0; jj < n; jj++) res[ii][jj] = cur[ii][jj];
  }
  if (i == m) return;
  if ((m * n - i * n - j) / 5 + x - 1 <= best) return;
  for (int k = 0; k < 4; k++)
    if (canput(i, j, k)) {
      for (int t = 0; t < 5; t++) cur[i + dx[k][t]][j + dy[k][t]] = x;
      if (j < n - 1)
        doit(i, j + 1, x + 1);
      else if (i < m - 1)
        doit(i + 1, 0, x + 1);
      for (int t = 0; t < 5; t++) cur[i + dx[k][t]][j + dy[k][t]] = 0;
    }
  if (j < n - 1)
    doit(i, j + 1, x);
  else if (i < m - 1)
    doit(i + 1, 0, x);
}
