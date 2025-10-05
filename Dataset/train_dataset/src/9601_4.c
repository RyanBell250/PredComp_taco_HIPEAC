#include <bits/stdc++.h>
using namespace std;

int main(){
  int n,y;
  cin>>n>>y;
  for(int a=0;a<=n;a++){
    for(int b=0;b<=n;b++){
      if((n-a-b>=0) && 10000*a + 5000*b + 1000*(n-a-b) == y){
        cout<<a<<" "<<b<<" "<<n-a-b<<endl;
        return 0;
      }
    }
  }
  cout<<-1<<" "<<-1<<" "<<-1<<endl;
}