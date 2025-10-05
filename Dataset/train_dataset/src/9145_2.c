#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pair<int, int> > vii;
#define rrep(i, m, n) for(int (i)=(m); (i)<(n);  (i)++)
#define erep(i, m, n) for(int (i)=(m); (i)<=(n); (i)++)
#define  rep(i, n)    for(int (i)=0; (i)<(n);  (i)++)
#define rrev(i, m, n) for(int (i)=(n)-1; (i)>=(m); (i)--)
#define erev(i, m, n) for(int (i)=(n); (i)>=(m); (i)--)
#define  rev(i, n)    for(int (i)=(n)-1; (i)>=0; (i)--)
#define vrep(i, c)    for(__typeof((c).begin())i=(c).begin(); i!=(c).end(); i++)
#define  ALL(v)       (v).begin(), (v).end()
#define pb            push_back
template<class T, class S> inline pair<T, S> mp(T x, S y){ return make_pair(x, y); }
template<class T, class S> inline bool minup(T& m, S x){ return m>(T)x ? (m=(T)x, true) : false; }
template<class T, class S> inline bool maxup(T& m, S x){ return m<(T)x ? (m=(T)x, true) : false; }

static const int    INF = 1000000000;
static const ll     MOD = 1000000007LL;
static const double EPS = 1E-12;

int w, h;
const int MAX_H = 30;
const int MAX_W = 30;
const int MAX_T = 12;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
char c[MAX_H][MAX_W+1];
int d[MAX_H][MAX_W][MAX_H][MAX_W];
int dp[1<<MAX_T][MAX_T];
int sx, sy;

inline bool check(int hx, int hy){ return 0 <= hx && hx < h && 0 <= hy && hy < w; }

int main()
{
  while(cin >> w >> h, h){
    rep(i, h) rep(j, w) rep(k, h) rep(l, w) d[i][j][k][l] = INF;
    rep(i, h) rep(j, w) cin >> c[i][j];
    rep(i, h) rep(j, w) if(c[i][j] == 'o') sx = i,  sy = j;

    rep(i, h) rep(j, w) d[i][j][i][j] = 0;
    rep(i, h) rep(j, w) rep(k, 4) if(c[i][j] != 'x'){
      int nx = i + dx[k];
      int ny = j + dy[k];
      if(check(nx, ny)){
        if(c[nx][ny] != 'x') d[i][j][nx][ny] = 1;
        if(c[nx][ny] == 'x') d[i][j][nx][ny] = INF;
      }
    }

    rep(k1, h) rep(k2, w) rep(i1, h) rep(i2, w) rep(j1, h) rep(j2, w) minup(d[i1][i2][j1][j2], d[i1][i2][k1][k2] + d[k1][k2][j1][j2]);

    vii vec;
    int n = 0;
    rep(i, h) rep(j, w) if(c[i][j] == '*'){
      n += 1;
      vec.pb(mp(i, j));
    }

    rep(i, 1 << n) rep(j, n) dp[i][j] = INF;
    rep(i, n) dp[1 << i][i] = d[sx][sy][vec[i].first][vec[i].second];

    rep(S, 1 << n) rep(v, n) rep(u, n) minup(dp[S | 1 << u][u], dp[S][v] + d[vec[v].first][vec[v].second][vec[u].first][vec[u].second]);

    int res = INF;
    rep(i, n) minup(res, dp[(1 << n) - 1][i]);
    cout << (res >= INF ? -1 : res) << endl;
  }

  return 0;
}