#pragma GCC optimize("O3")
#pragma GCC optimize("-Ofast","-funroll-all-loops","-ffast-math")
#include <algorithm>
#include <cassert>
#include <bits/stdc++.h>
#include <functional>
using namespace std;
using LL = long long;
#define int LL
#define eps 1e-8
#define fi first
#define se second
#define endl '\12'
#define eb emplace_back
#define SZ(a) int32_t(a.size())
#define ALL(x) (x).begin(),(x).end()
#define trav(a,x) for (auto& a: x)
#define LOG(FMT...) fprintf(stderr, FMT)
#define close std::ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr),cout<<fixed<<setprecision(10)
#define FOR(i, x, y) for (LL i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (LL i = (x), _##i = (y); i > _##i; --i)
#define SORT_UNIQUE(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#define CASET int ___T; cin>>___T; for(int __CS=1;__CS<=___T;__CS++)
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
constexpr int mod = 1e9+7; 
ll ex_gcd(ll a, ll b, ll& x, ll& y){if(!b){x=1;y=0;return a;}ll ret=ex_gcd(b,a%b,y,x);y-=a/b*x;return ret;}
LL mul(LL u, LL v, LL p) { return (u * v - LL((long double) u * v / p) * p + p) % p; }
LL bin(LL x, LL n, LL MOD) {LL ret = MOD != 1;for (x %= MOD; n; n >>= 1, x = x * x % MOD)if (n & 1) ret = ret * x % MOD;return ret;}
int norm(int x) { return x >= mod ? (x - mod) : x; }
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }
inline ll get_inv(ll a) { ll x, y; ex_gcd(a, mod, x, y); return norm(x + mod);}
template<class T>inline void umin(T &x, T y) {x = x > y ? y : x;}
template<class T>inline void umax(T &x, T y) {x = x < y ? y : x;}
template<class T>inline void dec(T &x, T y) {x -= y; if(x < 0) x += mod;}
template<class T>inline void add(T &x, T y) {x += y; if(x >= mod) x -= mod;}
template<typename T> void read(T &x){ cin >> x; }
template<typename T, typename... Args> void read(T &first, Args& ... args) { read(first); read(args...); }
template<class T>int ctz(T a){return sizeof(T)>2?__builtin_ctzll(a):__builtin_ctz(a);}
template<class T>inline T gcd(T _a,T _b){T a=abs(_a),b=abs(_b);int shift=ctz(a|b);for(b>>=ctz(b),a>>=ctz(a);a;a-=b,a>>=ctz(a))if(a<b)swap(a,b);return b<<shift;}
const double PI = acos(-1.0);
constexpr int INF = 0x3f3f3f3f;
constexpr ll linf = 0x3f3f3f3f3f3f3f3f;
constexpr ull base=2333, P_1=19260817, P_2=999998639;
constexpr int maxn = 1e6+10; 
 
namespace Fread {
const int SIZE = 1 << 21;
char buf[SIZE], *S, *T;
inline char getchar() {
    if (S == T) {
        T = (S = buf) + fread(buf, 1, SIZE, stdin);
        if (S == T) return '\n';
    }
    return *S++;
}
} 
namespace Fwrite {
const int SIZE = 1 << 21;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
    fwrite(buf, 1, S - buf, stdout);
    S = buf;
}
inline void putchar(char c) {
    *S++ = c;
    if (S == T) flush();
}
struct NTR {
    ~ NTR() { flush(); }
} ztr;
} 
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio {
struct Reader {
    template<typename T>
    Reader& operator >> (T& x) {
        char c = getchar();
        T f = 1;
        while (c < '0' || c > '9') {
            if (c == '-') f = -1;
            c = getchar();
        }
        x = 0;
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            c = getchar();
        }
        x *= f;
        return *this;
    }
    Reader& operator >> (char& c) {
        c = getchar();
        while (c == '\n' || c == ' ') c = getchar();
        return *this;
    }
    Reader& operator >> (char* str) {
        int len = 0;
        char c = getchar();
        while (c == '\n' || c == ' ') c = getchar();
        while (c != '\n' && c != ' ') {
            str[len++] = c;
            c = getchar();
        }
        str[len] = '\0';
        return *this;
    }
    Reader(){}
} cin;
struct Writer {
    template<typename T>
    Writer& operator << (T x) {
        if (x == 0) { putchar('0'); return *this; }
        if (x < 0) { putchar('-'); x = -x; }
        static int sta[45];
        int top = 0;
        while (x) { sta[++top] = x % 10; x /= 10; }
        while (top) { putchar(sta[top] + '0'); --top; }
        return *this;
    }
    Writer& operator << (char c) {
        putchar(c);
        return *this;
    }
    Writer& operator << (char* str) {
        int cur = 0;
        while (str[cur]) putchar(str[cur++]);
        return *this;
    }
    Writer& operator << (const char* str) {
        int cur = 0;
        while (str[cur]) putchar(str[cur++]);
        return *this;
    }
    Writer(){}
} cout;
} 
#define cin Fastio :: cin
#define cout Fastio :: cout
 
vi g[maxn];
int len[maxn], a[6][maxn], f[6][maxn],x , y, now = 0, pre = 1, m;
int32_t main()
{
    multiset<int> ss;
    for(int i = 1; i <= 4; i++) {
        cin >> len[i];
    }
    for(int i = 1; i <= 4; i++){
        for(int j = 1; j <= len[i] ; j++){
            cin >> a[i][j];
            if(i == 1) f[0][j] = a[1][j];
        }
    }
    auto swap = [&](int &x, int &y) {
        int t = x;
        x = y, y = t;
        return ;
    };
    for(int i = 2; i <= 4; i++){
        swap(now , pre);
        for(int j = 1; j <= len[i]; j++){
            f[now][j] = linf;
        }
        cin >> m;
        for(int j = 1; j <= len[i]; j++){
            vi().swap(g[j]);
        }
        ss.clear();
        while(m--) {
            cin >> x >> y;
            g[y].eb(x);
        }
        for(int j = 1; j <= len[i-1]; j++){
            ss.insert(f[pre][j]);
        }
        for(int j = 1; j <= len[i]; j++){
            for(int k = 0; k < SZ(g[j]); k++){
                ss.erase(ss.find(f[pre][g[j][k]]));
            }
            int tp = linf;
            if (SZ(ss)) tp = *ss.begin();
            if(tp != linf){
                umin(f[now][j], tp + a[i][j]);
            } 
            for(int k = 0; k < SZ(g[j]); k++){
                ss.insert(f[pre][g[j][k]]);
            }
        }
    }
    int ans = linf;
    for(int i = 1; i <= len[4]; i++){
        umin(ans, f[now][i]);
        cerr<<"ans == " << ans << endl;
    }
    cout << (ans == linf ? -1 : ans) << endl;
    return 0;
}
