#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,n) for(int i=0;i<(n);i++)
#define reps(i,a,b) for(int i=(a);i<(b);i++)
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(),(v).end()
#define fi first
#define se second
using vint=vector<int>;
using pint=pair<int,int>;
using vpint=vector<pint>;
template<typename A,typename B>inline void chmin(A &a,B b){if(a>b)a=b;}
template<typename A,typename B>inline void chmax(A &a,B b){if(a<b)a=b;}
template<class A,class B>
ostream& operator<<(ostream& ost,const pair<A,B>&p){
    ost<<"{"<<p.first<<","<<p.second<<"}";
    return ost;
}
template<class T>
ostream& operator<<(ostream& ost,const vector<T>&v){
    ost<<"{";
    for(int i=0;i<v.size();i++){
        if(i)ost<<",";
        ost<<v[i];
    }
    ost<<"}";
    return ost;
}
struct ModX{
    using ull=uint64_t;
    static const ull mod=(1ll<<61)-1;
    static const ull MASK30=(1ll<<30)-1;
    static const ull MASK31=(1ll<<31)-1;
    ull a;
    ModX& s(ull vv){
        a=vv<mod?vv:vv-mod;
        return *this;
    }
    ModX(ull a=0):a(a%mod){}
    ModX& operator+=(const ModX& x){return s(a+x.a);}
    ModX& operator-=(const ModX& x){return s(a+mod-x.a);}
    ModX& operator*=(const ModX& x){
        const ull au=a>>31;
        const ull ad=a&MASK31;
        const ull bu=x.a>>31;
        const ull bd=x.a&MASK31;
        const ull mid=ad*bu+au*bd;
        const ull midu=mid>>30;
        const ull midd=mid&MASK30;
        const ull z=au*bu*2+midu+(midd<<31)+ad*bd;
        return s((z&mod)+(z>>61));
    }
    ModX operator+(const ModX &x)const{return ModX(*this)+=x;}
    ModX operator-(const ModX &x)const{return ModX(*this)-=x;}
    ModX operator*(const ModX &x)const{return ModX(*this)*=x;}
    bool operator==(const ModX &x)const{return a==x.a;}
    bool operator!=(const ModX &x)const{return a!=x.a;}
    bool operator<(const ModX &x)const{return a<x.a;}
    ModX operator-()const{return ModX()-*this;}
};
istream& operator>>(istream& in,const ModX& a){
    return (in>>a.a);
}
ostream& operator<<(ostream& out,const ModX& a){
    return (out<<a.a);
}
using xint=ModX;
const xint base(1000000007);
const int RHSIZE=1111111;
xint basepow[RHSIZE];
struct RHInit{
    RHInit(){
        basepow[0]=1;
        for(int i=1;i<RHSIZE;i++)basepow[i]=basepow[i-1]*base;
    }
}RHInitDummy;
template<uint32_t mod>
struct ModInt{
    uint32_t a;
    ModInt& s(uint32_t vv){
        a=vv<mod?vv:vv-mod;
        return *this;
    }
    ModInt(int64_t x=0){s(x%mod+mod);}
    ModInt& operator+=(const ModInt &x){return s(a+x.a);}
    ModInt& operator-=(const ModInt &x){return s(a+mod-x.a);}
    ModInt& operator*=(const ModInt &x){
        a=uint64_t(a)*x.a%mod;
        return *this;
    }
    ModInt& operator/=(const ModInt &x){
        *this*=x.inv();
        return *this;
    }
    ModInt operator+(const ModInt &x)const{return ModInt(*this)+=x;}
    ModInt operator-(const ModInt &x)const{return ModInt(*this)-=x;}
    ModInt operator*(const ModInt &x)const{return ModInt(*this)*=x;}
    ModInt operator/(const ModInt &x)const{return ModInt(*this)/=x;}
    bool operator==(const ModInt &x)const{return a==x.a;}
    bool operator!=(const ModInt &x)const{return a!=x.a;}
    bool operator<(const ModInt &x)const{return a<x.a;}
    ModInt operator-()const{return ModInt()-*this;}
    ModInt pow(int64_t n)const{
        ModInt res(1),x(*this);
        while(n){
            if(n&1)res*=x;
            x*=x;
            n>>=1;
        }
        return res;
    }
    ModInt inv()const{return pow(mod-2);}
};
template<uint32_t mod>
istream& operator>>(istream& in,const ModInt<mod>& a){
    return (in>>a.a);
}
template<uint32_t mod>
ostream& operator<<(ostream& out,const ModInt<mod>& a){
    return (out<<a.a);
}
using mint=ModInt<1000000007>;
template<class Mint,int32_t lg>
struct ModIntTable{
    int N;
    vector<Mint>facts,finvs,invs;
    ModIntTable():N(1<<lg),facts(N),finvs(N),invs(N){
        const uint32_t mod=Mint(-1).a+1;
        invs[1]=1;
        for(int i=2;i<N;i++)invs[i]=invs[mod%i]*(mod-mod/i);
        facts[0]=1;
        finvs[0]=1;
        for(int i=1;i<N;i++){
            facts[i]=facts[i-1]*i;
            finvs[i]=finvs[i-1]*invs[i];
        }
    }
    inline Mint fact(int n)const{return facts[n];}
    inline Mint finv(int n)const{return finvs[n];}
    inline Mint inv(int n)const{return invs[n];}
    inline Mint binom(int n,int k)const{return facts[n]*finvs[k]*finvs[n-k];}
    inline Mint perm(int n,int k)const{return facts[n]*finvs[n-k];} 
};
ModIntTable<mint,19>mtable;
xint tree_rnd[111111];
mt19937 mt(119);
uniform_int_distribution<long long>uid(0,(1ll<<61)-2);
struct Pre{
    Pre(){
        for(int i=0;i<111111;i++)tree_rnd[i]=uid(mt);
    }
}PreDummy;
int N,K;
vint G[111111];
int deg[111111];
xint tree_hs[111111];
mint tree_col[111111];
int height[111111];
void dfs(int v,int p){
    height[v]=0;
    tree_col[v]=K;
    map<xint,int>cnt;
    map<xint,mint>mem;
    vector<xint>lis;
    for(auto &u:G[v]){
        if(u==p||deg[u]==2)continue;
        dfs(u,v);
        chmax(height[v],height[u]+1);
        xint h=tree_hs[u];
        cnt[h]++;
        mem[h]=tree_col[u];
        lis.eb(h);
    }
    tree_hs[v]=1;
    for(auto &h:lis)tree_hs[v]*=tree_rnd[height[v]]+h;
    for(auto &q:cnt){
        mint w=mem[q.fi];
        mint tmp=1;
        rep(i,q.se)tmp*=w+i;
        tmp*=mtable.finv(q.se);
        tree_col[v]*=tmp;
    }
}
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
template<class T>
vector<int>zalgorithm(T s){
    vector<int>a(s.size());
    a[0]=s.size();
    int i=1,j=0;
    while(i<s.size()){
        while(i+j<s.size()&&s[j]==s[i+j])j++;
        a[i]=j;
        if(j==0){i++;continue;}
        int k=1;
        while(i+k<s.size()&&k+a[k]<j)a[i+k]=a[k],k++;
        i+=k;j-=k;
    }
    return a;
}
signed main(){
    scanf("%lld%lld",&N,&K);
    rep(i,N){
        int a;
        scanf("%lld",&a);
        a--;
        G[i].pb(a);G[a].pb(i);
    }
    rep(i,N)for(auto &u:G[i]){
        deg[u]++;
    }
    queue<int>que;
    rep(i,N)if(deg[i]==1){
        que.push(i);
    }
    while(que.size()){
        int v=que.front();
        que.pop();
        for(auto &u:G[v]){
            if(--deg[u]==1){
                que.push(u);
            }
        }
    }
    int cyccnt=0;
    rep(i,N)if(deg[i]==2)cyccnt++;
    vint c;
    rep(i,N)if(deg[i]==2){
        c.pb(i);
        break;
    }
    while(c.size()<cyccnt){
        for(auto u:G[c.back()]){
            if(c.size()>1&&c[c.size()-2]==u)continue;
            if(deg[u]!=2)continue;
            c.pb(u);
            break;
        }
    }
    for(auto u:c)dfs(u,-1);
    int n=c.size();
    vector<xint>hs_cw,hs_ccw;
    vector<mint>col_cw;
    hs_cw.pb(0);col_cw.pb(1);
    rep(i,2*n){
        hs_cw.pb(hs_cw.back()*base+tree_hs[c[i%n]]);
        col_cw.pb(col_cw.back()*tree_col[c[i%n]]);
    }
    hs_ccw.pb(0);
    for(int i=2*n-1;i>=0;i--){
        hs_ccw.pb(hs_ccw.back()*base+tree_hs[c[i%n]]);
    }
    vint num(n+1);
    reps(i,1,n+1)num[gcd(i,n)]++;
    mint ans;
    int denom=0;
    vector<xint>uku;
    rep(i,n)uku.pb(tree_hs[c[i]]);
    auto z=zalgorithm(uku);
    int cir=n;
    for(int i=n-1;i>0;i--){
        if(n%i)continue;
        if(z[i]==n-i)cir=i;
    }
    for(int i=1;i<=n;i++){
        if(n%i)continue;
        if(i%cir)continue;
        mint tmp_ans=col_cw[i];
        ans+=tmp_ans*num[i];
        denom+=num[i];
    }
    if(n&1){
        int len=n/2;
        rep(i,n){
            xint h=hs_cw[i+1+len]-hs_cw[i+1]*basepow[len];
            int k=n-1-(i+n-1)%n;
            xint h2=hs_ccw[k+len]-hs_ccw[k]*basepow[len];
            if(h!=h2)continue;
            mint tmp=col_cw[i+1+len]*col_cw[i].inv();
            ans+=tmp;
            denom++;
        }
    }
    else{
        int len=n/2;
        rep(i,n/2){
            xint h=hs_cw[i+len]-hs_cw[i]*basepow[len];
            int k=n-1-(i+n-1)%n;
            xint h2=hs_ccw[k+len]-hs_ccw[k]*basepow[len];
            if(h!=h2)continue;
            mint tmp=col_cw[i+len]*col_cw[i].inv();
            ans+=tmp;
            denom++;
        }
        rep(i,n/2){
            xint h=hs_cw[i+len]-hs_cw[i+1]*basepow[len-1];
            int k=n-1-(i+n-1)%n;
            xint h2=hs_ccw[k+len-1]-hs_ccw[k]*basepow[len-1];
            if(h!=h2)continue;
            mint tmp=col_cw[i+len+1]*col_cw[i].inv();
            ans+=tmp;
            denom++;
        }
    }
    ans/=denom;
    cout<<ans<<endl;
    return 0;
}