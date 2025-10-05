#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "unroll-loops")
using namespace std;
const int maxt = 53;
int to[maxt][2];
int fail[maxt];
bool isend[maxt];
vector<int> meto[maxt];
int IT = 1;
long long F[102][maxt][maxt];
void buildac(vector<vector<int> > &vv) {
  memset(to, -1, sizeof to);
  sort((vv).begin(), (vv).end(), [&](vector<int> a, vector<int> b) {
    return (int)(a).size() < (int)(b).size();
  });
  vector<int> nok((int)(vv).size());
  for (int i = 0; i < (int)(vv).size(); ++i) {
    for (int j = i + 1; j < (int)(vv).size(); ++j) {
      for (int k = 0; k + (int)(vv[i]).size() <= (int)(vv[j]).size(); ++k) {
        bool sm = 1;
        for (int l = 0; l < (int)(vv[i]).size(); ++l) {
          if (vv[i][l] != vv[j][l + k]) {
            sm = 0;
            break;
          }
        }
        if (sm) {
          nok[j] = 1;
          break;
        }
      }
    }
  }
  for (int cnt = 0; cnt < (int)(vv).size(); ++cnt) {
    if (nok[cnt]) continue;
    vector<int> v = vv[cnt];
    int at = 0;
    for (int x : v) {
      int nxt = to[at][x] == -1 ? IT++ : to[at][x];
      to[at][x] = nxt;
      meto[nxt] = meto[at];
      meto[nxt].push_back(x);
      if (isend[at]) isend[nxt] = 1;
      at = nxt;
    }
    isend[at] = 1;
  }
  for (int i = 1; i < IT; ++i) {
    for (int j = 0; j < IT; ++j) {
      if ((int)(meto[j]).size() < (int)(meto[i]).size() &&
          (int)(meto[j]).size() > (int)(meto[fail[i]]).size()) {
        bool ok = 1;
        for (int k = 1; k <= (int)(meto[j]).size(); ++k) {
          if (meto[i][(int)(meto[i]).size() - k] !=
              meto[j][(int)(meto[j]).size() - k]) {
            ok = 0;
            break;
          }
        }
        if (ok) fail[i] = j;
      }
    }
  }
  memset(F, -1, sizeof F);
  for (int i = 0; i < IT; ++i) {
    if (!isend[i]) {
      int tmp = i;
      while (tmp != 0 && (to[tmp][0] == -1)) tmp = fail[tmp];
      if (~to[tmp][0]) {
        F[0][i][to[tmp][0]] = 1;
        ;
      } else
        F[0][i][0] = 1;
    }
    if (!isend[i]) {
      int tmp = i;
      while (tmp != 0 && (to[tmp][1] == -1)) tmp = fail[tmp];
      if (~to[tmp][1]) {
        F[1][i][to[tmp][1]] = 1;
        ;
      } else
        F[1][i][0] = 1;
    }
  }
}
vector<vector<int> > posg;
inline void W(long long &a, long long b) {
  if (a == -1)
    a = b;
  else if (b != -1)
    a = min(a, b);
}
long long dp[102][maxt];
bool go(int N, vector<int> &v) {
  int n = (int)(v).size();
  bool chg = 0;
  if (n == 1) {
    for (int st = 0; st < IT; ++st)
      if (!isend[st])
        for (int en = 0; en < IT; ++en)
          if (!isend[en]) {
            long long tmp = F[N][st][en];
            W(F[N][st][en], F[v[0]][st][en]);
            if (F[N][st][en] != tmp) chg = 1;
          }
    return chg;
  }
  for (int st = 0; st < IT; ++st)
    if (!isend[st]) {
      for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < IT; ++j) dp[i][j] = -1;
      }
      dp[0][st] = 0;
      for (int i = 1; i <= n; ++i) {
        for (int nd = 0; nd < IT; ++nd) {
          if (!isend[nd]) {
            for (int frm = 0; frm < IT; ++frm) {
              if (!isend[frm] && dp[i - 1][frm] != -1 &&
                  F[v[i - 1]][frm][nd] != -1) {
                if (dp[i - 1][frm] <= LLONG_MAX - F[v[i - 1]][frm][nd])
                  W(dp[i][nd], dp[i - 1][frm] + F[v[i - 1]][frm][nd]);
              }
            }
          }
        }
      }
      for (int en = 0; en < IT; ++en)
        if (!isend[en]) {
          long long tmp = F[N][st][en];
          W(F[N][st][en], dp[n][en]);
          if (F[N][st][en] != tmp) chg = 1;
        }
    }
  return chg;
}
vector<int> rg[103];
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  ;
  ;
  int G, numg, m;
  cin >> G >> numg >> m;
  vector<int> aofnum;
  for (int i = 0; i < numg; ++i) {
    int a, k;
    cin >> a >> k;
    aofnum.push_back(a);
    vector<int> hi(k);
    vector<int> seen(102, 0);
    for (int j = 0; j < k; ++j) {
      cin >> hi[j];
      if (!seen[hi[j]]) rg[hi[j]].push_back(i);
      seen[hi[j]] = 1;
    }
    posg.push_back(hi);
  }
  vector<vector<int> > gogo;
  for (int i = 0; i < m; ++i) {
    int k;
    cin >> k;
    vector<int> tmp(k);
    for (int j = 0; j < k; ++j) cin >> tmp[j];
    gogo.push_back(tmp);
  }
  buildac(gogo);
  ;
  queue<int> qq;
  vector<int> inq(G + 2, 0);
  qq.push(G);
  for (int i = 0; i < numg; ++i) {
    rg[G].push_back(i);
  }
  while (!qq.empty()) {
    int x = qq.front();
    qq.pop();
    inq[x] = 0;
    ;
    for (int u : rg[x]) {
      ;
      if (go(aofnum[u], posg[u])) {
        if (!inq[aofnum[u]]) {
          qq.push(aofnum[u]);
          inq[aofnum[u]] = 1;
        }
      }
    }
  }
  for (int i = 0; i < numg; ++i) {
    if (go(aofnum[i], posg[i])) {
      assert(0);
    }
  }
  for (int N = 2; N < G; ++N) {
    long long re = -1;
    for (int j = 0; j < IT; ++j) {
      if (!isend[j]) {
        W(re, F[N][0][j]);
      }
    }
    if (re == -1)
      cout << "YES" << '\n';
    else
      cout << "NO" << ' ' << re << '\n';
  }
}
