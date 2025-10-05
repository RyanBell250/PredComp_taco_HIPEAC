#include<iostream>
using namespace std;
#define MAX 1000000
int main()
{
  bool b[MAX+1]={0};
  int i,j;
  b[0]=b[1]=1;
  for(i=4;i<=MAX;i+=2)b[i]=1;
  for(i=3;i*i<=MAX;i+=2)
    if(!b[i])for(j=i+i;j<=MAX;j+=i)b[j]=1;
  int n,x,price[30],dp[MAX+1];
  bool f;
  while(cin>>n>>x,n|x){
    for(i=0;i<n;i++)cin>>price[i];
    for(i=0;i<x+1;i++)dp[i]=(i==0);
    for(i=0;i<x+1;i++){
      if(!dp[i])continue;
      for(j=0;j<n;j++)if(i+price[j]<x+1)dp[i+price[j]]=true;
    }
    f=false;
    for(i=x;i>0;i--)if(dp[i]&!b[i]){f=true;break;}
    if(f)cout<<i<<endl;
    else puts("NA");
  }
}