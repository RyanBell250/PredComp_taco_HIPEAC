#include <bits/stdc++.h>
const int con = 998244353;
using namespace std;
map<int, int> seg[200100];
struct Tree {
  long long sum;
  long long plus;
  long long mult;
} t[1000000];
int n, m;
void PutDown(int x, int nl, int nr, int mid) {
  int temp;
  for (int j = 0; j < 2; ++j) {
    if (j == 0)
      temp = mid - nl + 1;
    else
      temp = nr - mid;
    t[x * 2 + j].sum = (t[x * 2 + j].sum * t[x].mult + t[x].plus * temp) % con;
    t[x * 2 + j].mult = t[x * 2 + j].mult * t[x].mult % con;
    t[x * 2 + j].plus = (t[x * 2 + j].plus * t[x].mult + t[x].plus) % con;
  }
  t[x].plus = 0;
  t[x].mult = 1;
}
void Update(int x) { t[x].sum = (t[x * 2].sum + t[x * 2 + 1].sum) % con; }
int getmin(int a, int b) {
  if (a > b) return b;
  return a;
}
int getmax(int a, int b) {
  if (a > b) return a;
  return b;
}
void Insert(int x, int nl, int nr, int al, int ar, long long pl, int mu) {
  if (nl == al && nr == ar) {
    t[x].sum = (t[x].sum * mu + pl * (nr - nl + 1)) % con;
    t[x].plus = (t[x].plus * mu + pl) % con;
    t[x].mult = t[x].mult * mu % con;
    return;
  }
  int mid = (nl + nr) / 2;
  if (t[x].plus != 0 || t[x].mult != 1) PutDown(x, nl, nr, mid);
  if (al <= mid) Insert(x * 2, nl, mid, al, getmin(ar, mid), pl, mu);
  if (ar > mid) Insert(x * 2 + 1, mid + 1, nr, getmax(al, mid + 1), ar, pl, mu);
  Update(x);
}
long long Ask(int x, int nl, int nr, int al, int ar) {
  if (nl == al && nr == ar) return t[x].sum;
  int mid = (nl + nr) / 2;
  if (t[x].plus != 0 || t[x].mult != 1) PutDown(x, nl, nr, mid);
  long long re = 0;
  if (al <= mid) re += Ask(x * 2, nl, mid, al, getmin(ar, mid));
  if (ar > mid) re += Ask(x * 2 + 1, mid + 1, nr, getmax(al, mid + 1), ar);
  Update(x);
  re %= con;
  return re;
}
int main() {
  scanf("%d %d", &n, &m);
  int type, l, r, d, newl, newr, tl, tr;
  long long ans;
  int u;
  for (int i = 1; i <= 5 * n; ++i) t[i].mult = 1;
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d %d", &type, &l, &r);
    if (type == 1) {
      scanf("%d", &d);
      newl = l;
      newr = r;
      while (true) {
        auto iter = seg[d].lower_bound(l);
        if (iter == seg[d].end() || iter->second > r) {
          if (r >= l) Insert(1, 1, n, l, r, 1, 1);
          break;
        }
        if (iter->second < newl) newl = iter->second;
        if (iter->first > newr) newr = iter->first;
        tl = l;
        if (iter->second > tl) tl = iter->second;
        tr = r;
        if (iter->first < tr) tr = iter->first;
        if (tl > l) Insert(1, 1, n, l, tl - 1, 1, 1);
        Insert(1, 1, n, tl, tr, 0, 2);
        l = tr + 1;
        seg[d].erase(iter);
      }
      seg[d][newr] = newl;
    } else {
      ans = Ask(1, 1, n, l, r);
      printf("%I64d\n", ans);
    }
  }
  return 0;
}
