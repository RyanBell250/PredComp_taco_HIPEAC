#include <bits/stdc++.h>
using namespace std;
const double pi = 3.1415926535897932384;
typedef struct POINT {
  double x, y;
  POINT(double x = 0, double y = 0) : x(x), y(y) {}
  double operator&(const POINT& b) { return x * b.y - y * b.x; }
} PT;
typedef struct LINE {
  double a, b, c;
  double l, th;
  LINE(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {
    if (b != 0) {
      l = abs(c) / sqrt(a * a + b * b);
      th = atan(-1. * a / b);
      if (b * c > 0) {
        th += pi;
      }
      th += pi / 2;
    }
  }
} L;
int N, M;
pair<double, int> ia[50011 * 2];
L line[50011];
int sp[50011];
int bit[50011 * 2];
void add(int x, int k, int n) {
  while (x <= n) {
    bit[x] += k;
    x += x & (-x);
  }
}
int sum(int x) {
  int res = 0;
  while (x) {
    res += bit[x];
    x -= x & (-x);
  }
  return res;
}
double opt(double x) {
  while (x < 0) {
    x += 2 * pi;
  }
  while (x >= 2 * pi) {
    x -= 2 * pi;
  }
  return x;
}
long long cnt(double r) {
  int k = 0;
  for (int i = 0; i < N; i++) {
    if (line[i].l <= r) {
      double theta = acos(line[i].l / r);
      double t1 = opt(line[i].th + theta), t2 = opt(line[i].th - theta);
      ia[k++] = pair<double, int>(min(t1, t2), i << 1);
      ia[k++] = pair<double, int>(max(t1, t2), (i << 1) + 1);
    }
  }
  sort(ia, ia + k);
  long long res = 0;
  memset(bit, 0, sizeof(bit));
  for (int i = 0; i < k; i++) {
    if (ia[i].second & 1) {
      res += sum(i + 1) - sum(sp[ia[i].second >> 1] + 1);
      add((sp[ia[i].second >> 1]) + 1, -1, k);
    } else {
      sp[ia[i].second >> 1] = i;
      add(i + 1, 1, k);
    }
  }
  return res;
}
double iadis(int i, int j) {
  L& A = line[i];
  L& B = line[j];
  double tmp = PT(A.a, A.b) & PT(B.a, B.b);
  double x = (PT(A.b, A.c) & PT(B.b, B.c)) / tmp;
  double y = -(PT(A.a, A.c) & PT(B.a, B.c)) / tmp;
  return sqrt(x * x + y * y);
}
double cal(double r) {
  int q1[50011], q2[50011], num = 0, n1 = 0, n2 = 0;
  int k = 0;
  for (int i = 0; i < N; i++) {
    if (line[i].l <= r) {
      double theta = acos(line[i].l / r);
      double t1 = opt(line[i].th + theta), t2 = opt(line[i].th - theta);
      ia[k++] = pair<double, int>(min(t1, t2), i << 1);
      ia[k++] = pair<double, int>(max(t1, t2), (i << 1) + 1);
    }
  }
  sort(ia, ia + k);
  double res = 0;
  for (int i = 0; i < k; i++) {
    if (ia[i].second & 1) {
      int tmp = ia[i].second >> 1;
      while (q1[--n1] != tmp) {
        q2[n2++] = q1[n1];
        res += iadis(tmp, q1[n1]);
        num++;
      }
      while (n2) {
        q1[n1++] = q2[--n2];
      }
    } else {
      q1[n1++] = ia[i].second >> 1;
    }
  }
  return res + (M - num) * r;
}
int main() {
  int _x, _y;
  scanf("%d%d%d%d", &N, &_x, &_y, &M);
  for (int i = 0; i < N; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    line[i] = L(a * 1., -1000., a / 1000. * _x - _y + b);
  }
  double l = 0, r = 2.1e9;
  for (int _ = 0; _ < 100; _++) {
    double m = (l + r) / 2;
    if (cnt(m) < M) {
      l = m;
    } else {
      r = m;
    }
  }
  printf("%.9f\n", cal(l));
  return 0;
}
