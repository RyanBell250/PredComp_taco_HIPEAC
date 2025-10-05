#include<bits/stdc++.h>
using namespace std;

#define int long long

#define rep(i,n) for(int i=0;i<(n);i++)
#define pb push_back
#define all(v) (v).begin(),(v).end()
#define fi first
#define se second
typedef vector<int>vint;
typedef pair<int,int>pint;
typedef vector<pint>vpint;

template<typename A,typename B>inline void chmin(A &a,B b){if(a>b)a=b;}
template<typename A,typename B>inline void chmax(A &a,B b){if(a<b)a=b;}

const int INF=1001001001;
const int INFLL=1001001001001001001ll;
const int mod=1000000007;
inline void add(int &a,int b){
    a+=b;
    if(a>=mod)a-=mod;
}

int N,M,R;
int A[55],B[55];
vint X[66];
int Y[66];

int dpA[55][55];
int dpB[55][55];

void calc(int n,int a[55],int dp[55][55]){
    fill_n(*dp,55*55,0);
    n*=2;
    for(int i=0;i<n;i++)dp[i][i+1]|=1<<a[i];

    bool tmp[55];

    for(int len=2;len<=n;len++){
        for(int i=0;i+len<=n;i++){
            int j=i+len;

            for(int r=0;r<R;r++){
                memset(tmp,0,sizeof(tmp));
                tmp[i]=true;
                for(int k=0;k<X[r].size();k++){
                    for(int l=j;l>=i;l--){
                        tmp[l]=false;
                        for(int w=i;w<l;w++){
                            tmp[l]|=tmp[w]&(dp[w][l]>>X[r][k]&1);
                        }
                    }
                }
                if(tmp[j])dp[i][j]|=1<<Y[r];
            }
        }
    }
}

int dp[33][33];

void solve(){
    rep(i,N){
        cin>>A[i];
        A[i+N]=A[i];
    }
    rep(i,M){
        cin>>B[i];
        B[i+M]=B[i];
    }

    rep(i,R){
        X[i].clear();
        int k;cin>>k;
        X[i].resize(k);
        rep(j,k)cin>>X[i][j];
        cin>>Y[i];
    }

    calc(N,A,dpA);
    calc(M,B,dpB);

    int ans=INT_MIN;
    for(int x=0;x<N;x++){
        for(int y=0;y<M;y++){
            fill_n(*dp,33*33,INT_MIN);
            dp[0][0]=0;
            for(int i=0;i<N;i++){
                for(int j=0;j<M;j++){
                    for(int ii=1;i+ii<=N;ii++){
                        for(int jj=1;j+jj<=M;jj++){
                            if(dpA[x+i][x+i+ii]&dpB[y+j][y+j+jj]){
                                chmax(dp[i+ii][j+jj],dp[i][j]+1);
                            }
                        }
                    }
                }
            }
            chmax(ans,dp[N][M]);
        }
    }
    if(ans<0)puts("-1");
    else printf("%lld\n",ans);
}

signed main(){
    while(cin>>N>>M>>R,N||M||R)solve();
    return 0;
}