#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int w[N] , d[N] , cnt[20] , res , n , st , book[N] , sxr[N];
int main()
{
    scanf("%d" , &n);
    for(int i=1,u,v,va;i<n;i++){scanf("%d%d%d",&u,&v,&va);w[u]^=va;w[v]^=va;}
    for(int i=0;i<n;i++){cnt[w[i]]++;}
    for(int i=1;i<=15;i++)res+=cnt[i]/2,st|=(cnt[i]&1)<<(i-1);  
    for(int i=1;i<(1<<15);i++)d[i]=d[i>>1]+(i&1);
    for(int i=1;i<(1<<15);i++)d[i]-=1; 
    for(int i=1;i<(1<<15);i++)
        for(int j=0;j<15;j++)if((i>>j)&1)sxr[i]^=(j+1);
    for(int i=1;i<(1<<15);i++)
    {
        if(sxr[i]!=0)continue;
        for(int k=(i-1)&i;k;k=(k-1)&i)
            if(sxr[k]==0)d[i]=min(d[i],d[k]+d[i^k]);
    }printf("%d",res+d[st]);return 0;
}