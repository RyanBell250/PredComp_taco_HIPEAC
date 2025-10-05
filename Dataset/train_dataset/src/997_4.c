#include <bits/stdc++.h>
using namespace std;
const long double pi = acos(-1.0);
const long double log23 = 1.58496250072115618145373894394781;
const long double eps = 1e-8;
const long long INF = 1e18 + 239;
const long long prost = 239;
const int two = 2;
const int th = 3;
const long long MOD = 1e9 + 7;
const long long MOD2 = MOD * MOD;
const int BIG = 1e9 + 239;
const int alf = 26;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
const int dxo[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dyo[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int dig = 10;
const int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int digarr[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
const int bt = 31;
template <typename T>
inline T gcd(T a, T b) {
  while (a) {
    b %= a;
    swap(a, b);
  }
  return b;
}
template <typename T>
inline T lcm(T a, T b) {
  return (a / gcd(a, b)) * b;
}
inline bool is_down(char x) { return ('a' <= x && x <= 'z'); }
inline bool is_upper(char x) { return ('A' <= x && x <= 'Z'); }
inline bool is_digit(char x) { return ('0' <= x && x <= '9'); }
mt19937 rnd(239);
const int M = 2 * 1e5 + 239;
const int N = 2 * 1e3 + 239;
const int L = 20;
const int T = (1 << 18);
const int B = trunc(sqrt(M)) + 1;
const int X = (1 << 20);
int dist[X], kek[X];
vector<tuple<int, int, int> > v;
void gen(int ms, int n) {
  if (ms == 0) return;
  int to = kek[ms];
  vector<int> vv;
  for (int i = 0; i < n; i++)
    if (((ms >> i) & 1) != ((to >> i) & 1)) vv.push_back(i);
  gen(to, n);
  v.push_back(make_tuple(vv[0], vv[1], vv[2]));
}
void solve(int n) {
  for (int i = 0; i < (1 << n); i++) dist[i] = BIG;
  queue<int> r;
  r.push(0);
  dist[0] = 0;
  while (!r.empty()) {
    int ms = r.front();
    r.pop();
    for (int i = 0; i < n; i++)
      for (int j = 1; j < n; j++) {
        int x = i;
        int y = i - j;
        int z = i + j;
        if (y >= 0 && z < n) {
          int nw = ms;
          nw ^= (1 << x);
          nw ^= (1 << y);
          nw ^= (1 << z);
          if (dist[nw] > dist[ms] + 1) {
            r.push(nw);
            dist[nw] = dist[ms] + 1;
            kek[nw] = ms;
          }
        }
      }
  }
  int kol = 0;
  int mx = 0;
  int sum = 0;
  for (int i = 0; i < (1 << n); i++) {
    if (dist[i] == BIG) continue;
    kol++;
    mx = max(mx, dist[i]);
    sum += dist[i];
  }
}
const int MG = 600;
int n, a[M], st[M];
vector<pair<int, int> > in[L];
int main() {
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) st[i] = a[i];
  if (n <= 16) {
    int ms = 0;
    for (int i = 0; i < n; i++) ms += a[i] * (1 << i);
    solve(n);
    if (dist[ms] == BIG) {
      cout << "NO";
      return 0;
    }
    gen(ms, n);
    cout << "YES\n";
    cout << (int)v.size() << "\n";
    for (tuple<int, int, int> t : v)
      cout << get<0>(t) + 1 << " " << get<1>(t) + 1 << " " << get<2>(t) + 1
           << "\n";
    return 0;
  }
  cout << "YES\n";
  vector<tuple<int, int, int> > ans;
  for (int i = 0; i < n; i++)
    if (a[i] == 1)
      for (int x = 1; x < MG && a[i] == 1; x++) {
        int l = i - x;
        int r = i + x;
        if (l >= 0 && r < n)
          if (a[l] == 1 && a[r] == 1) {
            a[l] = 0;
            a[r] = 0;
            a[i] = 0;
            ans.push_back(make_tuple(l, i, r));
            break;
          }
      }
  vector<int> divide;
  int s = n;
  while (s >= 32) {
    int r = (abs((int)rnd()) % 9) + 8;
    divide.push_back(r);
    s -= r;
  }
  divide.push_back(s / 2);
  divide.push_back((s + 1) / 2);
  while (true) {
    shuffle(divide.begin(), divide.end(), rnd);
    for (int x = 0; x < L; x++) in[x].clear();
    int l = 0;
    for (int i = 0; i < (int)divide.size(); i++) {
      int r = l + divide[i];
      in[divide[i]].push_back(make_pair(l, r));
      l = r;
    }
    int ns = (int)ans.size();
    for (int x = 0; x < L; x++)
      if (!in[x].empty()) {
        solve(x);
        for (pair<int, int> t : in[x]) {
          int ms = 0;
          for (int i = t.first; i < t.second; i++)
            ms += a[i] * (1 << (i - t.first));
          ns += dist[ms];
        }
      }
    if (ns > (n / 3) + 12) continue;
    for (int x = 0; x < L; x++)
      if (!in[x].empty()) {
        solve(x);
        for (pair<int, int> t : in[x]) {
          int ms = 0;
          for (int i = t.first; i < t.second; i++)
            ms += a[i] * (1 << (i - t.first));
          v.clear();
          gen(ms, x);
          for (tuple<int, int, int> u : v)
            ans.push_back(make_tuple(get<0>(u) + t.first, get<1>(u) + t.first,
                                     get<2>(u) + t.first));
        }
      }
    break;
  }
  for (tuple<int, int, int> t : ans) {
    st[get<0>(t)] = 1 - st[get<0>(t)];
    st[get<1>(t)] = 1 - st[get<1>(t)];
    st[get<2>(t)] = 1 - st[get<2>(t)];
  }
  cout << (int)ans.size() << "\n";
  for (tuple<int, int, int> t : ans)
    cout << get<0>(t) + 1 << " " << get<1>(t) + 1 << " " << get<2>(t) + 1
         << "\n";
  return 0;
}
