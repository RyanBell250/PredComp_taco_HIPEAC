#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;
typedef pair<int,int>P;
int bdx[]={0,1,1,1,0,-1,-1,-1};
int bdy[]={-1,-1,0,1,1,1,0,-1};
int wdx[]={0,1,0,-1};
int wdy[]={-1,0,1,0};
int h,w;
vector<int>v[10000];
bool used[111][111];
string s[111];
void Input(){
  memset(used,0,sizeof(used));
  r(i,10000)v[i].clear();
  r(i,111)s[i]="";
  r(i,h)cin>>s[i+1],s[i+1]='.'+s[i+1]+'.';
  h+=2;w+=2;
  r(i,w)s[0]+='.',s[h-1]+='.';
}
int cnt;
void tree(int d,int y,int x,int c){
  set<P>::iterator it;
  queue<P>q;
  set<P>st;
  q.push(P(y,x));
  used[y][x]=1;
  while(!q.empty()){
    P p=q.front();q.pop();
    if(d%2){
      r(i,8){
        int ny=p.first+bdy[i];
        int nx=p.second+bdx[i];
        if(ny<0||nx<0||ny>=h||nx>=w)continue;
        if(used[ny][nx])continue;
        if(s[ny][nx]==s[y][x]){
          used[ny][nx]=1;
          q.push(P(ny,nx));
        }
        else st.insert(P(ny,nx));
      }
    }
    else{
      r(i,4){
        int ny=p.first+wdy[i];
        int nx=p.second+wdx[i];
        if(ny<0||nx<0||ny>=h||nx>=w)continue;
        if(used[ny][nx])continue;
        if(s[ny][nx]==s[y][x]){
          used[ny][nx]=1;
          q.push(P(ny,nx));
        }
        else st.insert(P(ny,nx));
      }
    }
  }
  for(it=st.begin();it!=st.end();it++){
    int ny=(*it).first;
    int nx=(*it).second;
    if(used[ny][nx])continue;
    v[c].push_back(cnt+1);
    cnt++;
    tree(d+1,ny,nx,cnt);
  }

}

string isomo(int x){
  string res;
  vector<string>vs;
  r(i,v[x].size()){
    vs.push_back(isomo(v[x][i]));
  }
  sort(vs.begin(),vs.end());
  r(i,vs.size()){
    res+=vs[i];
  }
  return '('+res+')';
}
signed main(){
  while(cin>>h>>w,h){
    cnt=0;
    Input();
    tree(0,0,0,cnt);
    string s1=isomo(0);
    cin>>h>>w;
    cnt=0;
    Input();
    tree(0,0,0,cnt);
    string s2=isomo(0);
    cout<<(s1==s2?"yes":"no")<<endl;
  }
}
