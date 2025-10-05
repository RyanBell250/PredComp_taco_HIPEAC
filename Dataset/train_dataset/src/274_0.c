#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;

#define fi first
#define se second
#define repl(i,a,b) for(ll i=(ll)(a);i<(ll)(b);i++)
#define rep(i,n) repl(i,0,n)
#define all(x) (x).begin(),(x).end()
#define dbg(x) cout<<#x"="<<x<<endl
#define mmax(x,y) (x>y?x:y)
#define mmin(x,y) (x<y?x:y)
#define maxch(x,y) x=mmax(x,y)
#define minch(x,y) x=mmin(x,y)
#define uni(x) x.erase(unique(all(x)),x.end())
#define exist(x,y) (find(all(x),y)!=x.end())
#define bcnt __builtin_popcountll

#define INF 1e16
#define mod 1000000007

ll mod_pow(ll a,ll n){
  ll res=1;
  while(n>0){
    if(n&1)res=res*a%mod;
    a=a*a%mod;
    n>>=1;
  }
  return res;
}

ll fac[10010],finv[10010];
ll comb[510][510];
void make_table(){
  for(ll i=0;i<=500;i++){
    comb[i][0]=1;
    comb[i][i]=1;
  }
  for(ll i=1;i<=500;i++)for(ll j=1;j<i;j++){
    comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
  }
}
ll N,K;
vector<vector<ll>> fs;
vector<ll> f;

void dfs(ll i,ll crt,ll sum){
  if(sum-1>N)return ;
  if(i==N){
    fs.push_back(f);
    return ;
  }
  fs.push_back(f);
  for(ll j=crt;j>=1;j--){
    f.push_back(j);
    dfs(i+1,j,sum+(j==1?1+1:(j-1)*2-1+1));
    f.pop_back();
  }
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);

  fac[0]=1;
  rep(i,10000)fac[i+1]=fac[i]*(i+1)%mod;
  rep(i,10001)finv[i]=mod_pow(fac[i],mod-2);
  make_table();

  string S;

  cin>>N>>K>>S;

  dfs(0,36,0);

  ll res=0;

  rep(i,fs.size()){
    vector<ll> f=fs[i];
    ll M=f.size();
    if(M==0)continue;
    vector<bool> used(K,false);
    vector<ll> rs(M,-1);
    ll rcnt=0;
    rep(j,K){
      if(S[j]=='r'){
        used[j]=true;
        rs[rcnt]=j;
        rcnt++;
        if(rcnt==M)break;
      }
    }
    if(rcnt<M)continue;
    vector<ll> bs(M,-1);
    rep(j,M){
      if(f[j]==1)continue;
      repl(k,rs[j],K){
        if(S[k]=='b'&&!used[k]){
          used[k]=true;
          bs[j]=k;
          break;
        }
      }
    }
    bool ok=true;
    rep(j,M){
      if(f[j]>1&&bs[j]==-1){
        ok=false;
      }
    }
    if(!ok)continue;

    rep(j,M){
      if(f[j]<=2)continue;
      ll rest=f[j]-2;
      repl(k,bs[j]+1,K){
        if(!used[k]){
          used[k]=true; rest--;
          if(rest==0)break;
        }
      }
      if(rest!=0){
        ok=false;
        break;
      }
    }
    if(!ok)continue;

    ll rest=(N+1)-(M-1);
    ll sel=0;
    ll cf=fac[M],scnt=0;
    rep(j,M){
      if(j>0&&f[j-1]==f[j])scnt++;
      else{
        cf*=finv[scnt]; cf%=mod;
        scnt=1;
      }
      if(f[j]==1){
        rest--;
        sel+=2;
      }else{
        rest-=(f[j]-1)*2-1;
        sel+=(f[j]-1)*2+2;
      }
    }
    cf*=finv[scnt]; cf%=mod;

    if(rest+sel-1>=0&&sel>=0)res+=comb[rest+sel-1][sel]*cf%mod;
    res%=mod;
  }
  res++;
  res%=mod;

  cout<<res<<endl;

  return 0;
}
