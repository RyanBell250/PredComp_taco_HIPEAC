#include <bits/stdc++.h>
long long que[1000000], acst[1000000], ev[1000000], en[1000000], eh[1000000];
long long head[1000000], dep[1000000], tail[1000000], path[1000000],
    edge[1000000], edge2[1000000];
long long vsize, esize;
void BFS(long long root) {
  unsigned long long i, j, k, a, b, c;
  i = 1;
  j = 1;
  que[1] = root;
  dep[root] = 1;
  while (i <= j) {
    root = que[i++];
    for (k = eh[root]; k > 0; k = en[k]) {
      a = ev[k];
      if (dep[a] == 0) {
        dep[a] = dep[root] + 1;
        acst[a] = root;
        que[++j] = a;
      }
    }
  }
}
void DFS(long long root) {
  long long i, j;
  for (i = eh[root]; i > 0; i = en[i]) {
    j = ev[i];
    if (dep[j] == 2) {
      dep[j] = 0;
      edge2[++(*edge2)] = j;
      DFS(j);
    }
  }
}
int main() {
  long long i, j, k, l, a, b, c, ans, ans1, ans2, n, m;
  scanf("%lld%lld", &vsize, &esize);
  n = vsize;
  memset(eh, 0, sizeof(*eh) * (vsize + 1));
  *ev = 1;
  for (i = 1; i <= esize; i++) {
    scanf("%lld%lld", &a, &b);
    ev[++(*ev)] = b;
    en[*ev] = eh[a];
    eh[a] = *ev;
    ev[++(*ev)] = a;
    en[*ev] = eh[b];
    eh[b] = *ev;
  }
  memset(dep, 0, sizeof(*dep) * (vsize + 1));
  ans = (long long)0xFFFFFFFFFFFFFF;
  BFS(1);
  acst[1] = 0;
  if (dep[n] > 0) {
    if (ans > dep[n] - 1) {
      ans = dep[n] - 1;
      *path = 0;
      for (i = n; i > 0; i = acst[i]) {
        path[++(*path)] = i;
      }
    }
  }
  ans1 = 0;
  ans2 = 0;
  for (i = 1; i <= vsize; i++) {
    if ((dep[i] == 3) && (i != n)) {
      ans1 = 4;
      ans2 = i;
      break;
    }
  }
  if ((ans1 > 0) && (ans1 < ans)) {
    ans = ans1;
    *path = 5;
    path[1] = n;
    path[2] = 1;
    path[3] = ans2;
    path[4] = acst[ans2];
    path[5] = 1;
  }
  *edge = 0;
  for (i = 1; i <= vsize; i++) {
    head[i] = (eh[i] > 0) ? (*edge + 1) : 0;
    for (j = eh[i]; j > 0; j = en[j]) {
      edge[++(*edge)] = ev[j];
    }
    tail[i] = (eh[i] > 0) ? (*edge) : 0;
    std::sort(edge + head[i], edge + tail[i] + 1);
  }
  for (i = 1; i <= vsize; i++) {
    if (dep[i] == 2) {
      *edge2 = 0;
      dep[i] = 0;
      DFS(i);
      std::sort(edge2 + 1, edge2 + *edge2 + 1);
      for (j = 1; j <= *edge2; j++) {
        a = edge2[j];
        l = head[a];
        for (k = j + 1; k <= *edge2; k++) {
          while ((l > 0) && (l <= tail[a]) && (edge[l] < edge2[k])) {
            l += 1;
          }
          if ((l == 0) || (edge2[k] != edge[l]) || (l > tail[a])) {
            if (ans > 5) {
              memset(dep, 0, sizeof(*dep) * (vsize + 1));
              dep[1] = 0xFFFF;
              dep[n] = 0xFFFF;
              acst[edge2[k]] = edge2[k];
              BFS(edge2[k]);
              b = acst[a];
              c = acst[b];
              ans = 5;
              *path = 6;
              path[1] = n;
              path[2] = a;
              path[3] = c;
              path[4] = b;
              path[5] = a;
              path[6] = 1;
            }
            goto SUC;
          }
        }
      }
    }
  }
SUC:
  if (ans == (long long)0xFFFFFFFFFFFFFF) {
    printf("-1\n");
  } else {
    printf("%lld\n", ans);
    for (i = *path; i >= 1; i--) {
      printf("%lld", path[i]);
      if (i > 1) {
        printf(" ");
      } else {
        printf("\n");
      }
    }
  }
  return 0;
}
