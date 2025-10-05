#include <bits/stdc++.h>
using namespace std;
char s[100000 + 5];
int main() {
  int a = 0, b = 0, n, c, d;
  scanf("%d%s", &n, s);
  for (int i = 0; i < n; i++)
    if (s[i] == 'r')
      a++;
    else
      b++;
  c = a;
  d = b;
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0) {
      if (s[i] == 'r') a--;
    } else {
      if (s[i] == 'b') b--;
    }
    if (i % 2 == 0) {
      if (s[i] == 'b') d--;
    } else {
      if (s[i] == 'r') c--;
    }
  }
  printf("%d", min(max(a, b), max(c, d)));
  return 0;
}
