#include <bits/stdc++.h>
using namespace std;
int nofkni, noffig, w, firsti;
vector<int> st(1200005, -1);
int stpos[300005];
void build(int l, int r, int pos) {
  if (l == r) {
    stpos[l] = pos;
    st[pos] = -1;
    return;
  }
  int m = (l + r) / 2;
  build(l, m, 2 * pos + 1);
  build(m + 1, r, 2 * pos + 2);
  st[pos] = -1;
  return;
}
void update(int ul, int ur, int uv, int l, int r, int pos) {
  if (l > r) return;
  if (ur < l || r < ul) return;
  if (st[pos] > 0) return;
  if (ul <= l && r <= ur) {
    if (st[pos] == -1) {
      st[pos] = uv;
    }
    return;
  }
  int m = (l + r) / 2;
  update(ul, ur, uv, l, m, 2 * pos + 1);
  update(ul, ur, uv, m + 1, r, 2 * pos + 2);
  return;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> nofkni >> noffig;
  build(0, nofkni - 1, 0);
  for (int i = 0; i < noffig; i++) {
    int fl, first, fw;
    cin >> fl >> first >> fw;
    if (i == (noffig - 1)) w = fw;
    if (fw - fl) update(fl - 1, fw - 2, fw, 0, nofkni - 1, 0);
    if (first - fw) update(fw, first - 1, fw, 0, nofkni - 1, 0);
  }
  st[0] = 0;
  for (int i = 0; i < nofkni; i++) {
    if ((i + 1) == w) {
      cout << 0 << " ";
    } else {
      int pos = stpos[i];
      while (st[pos] < 0) pos = (pos - 1) / 2;
      cout << st[pos] << " ";
    }
  }
  return 0;
}
