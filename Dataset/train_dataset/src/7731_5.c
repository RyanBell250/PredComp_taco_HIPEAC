#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <bitset>
using namespace std;

typedef pair<int, int> P;
#define rep(i, n) for (int i=0; i<(n); i++)
#define all(c) (c).begin(), (c).end()
#define uniq(c) c.erase(unique(all(c)), (c).end())
#define index(xs, x) (int)(lower_bound(all(xs), x) - xs.begin())
#define _1 first
#define _2 second
#define pb push_back
#define INF 1145141919
#define MOD 1000000007
int modpow(int x, int k) { int a = 1;
  while (k > 0) {
    if (k & 1) a = (1LL*a*x) % MOD;
    x = (1LL*x*x) % MOD;
    k >>= 1;
  }
  return a;
}

const int B = 12345;
//const int B = 100;
int pB[(int)(1e6+1)], pBinv[(int)(1e6+1)];
struct Hash {
  string S;
  int X[(int)(1e6+1)];
  Hash(string s) : S(s) {
    rep(i, S.length()) X[i] = (1LL*(S[i]-'a')*pB[i])%MOD;
    rep(i, (int)S.length()-1) X[i+1] =(X[i+1]+ X[i])%MOD;
  }
  int f(int l, int r) {
    int s = (X[r]+MOD-(l>0?X[l-1]:0))%MOD;
    return (1LL*s*pBinv[l])%MOD;
  }
};

string S;
int N;
Hash hs(""), hs_rev("");
void go(int len) {
  int T = hs.f(0, len-1);
  int revT = hs_rev.f(N-len, N-1);
  int p = 0;
  bool flip = false;
  for (; p+len-1<N; p+=len-1) {
    if (!flip && T != hs.f(p, p+len-1)) return;
    if ( flip && revT != hs.f(p, p+len-1)) return;
    flip ^= 1;
  }
  int rest = N-p;
  if (!flip && hs.f(0, rest-1) != hs.f(p, N-1)) return;
  if ( flip && hs_rev.f(N-len, N-len+rest-1) != hs.f(p, N-1)) return;
  cout << len << "\n";
  exit(0);
}

signed main() {
  ios::sync_with_stdio(false); cin.tie(0);
  cin >> N;
  cin >> S;
  pB[0] = 1; for (int i=1; i<=N; i++) pB[i] = (1LL*pB[i-1]*B)%MOD;
  int inv = modpow(B, MOD-2);
  pBinv[0] = 1; for (int i=1; i<=N; i++) pBinv[i] = (1LL*pBinv[i-1]*inv)%MOD;

  hs = Hash(S);
  reverse(all(S));
  hs_rev = Hash(S);
  reverse(all(S));
  for (int i=2; i<=N; i++) go(i);
  return 0;
}

