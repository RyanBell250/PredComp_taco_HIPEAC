#include<bits/stdc++.h>
using namespace std;

#define rep(i,n) for(i=0;i<n;i++)
#define ll long long
#define all(v) v.begin(), v.end()

int main()
{
  int n;cin>>n;
  int k;cin>>k;
  vector<int> p(k);
  vector<int> q(k);
  int i,j,l,m;
  rep(i,k)cin>>p[i]>>q[i];
  vector<vector<bool>> er(14,vector<bool>(7,false));
  rep(i,k)
  {
    er[p[i]][q[i]]=true;
  }
  
  vector<vector<bool>> use(10,vector<bool>(7,false));
  use[0]={1,1,1,0,1,1,1};
  use[1]={0,0,1,0,0,1,0};
  use[2]={1,0,1,1,1,0,1};
  use[3]={1,0,1,1,0,1,1};
  use[4]={0,1,1,1,0,1,0};
  use[5]={1,1,0,1,0,1,1};
  use[6]={1,1,0,1,1,1,1};
  use[7]={1,0,1,0,0,1,0};
  use[8]={1,1,1,1,1,1,1};
  use[9]={1,1,1,1,0,1,1};
  vector<ll> secc(15,0);
  rep(i,60)
  {
    int small=i%10;
    int large=i/10;
    int kc=0;
    rep(j,7)
    {
      if(use[small][j]&(!er[13][j]))
      {
        kc++;
      }
      if(use[large][j]&(!er[12][j]))
      {
        kc++;
      }
    }
    secc[kc]++;
  }
  vector<ll> minc(15,0);
  rep(i,60)
  {
    int small=i%10;
    int large=i/10;
    int kc=0;
    rep(j,7)
    {
      if(use[small][j]&(!er[11][j]))
      {
        kc++;
      }
      if(use[large][j]&(!er[10][j]))
      {
        kc++;
      }
    }
    minc[kc]++;
  }
  vector<ll> hourc(15,0);
  rep(i,24)
  {
    int small=i%10;
    int large=i/10;
    int kc=0;
    rep(j,7)
    {
      if(use[small][j]&(!er[9][j]))
      {
        kc++;
      }
      if(use[large][j]&(!er[8][j]))
      {
        kc++;
      }
    }
    hourc[kc]++;
  }
  vector<ll> times(43,0);
  rep(i,14+1)rep(j,14+1)rep(l,14+1)
  {
    times[i+j+l]+=secc[i]*minc[j]*hourc[l];
  }
  
  vector<ll> days(29,0);
  vector<ll> days_ur(29,0);
  vector<ll> years(29,0);
  vector<ll> years_ur(29,0);
  vector<int> md={31,29,31,30,31,30,31,31,30,31,30,31};
  for(i=1;i<=12;i++)
  {
    int ms=i%10;
    int ml=i/10;
    int lc=0;
    rep(m,7)
    {
      if(use[ms][m]&(!er[5][m]))
      {
        lc++;
      }
      if(use[ml][m]&(!er[4][m]))
      {
        lc++;
      }
    }
    for(j=1;j<=md[i-1];j++)
    {
      int small=j%10;
      int large=j/10;
      int kc=lc;
      rep(l,7)
      {
        if(use[small][l]&(!er[7][l]))
        {
          kc++;
        }
        if(use[large][l]&(!er[6][l]))
        {
          kc++;
        }
      }
      if(i!=2||j!=29)days[kc]++;
      days_ur[kc]++;
    }
    

  }
  rep(i,10000)
  {
    int d3=i%10;
    int d2=i/10%10;
    int d1=i/100%10;
    int d0=i/1000%10;
    int kc=0;
    bool ur=false;
    if(i%400==0||(i%4==0&&i%100!=0))ur=true;
    rep(j,7)
    {
      if(use[d3][j]&(!er[3][j]))
      {
        kc++;
      }
      if(use[d2][j]&(!er[2][j]))
      {
        kc++;
      }
      if(use[d1][j]&(!er[1][j]))
      {
        kc++;
      }
      if(use[d0][j]&(!er[0][j]))
      {
        kc++;
      }
    }
    if(ur)years_ur[kc]++;
    else years[kc]++;
  }
  ll ans=0;
  rep(i,28+1)rep(j,28+1)rep(l,42+1)
  {
    if(i+j+l==n)
    {
      ans+=years[i]*days[j]*times[l];
    }
  }
  rep(i,28+1)rep(j,28+1)rep(l,42+1)
  {
    if(i+j+l==n)
    {
      ans+=years_ur[i]*days_ur[j]*times[l];
    }
  }
  cout<<ans<<endl;
}
