#include <bits/stdc++.h>
using namespace std;
inline void read(int &x) {
   int c = getchar();
  x = 0;
  int neg = 0;
  for (; ((c < 48 || c > 57) && c != '-'); c = getchar())
    ;
  if (c == '-') {
    neg = 1;
    c = getchar();
  }
  for (; c > 47 && c < 58; c = getchar()) {
    x = (x << 1) + (x << 3) + c - 48;
  }
  if (neg) x = -x;
}
inline void write(int x) {
  char buffor[12];
   int i = 0;
  int neg = 0;
  if (x < 0) {
    neg = 1;
    x = -x;
  }
  do {
    buffor[i++] = (x % 10) + '0';
    x /= 10;
  } while (x);
  i--;
  if (neg) putchar('-');
  while (i >= 0) putchar(buffor[i--]);
}
inline void writeln(int x) {
  write(x);
  putchar('\n');
}
long long n, k;
void enter() { cin >> n >> k; }
void process() {
  if (k > n * (n - 1) / 2) {
    cout << "Impossible";
    return;
  }
  long long p = sqrt(k * 2) + 1;
  while (p * (p - 1) / 2 > k) --p;
  k -= p * (p - 1) / 2;
  int sz = 0;
  for (int i = (1), _b = (p); i <= _b; ++i) {
    if (k > 0 && i == k + 1) {
      cout << "()";
      sz += 2;
    }
    cout << '(';
    ++sz;
  }
  for (int i = (1), _b = (p); i <= _b; ++i) {
    cout << ')';
    ++sz;
  }
  for (int thua = n * 2 - sz; thua > 0; thua -= 2) cout << "()";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  enter();
  process();
  return 0;
}
