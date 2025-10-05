#include <bits/stdc++.h>
using namespace std;
string B[8];
string res[8];
int difer = 999999999;
int solve(int A[8], int b, int n) {
  string min = "999999999";
  string max = "-999999";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < b; j++) {
      res[i].at(j) = B[i].at(A[j]);
    }
    if (min > res[i]) min = res[i];
    if (max < res[i]) max = res[i];
  }
  stringstream ss;
  ss << max << " " << min;
  int mi, ma;
  ss >> ma >> mi;
  return ma - mi;
}
void bt(int b, int inx, int A[8], int n, bool visited[8]) {
  if (inx == b) {
    int res = solve(A, b, n);
    if (res < difer) difer = res;
  } else {
    for (int i = 0; i < b; i++) {
      if (!visited[i]) {
        visited[i] = true;
        int temp = A[inx];
        A[inx] = i;
        bt(b, inx + 1, A, n, visited);
        visited[i] = false;
        A[inx] = temp;
      }
    }
  }
}
int main() {
  int a, b;
  cin >> a >> b;
  for (int i = 0; i < a; i++) {
    cin >> B[i];
    res[i] = B[i];
  }
  int A[8];
  bool visited[8];
  for (int i = 0; i < b; i++) A[i] = i;
  memset(visited, false, sizeof visited);
  bt(b, 0, A, a, visited);
  cout << difer;
  return 0;
}
