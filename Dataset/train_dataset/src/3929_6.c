#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <complex>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stack>
using namespace std;
const double EPS=(1e-10);
typedef long long ll;
typedef pair<int,int> pii;
bool EQ(double a,double b){
  return abs((a)-(b))<EPS;
}
void fast_stream(){
  std::ios_base::sync_with_stdio(0);
}
int L,H;
bool sets[101][101];
string nums[101];
int hits[101];
int blows[101];
int resNum[101];
bool used[101];
int cnt;
int ans[101];
void dfs(int pos){
  if(pos==L){
    bool ok=true;
    for(int i=0;i<H;i++)
      if(hits[i]|blows[i])ok=false;
    if(!ok)return;
    cnt++;
    if(cnt==1)
      for(int i=0;i<pos;i++)ans[i]=resNum[i];
    return;
  }
  else{
    for(int i=0;i<10;i++){
      if(used[i])continue;
      resNum[pos]=i;
      used[i]=true;
      bool ok=true;
      
      for(int j=0;j<H;j++){
	if(nums[j][pos]-'0'==i)hits[j]--;
	else if(sets[j][i])blows[j]--;
	if(hits[j]<0||blows[j]<0)ok=false;
      }
      if(ok)dfs(pos+1);
      used[i]=false;
      for(int j=0;j<H;j++){
	if(nums[j][pos]-'0'==i)hits[j]++;
	else if(sets[j][i])blows[j]++;
      }
    }
  }
}
int main(){
  while(cin>>L>>H&&(L|H)){
    cnt=0;
    memset(sets,0,sizeof(sets));
    memset(used,0,sizeof(used));
    for(int i=0;i<H;i++){
      cin>>nums[i]>>hits[i]>>blows[i];
      for(int j=0;j<nums[i].size();j++)
	sets[i][nums[i][j]-'0']=true;
    }
    dfs(0);
    if(cnt==1){
      for(int i=0;i<L;i++)cout<<ans[i];
      cout<<endl;
    }
    else cout<<"NO"<<endl;
  }
  return 0;
}
