#include <bits/stdc++.h>
int main() {
  int n, k;
  std::cin >> n >> k;
  std::cout << ((6 * (n - 1) + 5) * k) << '\n';
  for (int i = 0; i < n; i++)
    std::cout << (6 * i + 1) * k << ' ' << (6 * i + 2) * k << ' '
              << (6 * i + 3) * k << ' ' << (6 * i + 5) * k << '\n';
  return 0;
}
