#include<bits/stdc++.h>
using namespace std;
using Int = long long;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
Int MOD;
template<typename T>
struct Mint{
  T v;
  Mint():v(0){}
  Mint(signed v):v(v){}
  Mint(long long t){v=t%MOD;if(v<0) v+=MOD;}
  Mint pow(long long k){
    Mint res(1),tmp(v);
    while(k){
      if(k&1) res*=tmp;
      tmp*=tmp;
      k>>=1;
    }
    return res;
  }
  Mint inv(){return pow(MOD-2);}
  Mint& operator+=(Mint a){v+=a.v;if(v>=MOD)v-=MOD;return *this;}
  Mint& operator-=(Mint a){v+=MOD-a.v;if(v>=MOD)v-=MOD;return *this;}
  Mint& operator*=(Mint a){v=1LL*v*a.v%MOD;return *this;}
  Mint& operator/=(Mint a){return (*this)*=a.inv();}
  Mint operator+(Mint a) const{return Mint(v)+=a;};
  Mint operator-(Mint a) const{return Mint(v)-=a;};
  Mint operator*(Mint a) const{return Mint(v)*=a;};
  Mint operator/(Mint a) const{return Mint(v)/=a;};
  Mint operator-(){return v?MOD-v:v;}
  bool operator==(const Mint a)const{return v==a.v;}
  bool operator!=(const Mint a)const{return v!=a.v;}
  bool operator <(const Mint a)const{return v <a.v;}
};
const Int MAX = 1020;
using M = Mint<Int>;
M dp[2][2][2][2][2][2][2][2][2][2][MAX];
signed main(){
  Int n;
  cin>>n>>MOD;
  dp[0][0][1][1][0][1][1][0][1][1][0]=M(1);
  dp[1][1][1][1][1][0][0][1][1][1][0]=M(1);
  for(int i=0;i<n;i++){
    for(int top=0;top<2;top++){
      for(int prv=0;prv<2;prv++){
        for(int lul=0;lul<2;lul++){
          for(int ldl=0;ldl<2;ldl++){
            for(int lur=0;lur<2;lur++){
              for(int ldr=0;ldr<2;ldr++){                
                for(int rul=0;rul<2;rul++){
                  for(int rdl=0;rdl<2;rdl++){
                    for(int rur=0;rur<2;rur++){
                      for(int rdr=0;rdr<2;rdr++){
                        for(int nl=0;nl<2;nl++){
                          for(int nr=0;nr<2;nr++){
                            for(int na=0;na<2;na++){
                              if(prv==0&&nl==1&&nr==0&&na==1) continue;
                              if(prv==1&&nl==0&&nr==1&&na==0) continue;
                              M tmp=dp[top][prv][lul][ldl][lur][ldr][rul][rdl][rur][rdr][i];
                              int nlul=(lul&&(nl==1)) || (lur&&(nr==1)&&(na==0));
                              int nldl=(ldl&&(nl==0)) || (ldr&&(nr==0)&&(na==1));
                              int nrur=(rur&&(nr==1)) || (rul&&(nl==1)&&(na==1));
                              int nrdr=(rdr&&(nr==0)) || (rdl&&(nl==0)&&(na==0));
                              int nlur=(lur&&(nr==1)) || (lul&&(nl==1)&&(na==1));
                              int nldr=(ldr&&(nr==0)) || (ldl&&(nl==0)&&(na==0));
                              int nrul=(rul&&(nl==1)) || (rur&&(nr==1)&&(na==0));
                              int nrdl=(rdl&&(nl==0)) || (rdr&&(nr==0)&&(na==1));
                              dp[top][na][nlul][nldl][nlur][nldr][nrul][nrdl][nrur][nrdr][i+1]+=tmp;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }    
    }
  }
  M ans(0);
  {
    for(int top=0;top<2;top++){
      for(int prv=0;prv<2;prv++){
        for(int lul=0;lul<2;lul++){
          for(int ldl=0;ldl<2;ldl++){
            for(int lur=0;lur<2;lur++){
              for(int ldr=0;ldr<2;ldr++){                
                for(int rul=0;rul<2;rul++){
                  for(int rdl=0;rdl<2;rdl++){
                    for(int rur=0;rur<2;rur++){
                      for(int rdr=0;rdr<2;rdr++){
                        for(int nl=0;nl<2;nl++){
                          for(int nr=0;nr<2;nr++){
                            {
                              if(top==0&&nl==0&&nr==1&&prv==1) continue;
                              if(top==1&&nl==1&&nr==0&&prv==0) continue;
                              M tmp=dp[top][prv][lul][ldl][lur][ldr][rul][rdl][rur][rdr][n-1];
                              int nlul=(lul&&(nl==1));
                              int nldl=(ldl&&(nl==0));
                              int nrur=(rur&&(nr==1));
                              int nrdr=(rdr&&(nr==0));                 
                              if(nlul||nldl||nrur||nrdr) continue;
                              ans+=tmp;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }    
    }
  }
  cout<<ans.v<<endl;
  return 0;
}
