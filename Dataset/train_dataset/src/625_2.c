#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100100;
struct seg {
  seg *fe, *fd;
  int meio, l, r, mex;
  seg(int x, int y) {
    l = x, r = y;
    meio = (x + y) / 2;
    mex = 0;
    if (l == r) return;
    fe = new seg(x, meio);
    fd = new seg(meio + 1, y);
  }
  void up(int pos, int novo) {
    if (l == r) {
      mex = novo;
      return;
    }
    if (pos <= meio)
      fe->up(pos, novo);
    else
      fd->up(pos, novo);
    mex = max(fe->mex, fd->mex);
  }
  int get(int a, int b) {
    if (l >= a && r <= b) return mex;
    if (l > b || r < a) return 0;
    return max(fe->get(a, b), fd->get(a, b));
  }
};
int f[MAXN], v[MAXN];
vector<pair<int, int>> vec;
bool comp1(pair<int, int> a, pair<int, int> b) {
  if (a.first != b.first) return a.first < b.first;
  return a.second < b.second;
}
bool comp2(pair<int, int> a, pair<int, int> b) {
  if (a.first != b.first) return a.first > b.first;
  return a.second < b.second;
}
bool comp3(pair<int, int> a, pair<int, int> b) {
  if (a.first != b.first) return a.first < b.first;
  return a.second > b.second;
}
bool comp4(pair<int, int> a, pair<int, int> b) {
  if (a.first != b.first) return a.first > b.first;
  return a.second > b.second;
}
seg st(1, MAXN);
int esq1[MAXN], esq2[MAXN], dir1[MAXN], dir2[MAXN];
int main() {
  memset(esq1, 0, sizeof esq1);
  memset(dir1, 0, sizeof dir1);
  memset(dir2, 0, sizeof dir2);
  memset(esq2, 0, sizeof esq2);
  memset(f, 0, sizeof f);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
    f[x]++, f[y + 1]--;
  }
  int soma = 0;
  for (int i = 1; i <= m; i++) {
    soma += f[i];
    v[i] = soma;
    vec.push_back({v[i], i});
  }
  sort(vec.begin(), vec.end(), comp1);
  for (int i = 0; i < vec.size(); i++) {
    int r = st.get(1, vec[i].second);
    esq1[vec[i].second] = max(esq1[vec[i].second], r + 1);
    st.up(vec[i].second, r + 1);
  }
  for (int i = 1; i <= m; i++) st.up(i, 0);
  sort(vec.begin(), vec.end(), comp2);
  for (int i = 0; i < vec.size(); i++) {
    int r = st.get(1, vec[i].second);
    esq2[vec[i].second] = max(esq2[vec[i].second], r + 1);
    st.up(vec[i].second, r + 1);
  }
  for (int i = 1; i <= m; i++) st.up(i, 0);
  sort(vec.begin(), vec.end(), comp3);
  for (int i = 0; i < vec.size(); i++) {
    int r = st.get(vec[i].second, m);
    dir1[vec[i].second] = max(dir1[vec[i].second], r + 1);
    st.up(vec[i].second, r + 1);
  }
  for (int i = 1; i <= m; i++) st.up(i, 0);
  sort(vec.begin(), vec.end(), comp4);
  for (int i = 0; i < vec.size(); i++) {
    int r = st.get(vec[i].second, m);
    dir2[vec[i].second] = max(dir2[vec[i].second], r + 1);
    st.up(vec[i].second, r + 1);
  }
  int resp = 0;
  for (int i = 1; i <= m; i++)
    resp = max(resp, max({esq1[i] + dir1[i] - 1, esq1[i] + dir2[i] - 1,
                          esq2[i] + dir1[i] - 1}));
  cout << resp << endl;
}
