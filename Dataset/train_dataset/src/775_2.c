#include <bits/stdc++.h>
using namespace std;
int box[505];
int N;
long long ans = 1e18;
map<int, bool> check;
void cal(int sz) {
  if (check.count(sz)) return;
  if (sz <= 0) return;
  long long score = 0;
  bool ok = 1;
  for (int i = 1; i <= N; i++) {
    int dy = box[i] / sz;
    int mod = box[i] % sz;
    score += dy;
    if (dy < mod) ok = 0;
  }
  if (ok) ans = min(ans, score);
  score = 0;
  ok = 1;
  if (sz == 1) return;
  for (int i = 1; i <= N; i++) {
    int dy = box[i] / sz;
    int mod = box[i] % sz;
    score += dy;
    if (mod != sz - 1 && mod != 0) ok = 0;
    if (mod == sz - 1) score++;
  }
  if (ok) ans = min(ans, score);
  sz++;
  score = 0;
  ok = 1;
  for (int i = 1; i <= N; i++)
    if (sz - box[i] > 1) return;
  for (int i = 1; i <= N; i++) {
    int dy = box[i] / sz;
    int mod = box[i] % sz;
    score += dy;
    if (mod == 0) continue;
    if (dy >= sz - mod - 1)
      score++;
    else
      ok = 0;
  }
  if (ok) ans = min(ans, score);
  check[sz] = 1;
}
int main() {
  scanf("%d", &N);
  int sz = 1e9 + 10;
  for (int i = 1; i <= N; i++) {
    scanf("%d", &box[i]);
    sz = min(sz, box[i]);
  }
  for (int i = 1; (long)i * i <= sz; i++) {
    cal(i);
    cal(i - 1);
    cal(i + 1);
    cal(sz / i);
    cal(sz / i - 1);
    cal(sz / i + 1);
  }
  printf("%lld\n", ans);
}
