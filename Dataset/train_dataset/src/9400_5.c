#include <bits/stdc++.h>
using namespace std;
const int N = 8;
struct point {
  long long coordinate[3];
  point operator-(const point &p) {
    point res;
    for (int i = 0; i < 3; ++i) {
      res.coordinate[i] = coordinate[i] - p.coordinate[i];
    }
    return res;
  }
} points[100];
long long dis(point p) {
  long long res = 0;
  for (int i = 0; i < 3; ++i) {
    res += p.coordinate[i] * p.coordinate[i];
  }
  return res;
}
bool check(int pos) {
  int cnt = 0;
  long long d[100];
  for (int i = 0; i < N; ++i) {
    if (i == pos) continue;
    d[cnt++] = dis(points[pos] - points[i]);
  }
  sort(d, d + 7);
  if (d[0] == 0) {
    return false;
  }
  if (d[0] != d[1] || d[0] != d[2]) {
    return false;
  }
  if (d[3] != d[4] || d[3] != d[5]) {
    return false;
  }
  if (d[0] * 2 != d[3] || d[0] * 3 != d[6]) {
    return false;
  }
  return true;
}
bool judge() {
  for (int i = 0; i < N; i++) {
    if (!check(i)) return false;
  }
  printf("YES\n");
  for (int i = 0; i < N; ++i) {
    printf("%lld %lld %lld\n", points[i].coordinate[0], points[i].coordinate[1],
           points[i].coordinate[2]);
  }
  return true;
}
bool dfs(int cur) {
  if (cur == N) return judge();
  sort(points[cur].coordinate, points[cur].coordinate + 3);
  do {
    if (dfs(cur + 1)) {
      return true;
    }
  } while (
      next_permutation(points[cur].coordinate, points[cur].coordinate + 3));
  return false;
}
int main() {
  for (int i = 0; i < N; ++i) {
    scanf("%lld%lld%lld", &points[i].coordinate[0], &points[i].coordinate[1],
          &points[i].coordinate[2]);
  }
  if (!dfs(1)) {
    printf("NO\n");
  }
}
