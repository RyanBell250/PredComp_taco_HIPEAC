#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define uint unsigned
#define pii pair<int,int>
#define pll pair<ll,ll>
#define PB push_back
#define fi first
#define se second
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define CLR(a,v) memset(a,v,sizeof(a));
#define CPY(a,b) memcpy(a,b,sizeof(a));
using namespace std;
const int mo=1000000007;
const int N=75;
int C[N*5][N*5];
int n,k,ans,used[N];
int q1[N],q2[N],suf[N];
int f[N][N];
char s[N];
void init(){
	For(i,0,N*5-1) C[i][0]=1;
	For(i,1,N*5-1) For(j,1,i)
		C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
}
void solve(int S1,int S2){
	if (!S1&&!S2) return ++ans,void(0);
	if ((S1+S2)*2>n+1||S1+2*S2>k) return; 
	memset(used,0,sizeof(used));
	int h=0,t=*q2=0;
	For(i,1,k)
		if (s[i]=='r') q1[++t]=i;
		else if (s[i]=='b'&&h!=t&&*q2!=S2)
			used[q1[++h]]=used[i]=1,q2[++*q2]=i;
	if (*q2!=S2) return;
	For(i,1,S1)
		if (h==t) return;
		else used[q1[++h]]=1;
	Rep(i,k,1) suf[i]=suf[i+1]+(!used[i]);
	For(i,1,S2) q2[i]=suf[q2[i]];
	memset(f,0,sizeof(f));
	f[0][0]=1;
	int upp=max(2,n)+1;
	For(i,2,upp) Rep(j,S2-1,0) For(k,2*j,upp-i*(S2-j)){
		int psum=k-2*j;
		For(l,1,min(S2-j,(upp-k)/i)){
			if ((psum+=i-2)>q2[S2-j-l+1]) break;
			f[j+l][k+i*l]=(f[j+l][k+i*l]+1ll*C[j+l][l]*f[j][k])%mo;
		}
	}
	For(k,0,upp){
		int sum=2*S1+2*k-2*S2-1;
		int par=2*S1+2*k+1;
		if (sum&&sum<=n&&f[S2][k])
			ans=(ans+1ll*f[S2][k]*C[n-sum+par-1][par-1]%mo*C[S2+S1][S2])%mo;
	}
}
int main(){
	init();
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	For(S1,0,n) For(S2,0,n) solve(S1,S2);
	printf("%d\n",ans);
}