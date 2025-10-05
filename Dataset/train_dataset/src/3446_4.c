#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define mp make_pair
#define PI pair<int,int>
#define poly vector<ll>
#define For(i,l,r) for(int i=(int)(l);i<=(int)(r);i++)
#define Rep(i,r,l) for(int i=(int)(r);i>=(int)(l);i--)
#define pb push_back
#define fi first
#define se second
inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline ll read(){
	ll x = 0; char ch = gc(); bool positive = 1;
	for (; !isdigit(ch); ch = gc())	if (ch == '-')	positive = 0;
	for (; isdigit(ch); ch = gc())	x = x * 10 + ch - '0';
	return positive ? x : -x;
}
inline void write(ll a){
    if(a<0){
    	a=-a; putchar('-');
	}
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
inline void writeln(ll a){write(a); puts("");}
inline void wri(ll a){write(a); putchar(' ');}
inline ull rnd(){
	return ((ull)rand()<<30^rand())<<4|rand()%4;
}
const int N=405,mod=998244353;
const ll mod2=(ll)mod*mod*8;
int b[N],sa,sb,n;
ll a[N],A[N],fac[N],ni[N],dp[2][N][N],yc[N],xs[N][N],inv[N];
ll ksm(ll a,int b){
	int ans=1;
	for(;b;b>>=1){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
	}
	return ans;
}
int main(){
	For(i,fac[0]=ni[0]=1,N-1){
		fac[i]=fac[i-1]*i%mod; ni[i]=ksm(fac[i],mod-2);
	}
	n=read(); ll s=0;
	For(i,1,n){s+=(a[i]=read());b[i]=read(); }
	inv[1]=1; For(i,2,n)inv[i]=mod-mod/i*inv[mod%i]%mod;
	s=ksm(s%mod,mod-2);
	For(i,1,n){
		A[i]=a[i]*s%mod;
	}
	dp[0][0][0]=1;
	For(i,1,n){
		int t=i&1,s=t^1;
		For(j,yc[0]=1,b[i]-1)yc[j]=yc[j-1]*A[i]%mod;
		For(j,0,b[i]-1)yc[j]=yc[j]*(mod-ni[j])%mod;
		sa+=a[i]; sb+=b[i]-1;
		For(j,0,sa)For(k,0,sb){
			dp[t][j][k]=j>=a[i]?dp[s][j-a[i]][k]:0;
			int meiju=min(k,b[i]-1);
			For(l,0,meiju){dp[t][j][k]+=dp[s][j][k-l]*yc[l]; if(dp[t][j][k]>=mod2)dp[t][j][k]-=mod2;}
			dp[t][j][k]%=mod;
		} 
	}
	For(i,0,sa-1){
		xs[i][0]=ksm((1-i*s)%mod,mod-2);
		For(j,1,sb){
			xs[i][j]=xs[i][j-1]*j%mod*xs[i][0]%mod;
		}
	}
	ll ans=0;
	For(i,0,sa-1)For(j,0,sb)ans=(ans+xs[i][j]*dp[n&1][i][j])%mod;
	cout<<(-ans%mod+mod)%mod<<endl;
}