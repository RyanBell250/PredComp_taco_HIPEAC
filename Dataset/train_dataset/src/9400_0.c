#include <bits/stdc++.h>
using namespace std;
int vertices[8][3];
int edges[28][3];
void print_answer() {
  int i, j;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 3; j++) printf("%d ", vertices[i][j]);
    puts("");
  }
}
unsigned long long sdist(int i, int j) {
  unsigned long long result = 0, tmp;
  int k;
  for (k = 0; k < 3; ++k) {
    tmp = (unsigned long long)(vertices[i][k] - vertices[j][k]);
    result += tmp * tmp;
  }
  return result;
}
unsigned long long sprod(int i, int j) {
  unsigned long long result = 0;
  int k;
  for (k = 0; k < 3; ++k)
    result += (unsigned long long)edges[i][k] * edges[j][k];
  return result;
}
int check() {
  int i, j, k, l, count = 0;
  unsigned long long sqr_l = ULLONG_MAX;
  for (i = 0; i < 8; ++i)
    for (j = i + 1; j < 8; ++j) {
      if (sdist(i, j) == sqr_l) {
        for (k = 0; k < 3; ++k)
          edges[count][k] = vertices[i][k] - vertices[j][k];
        ++count;
      } else if (sdist(i, j) < sqr_l) {
        for (k = 0; k < 3; ++k) edges[0][k] = vertices[i][k] - vertices[j][k];
        count = 1;
        sqr_l = sdist(i, j);
      }
    }
  if (sqr_l == 0 || count != 12) return 0;
  for (i = 0; i < count; ++i) {
    l = 0;
    for (j = 0; j < count; ++j)
      if (i != j && sprod(i, j) == 0) l++;
    if (l != 8) return 0;
  }
  return 1;
}
int main(int argc, char const *argv[]) {
  int i, j, i1, i2, i3, i4, i5, i6, i7;
  for (i = 0; i < 8; i++)
    for (j = 0; j < 3; j++) scanf("%d", &vertices[i][j]);
  if (check()) {
    puts("YES");
    print_answer();
    return 0;
  }
  for (i1 = 0; i1 < 6; ++i1) {
    swap(vertices[1][i1 % 3], vertices[1][(i1 + 1) % 3]);
    for (i2 = 0; i2 < 6; ++i2) {
      swap(vertices[2][i2 % 3], vertices[2][(i2 + 1) % 3]);
      for (i3 = 0; i3 < 6; ++i3) {
        swap(vertices[3][i3 % 3], vertices[3][(i3 + 1) % 3]);
        for (i4 = 0; i4 < 6; ++i4) {
          swap(vertices[4][i4 % 3], vertices[4][(i4 + 1) % 3]);
          for (i5 = 0; i5 < 6; ++i5) {
            swap(vertices[5][i5 % 3], vertices[5][(i5 + 1) % 3]);
            for (i6 = 0; i6 < 6; ++i6) {
              swap(vertices[6][i6 % 3], vertices[6][(i6 + 1) % 3]);
              for (i7 = 0; i7 < 6; ++i7) {
                swap(vertices[7][i7 % 3], vertices[7][(i7 + 1) % 3]);
                if (check()) {
                  puts("YES");
                  print_answer();
                  return 0;
                }
              }
            }
          }
        }
      }
    }
  }
  puts("NO");
  return 0;
}
