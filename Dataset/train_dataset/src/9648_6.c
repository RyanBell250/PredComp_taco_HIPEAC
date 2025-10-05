#include <bits/stdc++.h>
int N, M, Tt;
int Nxt[302], Pre[302], A[302];
long long ans[100001];
void init();
void doit();
int main() {
  init();
  doit();
  return 0;
}
void init() {
  int b, c, i;
  scanf("%d %d %d", &N, &M, &Tt);
  for (i = 1; i < N + 1; i++) scanf("%d", &A[i]);
  for (i = 1; i < M + 1; i++) {
    scanf("%d", &b);
    scanf("%d", &c);
    Nxt[b] = c;
    Pre[c] = b;
  }
}
void doit() {
  int i, j, x, v = 0, Cur = 0;
  long long T = Tt;
  for (i = 1; i < N + 1; i++)
    if (!Pre[i]) {
      Cur = A[x = i];
      v++;
      while (Nxt[x]) {
        v++;
        T -= Cur;
        x = Nxt[x];
        Cur += A[x];
        A[x] = Cur;
      }
    }
  if (T < 0 || v < N) {
    printf("%d\n", 0);
    return;
  }
  ans[0] = 1;
  for (i = 1; i < N + 1; i++)
    for (j = A[i]; j < T + 1; j++)
      ans[j] = (ans[j] + ans[j - A[i]]) % 1000000007;
  printf("%I64d\n", ans[T]);
}
