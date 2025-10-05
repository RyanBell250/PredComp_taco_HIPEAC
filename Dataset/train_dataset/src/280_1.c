#include <iostream>
const int P = (int)1e9 + 7;
int64_t pow(int64_t x, int64_t y) {
  int64_t ans = 1;
  while (y > 0) {
    if (y & 1) ans = ans * x % P;
    x = x * x % P;
    y >>= 1;
  }
  return ans;
}
int64_t comb(int64_t x, int64_t y) {
  if (y == x || y == 0) return 1;
  int64_t ans = 1;
  for (int i = 1; i <= y; ++i) {
    ans = ans * (x - y + i) % P * pow(i, P - 2) % P;
  }
  return ans;
}
int solve(int n, int a, int b) {
  return ((pow(2, n) - 1 - comb(n, a) - comb(n, b)) % P + P) % P;
}
int main() {
  int n, a, b;
  std::cin >> n >> a >> b;
  std::cout << solve(n, a, b) << std::endl;
  return 0;
}
