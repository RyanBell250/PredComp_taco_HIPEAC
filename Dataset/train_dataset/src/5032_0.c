#include <bits/stdc++.h>
#define syosu(x) fixed<<setprecision(x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> P;
typedef pair<double,double> pdd;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<string> vs;
typedef vector<P> vp;
typedef vector<vp> vvp;
typedef vector<pll> vpll;
typedef pair<int,P> pip;
typedef vector<pip> vip;
const int inf=1<<30;
const ll INF=1ll<<60;
const double pi=acos(-1);
const double eps=1e-9;
const int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int n,mod;
vi dp(4096);
int main(){
	cin>>n>>mod;
	for(int j=0;j<4096;j++){
		int a=j%2,b=j/2%2,c=j/4%2,d=j/8%2,e=j/16%2,f=j/32%2,g=j/64%2,h=j/128%2,x=j/256%2,y=j/512%2,z=j/1024%2,t=j/2048%2;
		if(x!=t) continue;
		if(x==0&&a==1&&b==1&&c==0&&d==1&&e==1&&f==0&&g==1&&h==1) dp[j]++;
		if(x==1&&a==1&&b==0&&c==1&&d==1&&e==1&&f==1&&g==0&&h==1) dp[j]++;
	}
	for(int i=1;i<n;i++){
		vi DP(4096);
		for(int j=0;j<4096;j++) for(int k=0;k<8;k++){
			int a=j%2,b=j/2%2,c=j/4%2,d=j/8%2,e=j/16%2,f=j/32%2,g=j/64%2,h=j/128%2,x=j/256%2,y=j/512%2,z=j/1024%2,t=j/2048%2;
			int A=0,B=0,C=0,D=0,E=0,F=0,G=0,H=0,X=k%2,Y=k/2%2,Z=k/4%2;
			if(x==0&&y==0&&z==0&&X==1||x==1&&y==1&&z==1&&X==0) continue;
			if(a==1&&y==1) A=1;
			if(b==1&&z==0) B=1;
			if(A==1&&X==0) B=1;
			if(B==1&&X==1) A=1;
			if(c==1&&y==1) C=1;
			if(d==1&&z==0) D=1;
			if(C==1&&X==0) D=1;
			if(D==1&&X==1) C=1;
			if(e==1&&y==0) E=1;
			if(f==1&&z==1) F=1;
			if(E==1&&X==1) F=1;
			if(F==1&&X==0) E=1;
			if(g==1&&y==0) G=1;
			if(h==1&&z==1) H=1;
			if(G==1&&X==1) H=1;
			if(H==1&&X==0) G=1;
			if(i==n-1){
				if(A==1&&Y==1||B==1&&Z==0&&t==1) continue;
				if(D==1&&Z==0||C==1&&Y==1&&t==0) continue;
				if(E==1&&Y==0||F==1&&Z==1&&t==0) continue;
				if(H==1&&Z==1||G==1&&Y==0&&t==1) continue;
				if(X==0&&Y==0&&Z==0&&t==1) continue;
				if(X==1&&Y==1&&Z==1&&t==0) continue;
			}
			(DP[A+B*2+C*4+D*8+E*16+F*32+G*64+H*128+X*256+Y*512+Z*1024+t*2048]+=dp[j])%=mod;
		}
		dp=DP;
	}
	int res=0;
	for(auto i:dp) (res+=i)%=mod;
	cout<<res<<endl;
}
