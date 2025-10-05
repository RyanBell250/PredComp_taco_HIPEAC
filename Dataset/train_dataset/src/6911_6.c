#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
#define REP(i,b,n) for(int i=b;i<n;i++)
#define rep(i,n)   REP(i,0,n)
#define num first
#define ch  second

const int score[4]={0,60,70,80};

int getstate(int *in){
  int ret=0;
  for(int i=0;i<5;i++){
    ret=(ret<<2)+in[i];
  }
  return ret;
}

int dp[5][(1<<11)]={0};
bool isexist[5][5];
bool vis[5][(1<<11)];
int button(int n,int ini[5],int next[5]){
//   if (n== 2 && vis[n-1][getstate(ini)]){
//     rep(i,5)cout << ini[i] <<" " ;
//   }
  if (!vis[n-1][getstate(ini)])return 0;
  int maxi=0;
  rep(i,4){
    rep(j,4){
      rep(k,4){
	rep(l,4){
	  int next1[5],next2[5];
	  rep(jj,5)next1[jj]=ini[jj],next2[jj]=next[jj];
	  next1[0]=(next1[0]+i)%4;
	  next1[1]=(next1[1]+i+j)%4;
	  next1[2]=(next1[2]+j+k)%4;
	  next1[3]=(next1[3]+k+l)%4;
	  next1[4]=(next1[4]+l)%4;
	  
	  next2[0]=(next2[0]+i)%4;
	  next2[1]=(next2[1]+i+j)%4;
	  next2[2]=(next2[2]+j+k)%4;
	  next2[3]=(next2[3]+k+l)%4;
	  next2[4]=(next2[4]+l)%4;
	  rep(jj,5){
	    if (!isexist[n-1][jj])next1[jj]=0;
	    if (!isexist[n  ][jj])next2[jj]=0;
	  }

	  int a=getstate(next2),b=getstate(ini);
	  int tmp=0,tmp2=0;
	  rep(jj,5){
	    if (isexist[n-1][jj])tmp+=score[next1[jj]];
	  }
	  rep(jj,5){
	    if (isexist[n  ][jj])tmp2+=score[next2[jj]];
	  }
	  dp[n][a]=max(dp[n][a],dp[n-1][b]+tmp);
	  vis[n][a]=true;
	  maxi=max(dp[n][a]+tmp2,maxi);
	}
      }
    }
  }
  return maxi;
}

int search(int n,int now,int *ini,int *next){
  if (now == 5){
    return button(n,ini,next);
  }
  if (!isexist[n-1][now]){
    ini[now]=0;
    return search(n,now+1,ini,next);
  }
  int maxi=0;
  rep(i,4){
    ini[now]=i;
    maxi=max(maxi,search(n,now+1,ini,next));
  }
  return maxi;
}

int main(){
  int te;
  cin>>te;
  while(te--){
    rep(i,5)rep(j,(1<<11))dp[i][j]=0,vis[i][j]=false;
    int a[5][5];
    int arr[5];
    rep(i,5){
      rep(j,5){
	cin>>a[i][j];
	if (a[i][j] == 0)isexist[i][j]=false;
	else {
	  isexist[i][j]=true;
	  a[i][j]--;
	}
      }
    }

    vis[0][getstate(a[0])]=true;
    
    int ans=0;
    REP(i,1,5){
      ans=max(ans,max(ans,search(i,0,arr,a[i])));
    }
    cout << ans << endl;

  }
  return false;
}