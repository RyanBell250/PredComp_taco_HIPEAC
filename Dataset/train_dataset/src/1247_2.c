#include<bits/stdc++.h>
using namespace std;



int main(){
  int A,B;
  int t[100][100];
  for(int i=0;i<100;i++){
    for(int j=0;j<100;j++){
      if(j>=50)t[i][j]=0;
      else t[i][j]=1;
    }
  }
  cin>>A>>B;

  for(int i=0;i<100;i+=2){
    for(int j=0;j<49;j+=2){
      if(A>1){
        t[i][j]=0;
        A--;
      }
    }
  }
  
  for(int i=0;i<100;i+=2){
    for(int j=51;j<100;j+=2){
      if(B>1){
        t[i][j]=1;
        B--;
      }
    }
  }

  cout<<100<<' '<<100<<endl;
  for(int i=0;i<100;i++){
    for(int j=0;j<100;j++){
      if(t[i][j]==0)cout<<'.';
      else cout<<'#';
    }
    cout<<endl;
  }

  return 0;
}
