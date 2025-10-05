#include<bits/stdc++.h>
using namespace std;
int cnt[100010]={0};
int main(){
   for(int x=1;x<=100;x++){
    for(int y=1;y<=100;y++){
        for(int z=1;z<=100;z++){
            cnt[x*x+y*y+z*z+x*z+y*z+y*x]++;
        }
    }
   }
   int n;
   scanf("%d",&n);
   for(int i=1;i<=n;i++){
    printf("%d\n",cnt[i]);
   }
    return 0;
}
