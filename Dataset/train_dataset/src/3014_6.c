#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#pragma comment(linker, "/STACK:400000000")

#define EPS 1e-9
#define INF MOD
#define MOD 1000000007LL
#define fir first
#define foreach(it,X) for(it=X.begin();it!=X.end();it++)
#define iss istringstream
#define ite iterator
#define ll long long
#define mp make_pair
#define rep(i,n) rep2(i,0,n)
#define rep2(i,m,n) for(int i=m;i<n;i++)
#define pi pair<int,int>
#define pb push_back
#define sec second
#define sh(i) (1LL<<i)
#define sst stringstream
#define sz size()
#define vi vector<int>
#define vc vector
#define vl vector<ll>
#define vs vector<string>

int N,M,L,a[8],b[8],c[8],x[8];
ll ans;

ll nCk(int n,int k){
	if(n<k)return 0;
	ll res=1;
	rep2(i,n-k+1,n+1)res*=i;
	rep2(i,1,k+1)res/=i;
	return res;
}

void f(int cur,int blank){
	if(x[cur-1]>M)return;
	if(cur==L){
		int count[21]={};
		rep(i,cur)count[x[i]]++;
		rep(i,cur)rep(j,cur)rep(k,cur){
			int needed[21]={};
			rep(l,7){
				needed[x[i]+l]+=a[l];
				needed[x[j]+l]+=b[l];
				needed[x[k]+l]+=c[l];
			}
			ll res=1;
			rep(l,21)if(needed[l]>count[l])goto fail;
			rep(l,14)res*=nCk(N,count[l]);
			ans+=res*nCk(M-x[cur-1]+blank,blank);
			return;
			fail:;
		}
		return;
	}
	x[cur]=x[cur-1];
	f(cur+1,blank);
	x[cur]=x[cur-1]+1;
	f(cur+1,blank);
	x[cur]=x[cur-1]+2;
	f(cur+1,blank+1);
}

int main(){
	while(cin>>N>>M>>L && N){
		rep(i,7)a[i]=b[i]=c[i]=0;
		string h;
		rep(i,L){
			cin>>h;
			if(h[0]=='a')a[h.sz-1]++;
			if(h[0]=='b')b[h.sz-1]++;
			if(h[0]=='c')c[h.sz-1]++;
		}
		ans=0;
		x[0]=1;
		f(1,1);
		printf("%.11f\n",1.*ans/nCk(N*M,L));
	}
}