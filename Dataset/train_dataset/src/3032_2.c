#include <bits/stdc++.h>
using namespace std;
const int N = 31700;
const int MX = 1e6 + 5;
const int inf = 1e9;
int n, a, b;
set<int> x;
vector<int> tv;
int divisors[MX], ok[MX];
int main() {
  memset(divisors, -1, sizeof(divisors));
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int val;
    scanf("%d", &val);
    x.insert(val);
  }
  scanf("%d%d", &a, &b);
  tv = vector<int>(x.begin(), x.end());
  for (int div : tv) {
    int i = b / div * div;
    if (i < b) i += div;
    for (; i <= a; i += div) {
      divisors[i - b] = max(divisors[i - b], div);
    }
  }
  int maxModified = b, maxVal = 0;
  list<pair<int, int> > process;
  process.push_back({b, 0});
  for (int start = b; start <= a; ++start) {
    while (start > process.front().first) process.pop_front();
    ok[start - b] = process.front().second;
    if (divisors[start - b] != -1) {
      int val = divisors[start - b];
      if (start + val - 1 > maxModified) {
        maxModified = start + val - 1;
      }
    }
    if (maxModified <= start) {
      process.push_back({start + 1, ok[start - b] + 1});
    } else {
      process.push_back({maxModified, ok[start - b] + 1});
    }
  }
  printf("%d\n", ok[a - b]);
  return 0;
}
