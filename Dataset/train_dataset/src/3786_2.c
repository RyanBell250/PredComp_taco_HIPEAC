#include <bits/stdc++.h>
using namespace std;
template <class T>
T sqr(T x) {
  return x * x;
}
const int INF = 1000 * 1000 * 1000;
const long long INF64 = sqr(static_cast<long long>(INF));
const double PI = acos(-1.0);
const int K = 200500;
long long n, m;
long long mex;
int k, a, b, c;
pair<long long, pair<long long, long long> > h[K], v[K];
pair<long long, long long> w[2 * K];
map<int, int> H, V;
int main() {
  cin >> n >> m >> k;
  if (m % 2 == 0) mex = mex ^ n;
  if (n % 2 == 0) mex = mex ^ m;
  for (int i = 0; i < k; ++i) {
    int bx, by, ex, ey;
    scanf("%d %d %d %d", &by, &bx, &ey, &ex);
    if (bx > ex) swap(bx, ex);
    if (by > ey) swap(by, ey);
    if (bx == ex)
      v[a++] = make_pair((long long)(bx),
                         make_pair((long long)(by), (long long)(ey)));
    else
      h[b++] = make_pair((long long)(by),
                         make_pair((long long)(bx), (long long)(ex)));
  }
  for (int i = 1; i < n && i < 100500; ++i)
    h[b++] =
        make_pair((long long)(i), make_pair((long long)(1), (long long)(1)));
  for (int i = 1; i < m && i < 100500; ++i)
    v[a++] =
        make_pair((long long)(i), make_pair((long long)(1), (long long)(1)));
  sort(v, v + a);
  sort(h, h + b);
  for (int i = 0; i < a;) {
    int j = i + 1;
    while (j < a && v[j].first == v[i].first) ++j;
    int c = 0;
    for (int p = i; p < j; ++p) {
      w[c++] = make_pair(v[p].second.first, 1);
      w[c++] = make_pair(v[p].second.second, 0);
    }
    w[c++] = make_pair(n, 0);
    sort(w, w + c);
    int cnt = 0;
    for (int p = 0, prev = 0, balance = 0; p < c; ++p) {
      if (balance <= 0) cnt += w[p].first - prev;
      if (w[p].second)
        ++balance;
      else
        --balance;
      prev = w[p].first;
    }
    V[v[i].first] = cnt;
    i = j;
  }
  for (int i = 0; i < b;) {
    int j = i + 1;
    while (j < b && h[j].first == h[i].first) ++j;
    int c = 0;
    for (int p = i; p < j; ++p) {
      w[c++] = make_pair(h[p].second.first, 1);
      w[c++] = make_pair(h[p].second.second, 0);
    }
    w[c++] = make_pair(m, 0);
    sort(w, w + c);
    int cnt = 0;
    for (int p = 0, prev = 0, balance = 0; p < c; ++p) {
      if (balance <= 0) cnt += w[p].first - prev;
      if (w[p].second)
        ++balance;
      else
        --balance;
      prev = w[p].first;
    }
    H[h[i].first] = cnt;
    i = j;
  }
  int VV = -1, HH = -1;
  int q = 1;
  for (map<int, int>::const_iterator it = V.begin(); it != V.end(); ++it) {
    if (q != -1) {
      if (it->first == q)
        ++q;
      else {
        VV = q;
        q = -1;
      }
    }
    mex = mex ^ n ^ it->second;
  }
  if (q != -1 && q < m) VV = q;
  q = 1;
  for (map<int, int>::const_iterator it = H.begin(); it != H.end(); ++it) {
    if (q != -1) {
      if (it->first == q)
        ++q;
      else {
        HH = q;
        q = -1;
      }
    }
    mex = mex ^ m ^ it->second;
  }
  if (q != -1 && q < n) HH = q;
  if (VV != -1) V[VV] = n;
  if (HH != -1) H[HH] = m;
  if (mex == 0) {
    cout << "SECOND" << endl;
    return 0;
  }
  cout << "FIRST" << endl;
  for (map<int, int>::const_iterator it = V.begin(); it != V.end(); ++it) {
    int CNT = it->second;
    if ((mex ^ CNT) <= CNT) {
      int x = CNT - (mex ^ CNT);
      for (int i = 0; i < a; ++i) {
        if (v[i].first < it->first) continue;
        int j = i + 1;
        while (j < a && v[j].first == v[i].first) ++j;
        int c = 0;
        for (int p = i; p < j; ++p) {
          w[c++] = make_pair(v[p].second.first, 1);
          w[c++] = make_pair(v[p].second.second, 0);
        }
        w[c++] = make_pair(n, 0);
        sort(w, w + c);
        int cnt = 0;
        for (int p = 0, prev = 0, balance = 0; p < c; ++p) {
          if (balance <= 0) {
            cnt += w[p].first - prev;
            if (cnt >= x) {
              cout << "0 " << it->first << " " << w[p].first - (cnt - x) << " "
                   << it->first << endl;
              return 0;
            }
          }
          if (w[p].second)
            ++balance;
          else
            --balance;
          prev = w[p].first;
        }
        break;
      }
    }
  }
  for (map<int, int>::const_iterator it = H.begin(); it != H.end(); ++it) {
    int CNT = it->second;
    if ((mex ^ CNT) <= CNT) {
      int x = CNT - (mex ^ CNT);
      for (int i = 0; i < b; ++i) {
        if (h[i].first < it->first) continue;
        int j = i + 1;
        while (j < b && h[j].first == h[i].first) ++j;
        int c = 0;
        for (int p = i; p < j; ++p) {
          w[c++] = make_pair(h[p].second.first, 1);
          w[c++] = make_pair(h[p].second.second, 0);
        }
        w[c++] = make_pair(m, 0);
        sort(w, w + c);
        int cnt = 0;
        for (int p = 0, prev = 0, balance = 0; p < c; ++p) {
          if (balance <= 0) {
            cnt += w[p].first - prev;
            if (cnt >= x) {
              cout << it->first << " 0 " << it->first << " "
                   << w[p].first - (cnt - x) << endl;
              return 0;
            }
          }
          if (w[p].second)
            ++balance;
          else
            --balance;
          prev = w[p].first;
        }
        break;
      }
    }
  }
  return 0;
}
