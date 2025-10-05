#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
using vb = vector<bool>;
using vc = vector<char>;
using vd = vector<double>;
using vi = vector<int>;
using vvi = vector<vi>;
using vlli = vector<lli>;
using vvlli = vector<vlli>;
using pi = pair<int, int>;
using plli = pair<lli, lli>;
void readc(char &q) { scanf("%c", &q); }
char readc() {
  char q;
  scanf("%c", &q);
  return q;
}
void readint(int &q) { scanf("%d", &q); }
int readint() {
  int q;
  scanf("%d", &q);
  return q;
}
void readlong(lli &q) { scanf("%lld", &q); }
lli readlong() {
  lli q;
  scanf("%lld", &q);
  return q;
}
void readdbl(double &q) { scanf("%lf", &q); }
double readdbl() {
  double q;
  scanf("%lf", &q);
  return q;
}
void printint(int q) { printf("%d", q); }
void printlong(lli q) { printf("%lld", q); }
void printdbl(double q, int p = 6) { printf("%.*lf", p, q); }
void readln() { scanf("\n"); }
void println() { printf("\n"); }
void printsp() { printf(" "); }
void print(int q) { printint(q); }
void print(long q) { printlong((lli)q); }
void print(lli q) { printlong(q); }
void print(double q) { printdbl(q); }
void print(char c) { printf("%c", c); }
void print(pi q) {
  print(q.first);
  printsp();
  print(q.second);
}
void print(vi q) {
  for (int i = 0; i < q.size(); ++i) {
    print(q[i]);
    printsp();
  }
}
void print(vlli q) {
  for (int i = 0; i < q.size(); ++i) {
    print(q[i]);
    printsp();
  }
}
void print(vd q) {
  for (int i = 0; i < q.size(); ++i) {
    print(q[i]);
    printsp();
  }
}
template <typename T>
void println(T q) {
  print(q);
  println();
}
template <typename T>
T maxim(T first, T second) {
  return (first > second) ? first : second;
}
template <typename T>
T maxim(T first, T second, T third) {
  return mndlim(maxim(first, second), third);
}
template <typename T>
T minim(T first, T second) {
  return (first < second) ? first : second;
}
template <typename T>
T minim(T first, T second, T third) {
  return minim(minim(first, second), third);
}
template <typename T>
T middle(T first, T second, T third) {
  return first + second + third - maxim(first, second, third) -
         minim(first, second, third);
}
template <typename T>
T abs(T arg) {
  return arg < 0 ? -arg : arg;
}
const lli modulo = 1000000007;
int main() {
  int t = readint();
  readln();
  for (lli k = 0; k < t; ++k) {
    int n = readint();
    vi lefts(n), rights(n);
    map<int, int> firstl, firstr;
    int bal = 0;
    vi q(n);
    for (int i = 0; i < n; ++i) {
      q[i] = readint();
    }
    for (int i = 0; i < n; ++i) {
      if (q[n - i - 1] == 1)
        bal--;
      else
        bal++;
      lefts[i] = bal;
    }
    int totalbal = bal;
    bal = 0;
    for (int i = 0; i < n; ++i) {
      int x = readint();
      if (x == 1)
        bal--;
      else
        bal++;
      rights[i] = bal;
    }
    totalbal += bal;
    for (int i = n - 1; i >= 0; --i) {
      firstl[lefts[i]] = i;
      firstr[rights[i]] = i;
    }
    firstl[0] = -1;
    firstr[0] = -1;
    int best = 2 * n;
    if (totalbal == 0)
      best = 0;
    else {
      if (firstr.find(totalbal) != firstr.end()) {
        best = firstr[totalbal] + 1;
      }
      for (int i = 0; i < n; ++i) {
        if (firstr.find(totalbal - lefts[i]) != firstr.end()) {
          best = minim(best, i + 1 + firstr[totalbal - lefts[i]] + 1);
        }
      }
    }
    cout << best << endl;
  }
  return 0;
}
