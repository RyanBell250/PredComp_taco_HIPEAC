#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> G, H;
vector<int> ord, comp;
vector<bool> V;
struct SCC {
  int n, c;
  SCC(int n) : n(n) {
    G.resize(n);
    H.resize(n);
    for (int i = 0; i < n; i++) {
      G[i].reserve(n);
      H[i].reserve(n);
      G[i].clear();
      H[i].clear();
    }
    ord.reserve(n);
    ord.clear();
  };
  void add_edge(int u, int v) {
    G[u].push_back(v);
    H[v].push_back(u);
  }
  void dfs1(int v) {
    V[v] = true;
    for (auto& u : G[v])
      if (!V[u]) dfs1(u);
    ord.push_back(v);
  }
  void dfs2(int v) {
    comp[v] = c;
    for (auto& u : H[v])
      if (comp[u] == -1) dfs2(u);
  }
  vector<int> scc() {
    V.assign(n, 0);
    for (int i = 0; i < n; i++)
      if (!V[i]) dfs1(i);
    comp.assign(n, -1);
    c = 0;
    for (int i = 0; i < n; i++) {
      int v = ord[n - 1 - i];
      if (comp[v] == -1) dfs2(v), c++;
    }
    return comp;
  }
  vector<vector<int>> dag() {
    set<pair<int, int>> S;
    vector<vector<int>> dag(c);
    for (int a = 0; a < n; a++) {
      for (auto& b : G[a]) {
        if (comp[a] == comp[b]) continue;
        if (!S.count({comp[a], comp[b]})) {
          dag[comp[a]].push_back(comp[b]);
          S.insert({comp[a], comp[b]});
        }
      }
    }
    return dag;
  }
};
int VAR(int i) { return 2 * i; }
int NOT(int i) { return i ^ 1; }
struct SAT {
  int n;
  SCC scc;
  SAT(int n) : n(n), scc(2 * n) {}
  void add_or(int a, int b) {
    if (a == NOT(b)) return;
    scc.add_edge(NOT(a), b);
    scc.add_edge(NOT(b), a);
  }
  void add_true(int a) { add_or(a, a); }
  void add_false(int a) { add_or(NOT(a), NOT(a)); }
  void add_xor(int a, int b) {
    add_or(a, b);
    add_or(NOT(a), NOT(b));
  }
  void add_imply(int a, int b) { add_or(NOT(a), b); }
  bool solve() {
    auto comp = scc.scc();
    for (int i = 0; i < 2 * n; i += 2) {
      if (comp[i] == comp[i + 1]) return false;
    }
    return true;
  }
};
struct Rule {
  int pos1, pos2;
  char t1, t2;
  void read() {
    cin >> pos1 >> t1 >> pos2 >> t2;
    pos1 = VAR(pos1 - 1);
    pos2 = VAR(pos2 - 1);
    if (t1 == 'C') pos1 = NOT(pos1);
    if (t2 == 'C') pos2 = NOT(pos2);
  }
};
string alpha, s;
int l, n, m;
bool vowel[256];
Rule rule[4 * 200 * 199];
char next_vowel[256], next_cons[256];
char min_v, min_c;
bool check_str(int pl, bool next_greater = true) {
  SAT sat(2 * n);
  if (!min_c) {
    for (int i = 0; i < n; i++) {
      sat.add_true(VAR(i));
    }
  } else if (!min_v) {
    for (int i = 0; i < n; i++) {
      sat.add_false(VAR(i));
    }
  }
  for (int i = 0; i < m; i++) {
    sat.add_imply(rule[i].pos1, rule[i].pos2);
  }
  for (int i = 0; i < pl; i++) {
    if (vowel[s[i]]) {
      sat.add_true(VAR(i));
    } else {
      sat.add_false(VAR(i));
    }
  }
  if (pl < n && next_greater) {
    char ch = s[pl];
    if (!next_vowel[ch] && !next_cons[ch]) {
      return false;
    }
    if (next_vowel[ch] && !next_cons[ch]) {
      sat.add_true(VAR(pl));
    }
    if (!next_vowel[ch] && next_cons[ch]) {
      sat.add_false(VAR(pl));
    }
  }
  return sat.solve();
}
string build_soln(int pl) {
  if (pl >= n) return s;
  string old_s = s;
  char ch = 127;
  char old = s[pl];
  s = old_s;
  for (int i = pl + 1; i < n; i++) {
    s[i] = 'a';
  }
  if (next_vowel[old]) {
    s[pl] = next_vowel[old];
    if (check_str(pl + 1, false)) {
      ch = min(ch, s[pl]);
    }
  }
  if (next_cons[old]) {
    s[pl] = next_cons[old];
    if (check_str(pl + 1, false)) {
      ch = min(ch, s[pl]);
    }
  }
  old_s[pl] = ch;
  for (int i = pl + 1; i < n; i++) {
    s = old_s;
    for (int j = i + 1; j < n; j++) {
      s[j] = 'a';
    }
    ch = 127;
    if (min_v) {
      s[i] = min_v;
      if (check_str(i + 1, false)) {
        ch = min(ch, s[i]);
      }
    }
    if (min_c) {
      s[i] = min_c;
      if (check_str(i + 1, false)) {
        ch = min(ch, s[i]);
      }
    }
    old_s[i] = ch;
  }
  return old_s;
}
int main() {
  cin >> alpha;
  l = alpha.length();
  for (int i = 0; i < l; i++) {
    vowel[i + 'a'] = alpha[i] == 'V';
  }
  min_v = min_c = 0;
  for (int i = 'a' + l - 1; i >= 'a'; i--) {
    next_vowel[i] = min_v;
    next_cons[i] = min_c;
    if (vowel[i]) {
      min_v = i;
    } else {
      min_c = i;
    }
  }
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    rule[i].read();
  }
  cin >> s;
  int prefix_len = n;
  while (prefix_len >= 0 && !check_str(prefix_len)) {
    prefix_len--;
  }
  if (prefix_len < 0) {
    cout << -1 << endl;
    return 0;
  }
  cout << build_soln(prefix_len) << endl;
  return 0;
}
