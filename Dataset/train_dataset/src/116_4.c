#include <algorithm>  
#include <iostream>  
#include <sstream>  
#include <string>  
#include <cstring>
#include <vector>  
#include <queue>  
#include <set>  
#include <map>  
#include <cstdio>  
#include <cstdlib>  
#include <cctype>  
#include <cmath>  
#include <list>  
#include <cassert>
#include <ctime>
#include <climits>
using namespace std;  
#define PB push_back  
#define MP make_pair  
#define SZ(v) ((int)(v).size())  
#define FOR(i,a,b) for(int i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)  
#define REPE(i,n) FORE(i,0,n)  
#define FORSZ(i,a,v) FOR(i,a,SZ(v))  
#define REPSZ(i,v) REP(i,SZ(v))  
typedef long long ll;
typedef unsigned long long ull;
ll gcd(ll a,ll b) { return b==0?a:gcd(b,a%b); }
const int MOD=1000000007;
const int MAXDIM=100;
int pw(int x,int n) { int ret=1; while(true) { if(n&1) ret=(ll)ret*x%MOD; if((n>>=1)==0) return ret; x=(ll)x*x%MOD; } }
void inc(int &a,ll b) { a=(a+b)%MOD; }
void dec(int &a,ll b) { a=(a+MOD-b%MOD)%MOD; }
int solve1(int x,int X) {
	int nx=X/x,ret=0;
	inc(ret,x);
	
	return ret;
}
int solve2(int x,int y,int X,int Y) {
	int nx=X/x,ny=Y/y,ret=0;
	inc(ret,(ll)pw(solve1(x,X),ny)*y);
	inc(ret,(ll)pw(solve1(y,Y),nx)*x);
	dec(ret,(ll)x*y);
	
	return ret;
}
int C[MAXDIM+1][MAXDIM+1];
int dp[MAXDIM+1][MAXDIM+1][MAXDIM+1]; 
int solve3(int x,int y,int z,int X,int Y,int Z) {
	if(X%x!=0||Y%y!=0||Z%z!=0) return 0;
	int nx=X/x,ny=Y/y,nz=Z/z,ret=0;
	
	inc(ret,(ll)pw(solve2(x,y,X,Y),nz)*z);
	inc(ret,(ll)pw(solve2(y,z,Y,Z),nx)*x);
	inc(ret,(ll)pw(solve2(z,x,Z,X),ny)*y);
	dec(ret,(ll)pw(solve1(x,X),ny*nz)*y*z);
	dec(ret,(ll)pw(solve1(y,Y),nz*nx)*z*x);
	dec(ret,(ll)pw(solve1(z,Z),nx*ny)*x*y);
	inc(ret,(ll)x*y*z);
	
	memset(dp,0,sizeof(dp)); dp[0][0][0]=1;
	REP(cz,nz) REPE(cx,nx) REPE(cy,ny) {
		int cdp=dp[cz][cx][cy]; if(cdp==0) continue;
		inc(dp[cz+1][cx][cy],cdp); 
		REPE(dx,nx-cx) { 
			int ways=pw(y,cx); if(dx==0) dec(ways,1);
			ways=(ll)ways*pw(y-1,dx)%MOD;
			ways=(ll)ways*C[nx-cx][dx]%MOD;
			inc(dp[cz+1][cx+dx][cy],(ll)cdp*ways);
		}
		REPE(dy,ny-cy) { 
			int ways=pw(x,cy); if(dy==0) dec(ways,1);
			ways=(ll)ways*pw(x-1,dy)%MOD;
			ways=(ll)ways*C[ny-cy][dy]%MOD;
			inc(dp[cz+1][cx][cy+dy],(ll)cdp*ways);
		}
	}
	FORE(cx,1,nx-1) FORE(cy,1,ny-1) {
		int cdp=dp[nz][cx][cy]; if(cdp==0) continue;
		int npillars=(nx-cx)*(ny-cy);
		int ways=pw(z,npillars); dec(ways,1);
		ways=(ll)ways*x*y*z%MOD;
		inc(ret,(ll)cdp*ways);
	}
	return ret;
}
int x,y,z,X,Y,Z;
void run() {
	REPE(i,MAXDIM) { C[i][0]=C[i][i]=1; FOR(j,1,i) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD; }
	scanf("%d%d%d%d%d%d",&x,&y,&z,&X,&Y,&Z);
	printf("%d\n",solve3(x,y,z,X,Y,Z));
}
int main() {
	run();
	return 0;
}
