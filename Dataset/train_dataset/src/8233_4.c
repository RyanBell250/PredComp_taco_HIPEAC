#include <bits/stdc++.h>
using namespace std;
struct _ {
  _() { ios_base::sync_with_stdio(0); }
} _;
template <class A, class B>
ostream &operator<<(ostream &o, pair<A, B> t) {
  o << "(" << t.first << ", " << t.second << ")";
  return o;
}
template <class T>
string tostring(T first, int len = 0, char c = '0') {
  stringstream ss;
  ss << first;
  string r = ss.str();
  if (r.length() < len) r = string(len - r.length(), c) + r;
  return r;
}
template <class T>
void PV(T a, T b, int n = 0, int w = 0, string s = " ") {
  int c = 0;
  while (a != b) {
    cout << tostring(*a++, w, ' ');
    if (a != b && (n == 0 || ++c % n))
      cout << s;
    else
      cout << endl;
  }
}
template <class T>
inline bool chmin(T &a, T b) {
  return a > b ? a = b, 1 : 0;
}
template <class T>
inline bool chmax(T &a, T b) {
  return a < b ? a = b, 1 : 0;
}
const long long linf = 0x3f3f3f3f3f3f3f3fLL;
const int inf = 0x3f3f3f3f;
const int mod = int(1e9) + 7;
const int N = 2222;
int n, m;
bool rr[N];
bool cc[N];
double dp[N][N];
double f(int nr, int nc) {
  if (nr < 0) return 0;
  if (nc < 0) return 0;
  double &res = dp[nr][nc];
  if (res < -inf / 2) {
    res = 0;
    double p0 = (double)(n - nc) * nr / n / n;
    double p1 = (double)(n - nr) * nc / n / n;
    double p2 = (double)nr * nc / n / n;
    double p3 = (double)(n - nc) * (n - nr) / n / n;
    if (nr + nc > 0) {
      res += f(nr - 1, nc) * p0;
      res += f(nr, nc - 1) * p1;
      res += f(nr - 1, nc - 1) * p2;
      res++;
      res /= (1 - p3);
    }
  }
  return res;
}
int main() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int first, second;
    cin >> first >> second;
    rr[first] = 1;
    cc[second] = 1;
  }
  int nr = 0, nc = 0;
  for (int i = 1; i <= n; i++)
    if (rr[i] == 0) nr++;
  for (int i = 1; i <= n; i++)
    if (cc[i] == 0) nc++;
  fill(&dp[0][0], &dp[N][0], -inf);
  double res = f(nr, nc);
  cout << fixed << setprecision(10) << res << endl;
  return 0;
}
