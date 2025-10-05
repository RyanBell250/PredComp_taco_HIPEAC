#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
string s,ans;
int n;
 
P getNum(string str,int x){
  int r=0;
  while('0'<=str[x]&&str[x]<='9')
    r=r*10+str[x]-'0',x++;
  return P(x,r);
}
 
void dfs(int b,int e){
  int p=b;
  while(p<=e&&ans.size()<=n){
    if('0'<=s[p]&&s[p]<='9'){
      P r=getNum(s,p);
      int x=r.first,num=r.second;
      int y=r.first,z=r.first;
      if(s[x]=='('){
    int c=1;
    y=x+1;
    for(z=y;z<=e&&c;z++){
      if(s[z]=='(')c++;
      if(s[z]==')')c--;
    }
    p=z;
    z-=2;
    while(num--)dfs(y,z);
      }else{
    while(num--)ans+=s[x];
    p=x+1;
      }
    }
   if('A'<=s[p]&&s[p]<='Z')
      ans+=s[p++];
  }
}
 
int main(){
  while(1){
    cin>>s>>n;
    if(s=="0"&&!n)break;
    dfs(0,s.size()-1);
    if(ans.size()<n+1)
      cout<<0<<endl;
    else cout<<ans[n]<<endl;
    ans.clear();
  }
  return 0;
}