#include <bits/stdc++.h>
using namespace std;
int n;
int main() {
  scanf("%d", &n);
  if (n % 2 == 0) {
    printf("NO\n");
    return 0;
  } else {
    printf("YES\n");
    printf("1 ");
    int temp = 0;
    for (int i = 1; i <= n / 2; i++) {
      printf("%d %d ", temp + 4, temp + 5);
      temp += 4;
    }
    temp = -2;
    for (int i = 1; i <= n / 2; i++) {
      printf("%d %d ", temp + 4, temp + 5);
      temp += 4;
    }
    printf("%d", n * 2);
  }
  return 0;
}
