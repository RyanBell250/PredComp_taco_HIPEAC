#include <bits/stdc++.h>
const long long N = 6e5 + 10;
const long long INF = (1LL << 60) + 5;
const long long mod = 1e9 + 7;
long long n;
long long h, w;
char op[N];
long long a[N], b[N];
void init() {
  std::cin >> n >> h >> w;
  scanf("%s", op + 1);
}
void work() {
  for (long long i = 1; i <= w; i++) {
    a[i] = INF;
  }
  for (long long i = 1; i <= h; i++) {
    b[i] = INF;
  }
  long long step = 0;
  for (long long i = 1; i <= n; i++) {
    if (op[i] == 'L') {
      step--;
    } else if (op[i] == 'R') {
      step++;
    }
    if (step < 0) {
      if (-step <= w) {
        a[-step] = std::min(a[-step], i);
      }
    } else {
      if (w - step + 1 >= 1) {
        a[w - step + 1] = std::min(a[w - step + 1], i);
      }
    }
  }
  if (step > 0) {
    for (long long i = w; i >= 1; i--) {
      if (i - step >= 1) {
        a[i - step] = std::min(a[i - step], a[i] + n);
      }
    }
  } else {
    for (long long i = 1; i <= w; i++) {
      if (i - step <= w) {
        a[i - step] = std::min(a[i - step], a[i] + n);
      }
    }
  }
  step = 0;
  for (long long i = 1; i <= n; i++) {
    if (op[i] == 'U') {
      step--;
    } else if (op[i] == 'D') {
      step++;
    }
    if (step < 0) {
      if (-step <= h) {
        b[-step] = std::min(b[-step], i);
      }
    } else {
      if (h - step + 1 >= 1) {
        b[h - step + 1] = std::min(b[h - step + 1], i);
      }
    }
  }
  if (step > 0) {
    for (long long i = h; i >= 1; i--) {
      if (i - step >= 1) {
        b[i - step] = std::min(b[i - step], b[i] + n);
      }
    }
  } else {
    for (long long i = 1; i <= h; i++) {
      if (i - step <= h) {
        b[i - step] = std::min(b[i - step], b[i] + n);
      }
    }
  }
  std::sort(a + 1, a + w + 1);
  std::sort(b + 1, b + h + 1);
  if (a[w] == INF && b[h] == INF) {
    printf("-1\n");
    return;
  }
  long long it = 0, sum = 0, answer = 0;
  for (long long i = 1; i <= h; i++) {
    while (it + 1 <= w && a[it + 1] < b[i]) {
      sum += a[it + 1];
      sum %= mod;
      it++;
    }
    answer += sum;
    answer %= mod;
    answer += (long long)(w - it) * b[i] % mod;
    answer %= mod;
  }
  std::cout << answer << std::endl;
}
int main() {
  init();
  work();
  return 0;
}
