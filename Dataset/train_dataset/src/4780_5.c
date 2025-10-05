#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int(i)=1;i<=(n);i++)

int gcd(int a, int b) {
  return b?gcd(b,a%b):a;
}

int main(){
  int k,ans=0;cin>>k;
  REP(i,k) REP(j,k) REP(l,k){
    ans+=gcd(i,gcd(j,l));
  }
  cout<<ans;  
}
