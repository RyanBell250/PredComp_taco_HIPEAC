#include <bits/stdc++.h>
int gcd(int a, int b) {
  if (a == 0 || b == 0)
    return a + b;
  else if (a % b == 0)
    return b;
  else
    return gcd(b, a % b);
}
int power(int base, int pow) {
  if (pow == 0) return 1;
  long long int base_to_the_power_pow = power(base, pow / 2);
  base_to_the_power_pow =
      (base_to_the_power_pow * base_to_the_power_pow) % 998244353;
  if (pow % 2)
    base_to_the_power_pow = (base_to_the_power_pow * base) % 998244353;
  int result = (int)base_to_the_power_pow;
  return result;
}
int combination(int n, int r) {
  if (r > n) return 0;
  if (r > n - r) r = n - r;
  int numbers[r][2], i, j, GCD, k;
  for (i = 0; i < r; i++) {
    numbers[i][0] = n - i;
    numbers[i][1] = i + 1;
  }
  for (i = r - 1; i > 0; i--) {
    k = 0;
    for (j = 0; numbers[i][1] > 1 && j < r; j++) {
      GCD = gcd(numbers[i][1], numbers[j][0]);
      numbers[i][1] = numbers[i][1] / GCD;
      numbers[j][0] = numbers[j][0] / GCD;
      k++;
    }
  }
  long long int Combination = 1;
  for (i = 0; i < r; i++) {
    Combination = (Combination * numbers[i][0]) % 998244353;
  }
  int result = (int)Combination;
  return result;
}
int main() {
  int i, j, n, m, k;
  long long int number_of_ways;
  scanf("%d %d %d", &n, &m, &k);
  number_of_ways = m;
  number_of_ways = (number_of_ways * power(m - 1, k)) % 998244353;
  number_of_ways = (number_of_ways * combination(n - 1, k)) % 998244353;
  printf("%I64d", number_of_ways);
  return 0;
}
