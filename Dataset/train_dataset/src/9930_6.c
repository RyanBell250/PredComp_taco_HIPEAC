#include <bits/stdc++.h>
using namespace std;
int main() {
  long long x;
  long long c = 0;
  scanf("%lld", &x);
  long long b;
  for (long long i = 1; i <= x; i++) {
    for (long long j = i + 1; j <= x; j++) {
      b = i ^ j;
      if (b <= x && (i + j) > b && i < b && j < b) {
        c++;
      }
    }
  }
  printf("%lld", c);
}
