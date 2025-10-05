#include <bits/stdc++.h>
using namespace std;
const int MX = (1 << 20);
unsigned long long x;
int a[MX], b[MX], n, d;
unsigned long long getNextX() {
  x = (x * 37 + 10007) % 1000000007;
  return x;
}
void initAB() {
  for (int i = 0; i < n; i = i + 1) {
    a[i] = i + 1;
  }
  for (int i = 0; i < n; i = i + 1) {
    swap(a[i], a[getNextX() % (i + 1)]);
  }
  for (int i = 0; i < n; i = i + 1) {
    if (i < d)
      b[i] = 1;
    else
      b[i] = 0;
  }
  for (int i = 0; i < n; i = i + 1) {
    swap(b[i], b[getNextX() % (i + 1)]);
  }
}
int ans[MX];
pair<int, int> arr[MX];
int main() {
  cin >> n >> d >> x;
  initAB();
  set<int> S, ones;
  for (int j = 0; j < n; j++) {
    if (b[j]) ones.insert(j);
    arr[j] = {a[j], j};
    S.insert(j);
  }
  if (ones.empty()) {
    for (int j = 0; j < n; j++) puts("0");
    return 0;
  }
  sort(arr, arr + n);
  reverse(arr, arr + n);
  for (int j = 0; j < n; j++) {
    int idx = arr[j].second;
    int cur = idx + *ones.begin();
    auto it = S.lower_bound(cur);
    while (1) {
      if (it == S.end()) break;
      int pos = *it;
      if (b[pos - idx]) {
        ans[pos] = arr[j].first;
        S.erase(pos);
      }
      auto iit = ones.upper_bound(pos - idx);
      if (iit == ones.end()) break;
      it = S.lower_bound(idx + *iit);
    }
  }
  for (int j = 0; j < n; j++) printf("%d\n", ans[j]);
}
