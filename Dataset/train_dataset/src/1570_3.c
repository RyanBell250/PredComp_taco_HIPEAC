
#include<bits/stdc++.h>
using namespace std;
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
#define SPEED ios_base::sync_with_stdio(false);cin.tie(nullptr)
#define rep(i,n) for(int i=0; i<(int)(n); i++)
#define all(v) v.begin(), v.end()
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }
using ll = long long;
using ull = unsigned long long;
using P = pair<ll, ll>;
constexpr long double PI = 3.14159265358979323846264338327950288L;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
constexpr ll mod17 = 1e9+7;
constexpr ll mod19 = 1e9+9;
constexpr ll mod9 = 998244353;
ll mod = mod17;
template<typename T>
T mod_pow(T a, ll x) {
  T res = 1;
  while(x > 0) {
    if (x & 1) res *= a;
    a *= a; x >>= 1;
  }
  return res;
}
unordered_map<ll, ll> minvmap;
ll minv(ll a, ll m) {
  auto k = a; auto p = minvmap[a]; if (p != 0) return p;
  ll b = m, u = 1, v = 0;
  while (b) { ll t = a/b; swap(a -= t*b, b); swap(u -= t*v, v); }
  p = (u%m+m)%m; minvmap[k] = p; return p;
}
struct mint {
  ll x;
  mint():x(0){}
  mint(ll x):x((x%mod+mod)%mod){}
  mint& fix() { x = (x%mod+mod)%mod; return *this;}
  mint operator-() const { return mint(0) - *this;}
  mint& operator+=(const mint& a){ if((x+=a.x)>=mod) x-=mod; return *this;}
  mint& operator-=(const mint& a){ if((x+=mod-a.x)>=mod) x-=mod; return *this;}
  mint& operator*=(const mint& a){ (x*=a.x)%=mod; return *this;}
  mint& operator/=(const mint& a){ (x*=minv(a.x, mod))%=mod; return *this; }
  mint operator+(const mint& a)const{ return mint(*this) += a;}
  mint operator-(const mint& a)const{ return mint(*this) -= a;}
  mint operator*(const mint& a)const{ return mint(*this) *= a;}
  mint operator/(const mint& a)const{ return mint(*this) /= a;}
  bool operator<(const mint& a)const{ return x < a.x;}
  bool operator==(const mint& a)const{ return x == a.x;}
};
struct mint64 {
    ull x;
    static ull mod, inv, r2;
    mint64(): x(0){}
    mint64(ull x): x(init(x)) {}
    static ull init(ull x) { return reduce(__uint128_t(x)*r2);}
    static void set_mod(ull m) {
      mod = inv = m;
      for(int i=0; i<5; i++) inv *= 2 - inv*m;
      r2 = -__uint128_t(m)%m;
    }
    static ull reduce(__uint128_t x) {
      ull y = ull(x >> 64) - ull((__uint128_t(ull(x)*inv)*mod)>>64);
      return ll(y) < 0 ? y+mod : y;
    }
    mint64& operator+=(mint64& a) { x+=a.x-mod; if(ll(x)<0) x+=mod; return *this; }
    mint64 operator+(mint64& a) const{ return mint64(*this)+=a; }
    mint64& operator*=(mint64& a) { x=reduce(__uint128_t(x)*a.x); return *this; }
    mint64 operator*(mint64& a) const { return mint64(*this)*=a; }
};
ull mint64::mod, mint64::inv, mint64::r2;
struct Miller {
    const vector<ull> v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    bool suspect(ull a, ull s, ull d, ull n) {
      if (mint64::mod != n) mint64::set_mod(n);
      mint64 one = 1, minusone = n-1, ma = a;
      auto x = mod_pow(ma, d);
      if (x.x == one.x) return true;
      for(int r = 0; r < s; r++) {
        if (x.x == minusone.x) return true;
        x = x * x;
      }
      return false;
    }
    bool check(ull n) {
      if (n < 2 || (n > 2 && n % 2 == 0)) return false;
      ull d = n - 1;
      ull s = 0;
      while (!(d & 1)) {
        d >>= 1;
        s++;
      }
      for (auto a: v) {
        if (a >= n) break;
        if (!suspect(a, s, d, n)) return false;
      }
      return true;
    }
};
class combination {
    public: std::vector<mint> fact;
    public: std::vector<mint> inv;
    combination(int n) {
      fact.resize(n + 1);
      inv.resize(n + 1);
      fact[0] = 1;
      for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
      }
      inv[n] = mint(1) / fact[n];
      for (int i = n - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1);
      }
    }
    public: mint get(int n, int r) {
      if (n < r || n < 0 || r < 0) return 0;
      return fact[n]*inv[r]*inv[n-r];
    }
    public: mint p(int n, int r) {
      if (n < r || n < 0) return 0;
      return fact[n]*inv[n-r];
    }
};
class DSecretPassage {
public:
    void solve(istream& cin, ostream& cout) {
      SPEED;
      string s; cin >> s;
      int n = s.size();
      auto rs = s;
      reverse(all(rs));
      bool dp[n+1][n+1][n+1];
      rep(i, n+1) rep(j, n+1) rep(k, n+1) {
        dp[i][j][k] = false;
      }
      dp[0][0][0] = true;
      for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
          for(int k=0; k<n; k++) {
            if (dp[i][j][k]) {
              if (i < n-1) {
                if (s[i] == '0' || s[i+1] == '0') {
                  dp[i+2][j+1][k] = true;
                }
                if (s[i] == '1' || s[i+1] == '1') {
                  dp[i+2][j][k+1] = true;
                }
              }
              dp[i+1][j][k] = true;
              if (s[i] == '0' && k > 0) {
                dp[i+1][j+1][k-1] = true;
              }
              if (s[i] == '1' && j > 0) {
                dp[i+1][j-1][k+1] = true;
              }
            }
          }
        }
      }
      mod = mod9;
      mint dp2[n+1][n+1][n+1];
      rep(i, n+1) rep(j, n+1) rep(k, n+1) {
        dp2[i][j][k] = 0;
      }
      dp2[0][0][0] = 1;
      for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
          for(int k=0; k<n; k++) {
            if (rs[i] == '0') {
              dp2[i+1][j][k] += dp2[i][j][k];
            } else {
              dp2[i][j+1][k] += dp2[i][j][k];
            }
            if (rs[i] == '1') {
              dp2[i+1][j][k] += dp2[i][j][k];
            } else {
              dp2[i][j][k+1] += dp2[i][j][k];
            }
          }
        }
      }
      mint ans = 0;
      for(int i=0; i<=n; i++) {
        for(int j=0; j<=n; j++) {
          for(int k=0; k<=n; k++) {
            if (!dp[n-i][j][k]) continue;
            ans += dp2[i][j][k];
          }
        }
      }
      cout << (ans -1).x << endl;
    }
};
signed main() {
  DSecretPassage solver;
  std::istream& in(std::cin);
  std::ostream& out(std::cout);
  solver.solve(in, out);
  return 0;
}