#include <bits/stdc++.h>
using namespace std;
const int BASE = 100002;
int N, M, K;
set<pair<int, int> > S1[300002], S2[300002];
set<pair<int, int> > S;
void add(int x, int y) {
  S.insert(make_pair(x, y));
  S1[BASE + x - y].insert(make_pair(x, y));
  S2[x + y].insert(make_pair(x, y));
}
int block(int x, int y) { return (S.find(make_pair(x, y)) != S.end()); }
int myabs(int x) { return (x < 0 ? -x : x); }
int main() {
  cin.sync_with_stdio(false);
  cin >> N >> M >> K;
  for (int i = 0; i <= N + 1; ++i) {
    add(i, 0);
    add(i, M + 1);
  }
  for (int i = 0; i <= M + 1; ++i) {
    add(0, i);
    add(N + 1, i);
  }
  for (int i = 1, px, py; i <= K; ++i) {
    cin >> px >> py;
    add(px, py);
  }
  int pnx, pny, addx, addy;
  char wh[4];
  cin >> pnx >> pny >> wh;
  if (wh[0] == 'N' && wh[1] == 'E')
    addx = -1, addy = 1;
  else if (wh[0] == 'N' && wh[1] == 'W')
    addx = -1, addy = -1;
  else if (wh[0] == 'S' && wh[1] == 'E')
    addx = 1, addy = 1;
  else
    addx = 1, addy = -1;
  if (addx == -1 && addy == -1) {
    set<pair<int, int> >::iterator it =
        S1[BASE + pnx - pny].lower_bound(make_pair(pnx, pny));
    --it;
    pnx = it->first + 1;
    pny = it->second + 1;
    if ((block(it->first, it->second + 1) + block(it->first + 1, it->second)) %
            2 ==
        0)
      addx = -addx, addy = -addy;
    else if (block(it->first, it->second + 1)) {
      addx = -addx;
      --pny;
    } else {
      addy = -addy;
      --pnx;
    }
  } else if (addx == 1 && addy == 1) {
    set<pair<int, int> >::iterator it =
        S1[BASE + pnx - pny].lower_bound(make_pair(pnx, pny));
    pnx = it->first - 1;
    pny = it->second - 1;
    if ((block(it->first, it->second - 1) + block(it->first - 1, it->second)) %
            2 ==
        0)
      addx = -addx, addy = -addy;
    else if (block(it->first, it->second - 1)) {
      addx = -addx;
      ++pny;
    } else {
      addy = -addy;
      ++pnx;
    }
  } else if (addx == -1 && addy == 1) {
    set<pair<int, int> >::iterator it =
        S2[pnx + pny].lower_bound(make_pair(pnx, pny));
    --it;
    pnx = it->first + 1;
    pny = it->second - 1;
    if ((block(it->first, it->second - 1) + block(it->first + 1, it->second)) %
            2 ==
        0)
      addx = -addx, addy = -addy;
    else if (block(it->first, it->second - 1)) {
      addx = -addx;
      ++pny;
    } else {
      addy = -addy;
      --pnx;
    }
  } else {
    set<pair<int, int> >::iterator it =
        S2[pnx + pny].lower_bound(make_pair(pnx, pny));
    pnx = it->first - 1;
    pny = it->second + 1;
    if ((block(it->first, it->second + 1) + block(it->first - 1, it->second)) %
            2 ==
        0)
      addx = -addx, addy = -addy;
    else if (block(it->first, it->second + 1)) {
      addx = -addx;
      --pny;
    } else {
      addy = -addy;
      ++pnx;
    }
  }
  int ix = pnx, iy = pny, iax = addx, iay = addy;
  long long result = 0;
  bool fnow = false, diff = false;
  while (true) {
    if (pnx == ix && pny == iy && addx == iax && addy == iay && fnow) break;
    if (addx == -1 && addy == -1) {
      set<pair<int, int> >::iterator it =
          S1[BASE + pnx - pny].lower_bound(make_pair(pnx, pny));
      --it;
      result += myabs(it->first - pnx);
      pnx = it->first + 1;
      pny = it->second + 1;
      if ((block(it->first, it->second + 1) +
           block(it->first + 1, it->second)) %
              2 ==
          0) {
        addx = -addx, addy = -addy;
        diff = true;
      } else if (block(it->first, it->second + 1)) {
        addx = -addx;
        --pny;
      } else {
        addy = -addy;
        --pnx;
      }
    } else if (addx == 1 && addy == 1) {
      set<pair<int, int> >::iterator it =
          S1[BASE + pnx - pny].lower_bound(make_pair(pnx, pny));
      result += myabs(it->first - pnx);
      pnx = it->first - 1;
      pny = it->second - 1;
      if ((block(it->first, it->second - 1) +
           block(it->first - 1, it->second)) %
              2 ==
          0) {
        addx = -addx, addy = -addy;
        diff = true;
      } else if (block(it->first, it->second - 1)) {
        addx = -addx;
        ++pny;
      } else {
        addy = -addy;
        ++pnx;
      }
    } else if (addx == -1 && addy == 1) {
      set<pair<int, int> >::iterator it =
          S2[pnx + pny].lower_bound(make_pair(pnx, pny));
      --it;
      result += myabs(it->first - pnx);
      pnx = it->first + 1;
      pny = it->second - 1;
      if ((block(it->first, it->second - 1) +
           block(it->first + 1, it->second)) %
              2 ==
          0) {
        addx = -addx, addy = -addy;
        diff = true;
      } else if (block(it->first, it->second - 1)) {
        addx = -addx;
        ++pny;
      } else {
        addy = -addy;
        --pnx;
      }
    } else {
      set<pair<int, int> >::iterator it =
          S2[pnx + pny].lower_bound(make_pair(pnx, pny));
      result += myabs(it->first - pnx);
      pnx = it->first - 1;
      pny = it->second + 1;
      if ((block(it->first, it->second + 1) +
           block(it->first - 1, it->second)) %
              2 ==
          0) {
        addx = -addx, addy = -addy;
        diff = true;
      } else if (block(it->first, it->second + 1)) {
        addx = -addx;
        --pny;
      } else {
        addy = -addy;
        ++pnx;
      }
    }
    fnow = true;
  }
  cout << result / (diff ? 2 : 1) << '\n';
}
