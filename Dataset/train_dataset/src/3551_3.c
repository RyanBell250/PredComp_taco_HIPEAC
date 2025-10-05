#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cctype>
#include<math.h>
#include<string>
#include<string.h>
#include<stack>
#include<queue>
#include<vector>
#include<utility>
#include<set>
#include<map>
#include<stdlib.h>
#include<iomanip>
using namespace std;
#define ll long long
#define ld long double
#define EPS 0.0000000001
#define INF 1e9
#define MOD 1000000007
#define rep(i,n) for(i=0;i<(n);i++)
#define loop(i,a,n) for(i=a;i<(n);i++)
#define all(in) in.begin(),in.end()
#define shosu(x) fixed<<setprecision(x)
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pii;
int main(void) {
  int i,j;
  int n;
  cin>>n;
  vi num(13,0);
  rep(i,n){
    int d;
    cin>>d;
    num[d]++;
  }
  rep(i,13)if(num[i]>=3){
    cout<<0<<endl;
    return 0;
  }
  vi t(25,0);
  if(num[0]){
    cout<<0<<endl;
    return 0;
  }
  rep(i,13)if(num[i]==2){
    t[i]++;
    t[24-i]++;
  }
  t[0]++;
  int ans=0;
  int bit;
  rep(bit,1<<13){
    vector<bool> tmp(24,false);
    rep(i,13)if(num[i]==1){
      if((bit&(1<<i))!=0)tmp[i]=true;
      else tmp[24-i]=true;
    }
    int m=INF;
    rep(i,24)rep(j,24)if(i!=j)
      if((t[i]||tmp[i]) && (t[j]||tmp[j])){
	int d=abs(i-j);
	m=min(m, min(d,24-d));
      }
    ans=max(ans,m);
  }
  cout<<ans<<endl;
}
