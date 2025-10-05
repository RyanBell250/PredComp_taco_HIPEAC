#include <bits/stdc++.h>
using namespace std;
int N, T, A, tmp, L;
bool use[3000000], odd;
vector<int> P;
inline bool prime(int X) {
  for (int i = 0; i < L; ++i) {
    if (X / P[i] * P[i] == X)
      return 0;
    else if (P[i] * P[i] >= X)
      return 1;
  }
}
int main() {
  scanf("%d", &N);
  if (N == 1)
    printf("-1\n");
  else {
    T = N * (N + 1) / 2;
    use[0] = use[1] = 1;
    for (int i = 2; i < 3000000; ++i) {
      if (!use[i]) {
        P.push_back(i);
        for (int j = i + i; j < 3000000; j += i) use[j] = 1;
      }
    }
    L = P.size();
    if (T <= 3000000 && !use[T]) {
      for (int i = 0; i < N; ++i) printf("1 ");
      printf("\n");
    } else {
      if (T % 2 == 1) {
        if (prime(T - 2)) {
          for (int i = 1; i <= N; ++i) printf("%d ", (i == 2) ? 2 : 1);
          printf("\n");
          goto end;
        }
        odd = 1;
        T -= 3;
        if (prime(T)) {
          for (int i = 1; i <= N; ++i) printf("%d ", (i == 3) ? 1 : 2);
          printf("\n");
          goto end;
        }
      }
      for (int i = 0; i < L; ++i) {
        if (P[i] <= T && prime(T - P[i])) {
          A = P[i];
          break;
        }
      }
      memset(use, 0, sizeof(use));
      if (odd) use[3] = 1;
      tmp = min(A, N);
      while (A > 0) {
        if (!use[tmp] && tmp <= A) {
          A -= tmp;
          use[tmp] = 1;
        }
        --tmp;
      }
      for (int i = 1; i <= N; ++i) {
        if (i == 3) {
          if (odd)
            printf("3 ");
          else
            printf("%d ", use[i] + 1);
        } else
          printf("%d ", use[i] + 1);
      }
      printf("\n");
    }
  }
end:;
}
