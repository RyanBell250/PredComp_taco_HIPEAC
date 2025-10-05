#include <bits/stdc++.h>
using namespace std;
const long long mod = 1000000007;
const unsigned gen_seed =
    std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937_64 gen(gen_seed);
const int A = 501;
int parent[A * A];
int rk[A * A];
void make_set(int v) {
  parent[v] = v;
  rk[v] = 0;
}
int nb[A][A];
int black[A][A];
int wblack[A][A];
std::vector<std::pair<int, int> > omega;
int find_set(int v) {
  if (v == parent[v]) return v;
  return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);
  if (a != b) {
    if (rk[a] < rk[b]) swap(a, b);
    parent[b] = a;
    if (rk[a] == rk[b]) ++rk[a];
  }
}
void go(int x, int y) {
  black[x][y] = 1;
  std::vector<std::pair<int, int> > st = {make_pair(1, 0), make_pair(-1, 0)};
  if (x % 2 == 0)
    st.push_back(make_pair(1, -1));
  else
    st.push_back(make_pair(-1, 1));
  for (auto shift : st) {
    int x1 = x + shift.first;
    int y1 = y + shift.second;
    if (x1 >= 0 && y1 >= 0 && x1 < A && y1 < A) {
      nb[x1][y1]++;
      if (nb[x1][y1] == 2) omega.push_back(make_pair(x1, y1));
    }
  }
}
int main() {
  for (int i = 0; i < A * A; i++) make_set(i);
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    omega.push_back(make_pair(x, y));
    wblack[x][y] = 1;
    nb[x][y] = 3;
  }
  while (!omega.empty()) {
    auto x = omega.back();
    omega.pop_back();
    go(x.first, x.second);
  }
  int ans = 0;
  for (int i = 0; i < A; i++)
    for (int j = 0; j < A; j++) {
      if (wblack[i][j]) {
        std::vector<std::pair<int, int> > st = {make_pair(1, 0),
                                                make_pair(-1, 0)};
        if (i % 2 == 0)
          st.push_back(make_pair(1, -1));
        else
          st.push_back(make_pair(-1, 1));
        for (auto shift : st) {
          int x1 = i + shift.first;
          int y1 = j + shift.second;
          if (x1 < 0 || y1 < 0 || x1 >= A || y1 >= A || wblack[x1][y1] == 0)
            ans++;
        }
      }
    }
  for (int i = 0; i < A; i++)
    for (int j = 0; j < A; j++) {
      if (black[i][j]) {
        std::vector<std::pair<int, int> > st = {make_pair(1, 0),
                                                make_pair(-1, 0)};
        if (i % 2 == 0)
          st.push_back(make_pair(1, -1));
        else
          st.push_back(make_pair(-1, 1));
        for (auto shift : st) {
          int x1 = i + shift.first;
          int y1 = j + shift.second;
          if (x1 >= 0 && y1 >= 0 && x1 < A && y1 < A && black[x1][y1]) {
            union_sets(i * A + j, x1 * A + y1);
          }
        }
      }
    }
  std::vector<int> comp(A * A, 0);
  std::vector<int> ed(A * A, 0);
  for (int i = 0; i < A; i++)
    for (int j = 0; j < A; j++) {
      if (black[i][j]) {
        comp[find_set(A * i + j)]++;
        std::vector<std::pair<int, int> > st = {make_pair(1, 0),
                                                make_pair(-1, 0)};
        if (i % 2 == 0)
          st.push_back(make_pair(1, -1));
        else
          st.push_back(make_pair(-1, 1));
        for (auto shift : st) {
          int x1 = i + shift.first;
          int y1 = j + shift.second;
          if (x1 >= 0 && y1 >= 0 && x1 < A && y1 < A && black[x1][y1]) {
            ed[find_set(A * i + j)]++;
          }
        }
      }
    }
  for (int i = 0; i < A; i++)
    for (int j = 0; j < A; j++) {
      if (black[i][j] && wblack[i][j] == 0 && comp[find_set(A * i + j)] == 4) {
        std::vector<std::pair<int, int> > st = {make_pair(1, 0),
                                                make_pair(-1, 0)};
        if (i % 2 == 0)
          st.push_back(make_pair(1, -1));
        else
          st.push_back(make_pair(-1, 1));
        int bn = 0;
        for (auto shift : st) {
          int x1 = i + shift.first;
          int y1 = j + shift.second;
          if (x1 >= 0 && y1 >= 0 && x1 < A && y1 < A && wblack[x1][y1]) {
            bn++;
          }
        }
        if (bn == 3) ans -= 2;
      }
    }
  for (int i = 0; i < A * A; i++) {
    if (comp[i] > 0 && (comp[i] - 1) * 2 != ed[i]) {
      cout << "SICK";
      exit(0);
    }
  }
  std::vector<int> taken(A * A, 0);
  for (int i = 0; i < A; i++)
    for (int j = 0; j < A; j++) {
      if (black[i][j]) {
        int par = find_set(A * i + j);
        if (taken[par] == 0) {
          ans -= 2;
          taken[par] = 1;
        }
      }
    }
  cout << "RECOVERED\n";
  cout << ans;
}
