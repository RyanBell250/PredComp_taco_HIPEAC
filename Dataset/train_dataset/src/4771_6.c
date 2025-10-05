#include <bits/stdc++.h>
using namespace std;
const int L = 200, M = 20, TRIE_SIZE = L + 1, K = 500, MODULO = (int)1e9 + 7;
struct Node {
  int next[M], go[M], parent, prefix, match, c, value;
  Node(int c = -1) {
    memset(next, -1, sizeof next);
    memset(go, -1, sizeof go);
    parent = prefix = match = -1;
    value = 0;
    this->c = c;
  }
};
Node trie[TRIE_SIZE];
int nNode;
void addString(vector<int> v, int value) {
  int n = v.size(), curr = 0;
  for (int i = 0; i < n; ++i) {
    int c = v[i];
    if (trie[curr].next[c] == -1) {
      trie[curr].next[c] = nNode;
      (trie[nNode++] = Node(c)).parent = curr;
    }
    curr = trie[curr].next[c];
  }
  trie[curr].value += value;
}
int goState(int pos, int c);
int findPrefix(int pos) {
  int &res = trie[pos].prefix;
  if (res != -1) return res;
  if (pos == 0 || trie[pos].parent == 0) return res = 0;
  return res = goState(findPrefix(trie[pos].parent), trie[pos].c);
}
int goState(int pos, int c) {
  int &res = trie[pos].go[c];
  if (res != -1) return res;
  if (trie[pos].next[c] != -1) return res = trie[pos].next[c];
  if (pos == 0) return res = 0;
  return res = goState(findPrefix(pos), c);
}
int getMatch(int pos) {
  int &res = trie[pos].match;
  if (res != -1) return res;
  if (pos == 0) return res = 0;
  return res = getMatch(findPrefix(pos)) + trie[pos].value;
}
void add(int &x, int y) {
  if ((x += y) >= MODULO) x -= MODULO;
}
int f[TRIE_SIZE][K + 1][2][2], g[TRIE_SIZE][K + 1][2][2], base, maxCost;
int count(const vector<int> &lim, bool strict) {
  memset(f, 0, sizeof f);
  int digitCount = lim.size(), res = 0;
  f[0][0][0][0] = 1;
  for (int len = 0; len <= digitCount; ++len) {
    memset(g, 0, sizeof g);
    for (int node = 0; node < nNode; ++node)
      for (int sum = 0; sum <= maxCost; ++sum)
        for (int smaller = 0; smaller < 2; ++smaller)
          for (int started = 0; started < 2; ++started) {
            int old = f[node][sum][smaller][started];
            if (old == 0) continue;
            if (len == digitCount) {
              if (!strict || smaller == 1) add(res, old);
            } else {
              int digit = lim[len];
              for (int next = smaller == 1 ? base - 1 : digit; next >= 0;
                   --next) {
                int newNode =
                    started == 0 && next == 0 ? node : goState(node, next);
                int newSum = sum + getMatch(newNode);
                int newSmaller = smaller | (next < digit ? 1 : 0);
                int newStarted = started | (next > 0 ? 1 : 0);
                if (newSum <= maxCost)
                  add(g[newNode][newSum][newSmaller][newStarted], old);
              }
            }
          }
    memcpy(f, g, sizeof f);
  }
  return res;
}
vector<int> nextNumber() {
  int n;
  cin >> n;
  vector<int> res(n);
  for (int i = 0; i < n; ++i) cin >> res[i];
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  trie[0] = Node();
  nNode = 1;
  int n;
  cin >> n >> base >> maxCost;
  vector<int> low = nextNumber();
  vector<int> high = nextNumber();
  for (int i = 0; i < n; ++i) {
    vector<int> pattern = nextNumber();
    int value;
    cin >> value;
    addString(pattern, value);
  }
  cout << (count(high, false) - count(low, true) + MODULO) % MODULO;
  return 0;
}
