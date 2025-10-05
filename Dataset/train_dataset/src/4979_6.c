#include <bits/stdc++.h>
using namespace std;
set<int> ss;
int num[110], g[110][110];
int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    ss.clear();
    for (int i = 0; i < n; i++) {
      num[i] = 1;
      while (true) {
        bool exit = true;
        if (ss.find(num[i]) != ss.end()) exit = false;
        for (int j = 0; j < i; j++)
          if (ss.find(num[j] + num[i]) != ss.end()) exit = false;
        if (exit) break;
        num[i]++;
      }
      ss.insert(num[i]);
      for (int j = 0; j < i; j++) {
        g[i][j] = g[j][i] = num[i] + num[j];
        ss.insert(num[i] + num[j]);
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) printf("%d ", g[i][j]);
      printf("\n");
    }
  }
  return 0;
}
