#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull B = 5575777;

int h,w;
char t[20][20];
int ans=15*15;

map< ull , int > mp[20][20];

void dfs(int y,int x,int c){
  if(c>=ans)return;
  
  if(x==w+1){
    dfs(y+1,0,c);
    return;
  }
  
  if(y==h+1){
    ans=min(ans,c);
    return;
  }

  ull key=0;
  int ny=y-1,nx=x-1;
  for(int i=0;i<=2*w+1;i++){
    char ch='z';
    if(0<=ny&&ny<h&&0<=nx&&nx<w)ch=t[ny][nx];
    key=key*B+ch;
    nx++;
    if(nx==w){
      nx=0;
      ny++;
    }
  }
  
  if(mp[y][x].count(key)==0)mp[y][x][key]=15*15;
  if(mp[y][x][key]<=c)return;
  mp[y][x][key]=c;
  
  if(y&&x&&'1'<=t[y-1][x-1]&&t[y-1][x-1]<='9'){
    
  }else{
    dfs(y,x+1,c);
    
  }
  
  if(y<h && x<w && t[y][x]!='.'){
    bool flag=true;
    for(int i=-1;i<=1;i++){
      for(int j=-1;j<=1;j++){
        int py=y+i,px=x+j;
        if(0<=py && py<h && 0<=px&&px<w && '0'<=t[py][px]&&t[py][px]<='9'){
          if(t[py][px]=='0')flag=false;
          t[py][px]--;
        }
      }
    }
    bool flag2=true;
    if(y&&x&&'1'<=t[y-1][x-1]&&t[y-1][x-1]<='9')flag2=false;
    
    if(flag && flag2){
      dfs(y,x+1,c+1);
    }
    
    for(int i=-1;i<=1;i++){
      for(int j=-1;j<=1;j++){
        int py=y+i,px=x+j;
        if(0<=py && py<h && 0<=px&&px<w && '0'-1<=t[py][px]&&t[py][px]<='9'){
          t[py][px]++;
        }
      }
    }
  }
  

}

int main(){
  
  while(cin>>h>>w){
    if(h==0&&w==0)break;
    ans=15*15;
    
    for(int i=0;i<20;i++)
      for(int j=0;j<20;j++)
        mp[i][j].clear();
    
    
    for(int i=0;i<h;i++){
      for(int j=0;j<w;j++){
        cin>>t[i][j];
      }
    }
    
    dfs(0,0,0);
    cout<<ans<<endl;
  }
  return 0;  
}

