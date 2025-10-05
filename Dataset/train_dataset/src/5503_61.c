#include <bits/stdc++.h>
template <class c>
int popc(c a) {
  if (sizeof(c) == 8)
    return __builtin_popcountll(a);
  else
    return __builtin_popcount(a);
}
template <class c>
int ctz(c a) {
  if (sizeof(c) == 8)
    return __builtin_ctzll(a);
  else
    return __builtin_ctz(a);
}
template <class c>
int clz(c a) {
  if (sizeof(c) == 8)
    return __builtin_clzll(a);
  else
    return __builtin_clz(a);
}
inline int min(const int &first, const int &second) {
  return (((second - first) >> (32 - 1)) & (first ^ second)) ^ first;
}
inline int max(const int &first, const int &second) {
  return (((second - first) >> (32 - 1)) & (first ^ second)) ^ second;
}
inline long long min(const long long &first, const long long &second) {
  return (((second - first) >> (64 - 1)) & (first ^ second)) ^ first;
}
inline long long max(const long long &first, const long long &second) {
  return (((second - first) >> (64 - 1)) & (first ^ second)) ^ second;
}
using namespace std;
char string_in_buffer[(int)260];
void fast_scan(int &first) { scanf("%d", &first); }
void fast_scan(long long &first) { scanf("%lld", &first); }
void fast_scan(unsigned long long &first) { scanf("%llu", &first); }
void fast_scan(double &first) { scanf("%lf", &first); }
void fast_scan(long double &first) { scanf("%Lf", &first); }
void fast_scan(char &first) {
  scanf("%c", &first);
  if (first == '\n') {
    fast_scan(first);
  }
}
void fast_scan(string &first) {
  scanf("%s", string_in_buffer);
  first = string(string_in_buffer);
}
template <class TFirst, class TSecond>
void fast_scan(pair<TFirst, TSecond> &p) {
  fast_scan(p.first);
  fast_scan(p.second);
}
template <class T>
void fast_scan(vector<T> &v) {
  for (auto &first : v) fast_scan(first);
}
void fast_print(const int &first) { printf("%d", first); }
void fast_print(const unsigned int &first) { printf("%u", first); }
void fast_print(const long long &first) { printf("%lld", first); }
void fast_print(const unsigned long long &first) { printf("%llu", first); }
void fast_print(const char &first) { printf("%c", first); };
void fast_print(const double &first) { printf("%.15lf", first); }
void fast_print(const long double &first) { printf("%.15Lf", first); }
void fast_print(const string &first) { printf("%s", first.c_str()); }
void fast_print(const char v[]) { fast_print((string)v); }
template <class TFirst, class TSecond>
void fast_print(const pair<TFirst, TSecond> &p) {
  fast_print(p.first);
  fast_print(' ');
  fast_print(p.second);
}
template <class T>
void fast_print(const vector<T> &v) {
  if (v.empty()) return;
  fast_print(v[0]);
  for (int i = 1; i < v.size(); i++) {
    fast_print(' ');
    fast_print(v[i]);
  }
}
template <class T>
void fast_print(const vector<vector<T>> &v) {
  if (v.empty()) return;
  fast_print(v[0]);
  for (int i = 1; i < v.size(); i++) {
    fast_print('\n');
    fast_print(v[i]);
  }
}
template <class T>
void fast_print(const T &v) {
  for (const auto &first : v) {
    fast_print(first);
    fast_print(' ');
  }
}
using namespace std;
namespace smart_io {
string print_start = "";
string sep = " ";
bool first_print = false;
void precall_print() {
  fast_print(print_start);
  print_start = "\n";
  first_print = true;
}
void _print(deque<string>) {}
template <class T, class... Args>
void _print(deque<string> names, T elem, Args... args) {
  if (!first_print) {
    fast_print("\n");
  } else {
    first_print = false;
  }
  fast_print(names.front());
  fast_print(" = ");
  fast_print(elem);
  names.pop_front();
  _print(names, args...);
}
}  
template <class T>
ostream &operator,(ostream &os, const T &object) {
  if (!smart_io::first_print) {
    fast_print(smart_io::sep);
  } else {
    smart_io::first_print = false;
  }
  fast_print(object);
  return os;
}
template <class T>
istream &operator,(istream &is, T &object) {
  fast_scan(object);
  return is;
}
namespace escape__from__random__aetuhoetnuhshe {
using namespace std::chrono;
mt19937 rng(duration_cast<milliseconds>(system_clock::now().time_since_epoch())
                .count());
uniform_real_distribution<> prob_dist(0.0, 1.0);
};  
namespace typedefs {}
namespace numbers_operation {
template <class T>
inline T floor_mod(T a, const T &b) {
  a %= b;
  if (a < 0) a += b;
  return a;
}
}  
using namespace numbers_operation;
using namespace typedefs;
using namespace escape__from__random__aetuhoetnuhshe;
const unsigned long long INF = (1ULL << 63);
bool chkmin(unsigned long long &a, unsigned long long b, unsigned long long c) {
  if (b == INF && c == INF) {
    return false;
  }
  b += c;
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
const int N = 1000;
struct Node {
  int ch[2] = {0, 0};
  int go[2] = {0, 0};
  int suff = 0;
  int p = 0;
  int p_c = -1;
  bool term = false;
} S[N];
int it = 2;
int g, n, m;
vector<pair<int, vector<int>>> seq;
signed main(signed argc, char *argv[]) {
  cin, g, n, m;
  for (int i = 0; i < n; i++) {
    int a, k;
    cin, a, k;
    vector<int> v(k);
    cin, v;
    seq.emplace_back(a, v);
  }
  for (int i = 0; i < m; i++) {
    int k;
    cin, k;
    vector<int> seq(k);
    cin, seq;
    int cur = 1;
    for (int first : seq) {
      if (!S[cur].ch[first]) {
        S[cur].ch[first] = it++;
        S[S[cur].ch[first]].p = cur;
        S[S[cur].ch[first]].p_c = first;
      }
      cur = S[cur].ch[first];
    }
    S[cur].term = true;
  }
  deque<int> deq{1};
  while (!deq.empty()) {
    int v = deq[0];
    deq.pop_front();
    if (v == 1 || S[v].p == 1) {
      S[v].suff = 1;
    } else {
      S[v].suff = S[S[S[v].p].suff].go[S[v].p_c];
    }
    S[v].term |= S[S[v].suff].term;
    for (int t = 0; t < (2); t++) {
      if (S[v].ch[t]) {
        deq.push_back(S[v].ch[t]);
        S[v].go[t] = S[v].ch[t];
      } else {
        if (S[v].suff == v) {
          S[v].go[t] = 1;
        } else {
          S[v].go[t] = S[S[v].suff].go[t];
        }
      }
    }
  }
  S[it].go[0] = S[it].go[1] = it;
  it++;
  for (int i = 1; i < it - 1; i++) {
    if (S[S[i].go[0]].term) {
      S[i].go[0] = it - 1;
    }
    if (S[S[i].go[1]].term) {
      S[i].go[1] = it - 1;
    }
  }
  vector<vector<vector<vector<unsigned long long>>>> dp(((int)seq.size()));
  for (int i = 0; i < ((int)seq.size()); i++) {
    dp[i].resize(((int)seq[i].second.size()) + 1,
                 vector<vector<unsigned long long>>(
                     it, vector<unsigned long long>(it, INF)));
    for (int a = 1; a < it; a++) dp[i][0][a][a] = 0;
  }
  while (clock() < CLOCKS_PER_SEC * 0.6) {
    bool upd = false;
    for (int i = 0; i < ((int)seq.size()); i++) {
      for (int j = 0; j < ((int)seq[i].second.size()); j++) {
        for (int a = 1; a < it; a++) {
          if (S[a].term) continue;
          for (int b = 1; b < it; b++) {
            if (S[b].term) continue;
            if (dp[i][j][a][b] == INF) continue;
            int eng = seq[i].second[j];
            if (eng <= 1) {
              if (chkmin(dp[i][j + 1][a][S[b].go[eng]], dp[i][j][a][b], 1)) {
                upd = true;
              }
            } else {
              for (int k = 0; k < ((int)seq.size()); k++) {
                if (seq[k].first == eng) {
                  for (int c = 1; c < it; c++) {
                    if (chkmin(dp[i][j + 1][a][c], dp[i][j][a][b],
                               dp[k][((int)seq[k].second.size())][b][c])) {
                      upd = true;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    if (!upd) break;
  }
  vector<unsigned long long> rez(g, INF);
  for (int i = 0; i < ((int)seq.size()); i++) {
    for (int end = 1; end < it - 1; end++) {
      rez[seq[i].first] =
          min(rez[seq[i].first], dp[i][((int)seq[i].second.size())][1][end]);
    }
  }
  for (int i = 2; i < g; i++) {
    if (rez[i] < INF) {
      smart_io::precall_print();
      cout, "NO", rez[i];
    } else {
      smart_io::precall_print();
      cout, "YES";
    }
  }
}
