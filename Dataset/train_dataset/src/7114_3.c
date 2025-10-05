#include <bits/stdc++.h>
using namespace std;
int n, m;
std::vector<int> b[200010];
int main() {
  scanf("%d%d", &n, &m);
  int temp;
  for (int r = 0; r < n; r++) {
    b[r].push_back(0);
    for (int c = 1; c <= m; c++) {
      scanf("%d", &temp);
      b[r].push_back(temp);
    }
  }
  int total = 0;
  for (int c = 1; c <= m; c++) {
    int level = c % m;
    int lowBound = 0;
    std::map<int, int> numMap;
    numMap.clear();
    for (int r = 0; r < n; r++) {
      if (b[r][c] % m != level) {
        lowBound++;
        b[r][c] = -1;
        continue;
      } else {
        b[r][c] = (b[r][c] - c) / m;
        if (b[r][c] >= n) {
          lowBound++;
          continue;
        }
        int diffNum = r - b[r][c];
        while (diffNum < 0) {
          diffNum = diffNum + n;
        }
        numMap[diffNum]++;
      }
    }
    int minLine = n;
    int curLine;
    for (int r = 0; r < n; r++) {
      curLine = r + n - numMap[r];
      if (minLine > curLine) minLine = curLine;
    }
    total = total + minLine;
  }
  printf("%d\n", total);
  return 0;
}
