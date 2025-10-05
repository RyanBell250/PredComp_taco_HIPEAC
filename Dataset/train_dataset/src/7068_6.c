#include<iostream>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const int N=50000005;
int s,len[N],p[N];
ll qpow(ll a,ll n)
{
    ll ans=1;
    while(n)
    {
        if(n&1) ans=ans*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return ans;
}
int main()
{
    p[0]=1;
    scanf("%d",&s);
    ll ans=0;
    int sum=0;
    for(int l=1,r=0;l<10000000;l++)
    {
        while(sum<s)
        {
            r++;
            p[r]=p[r-1];
            len[r]=len[r-1];
            if(r/p[r]!=0) p[r]*=10,len[r]++;
            sum+=len[r];
        }
        if(sum==s) ans++;
        sum-=len[l];
    }
    for(int t=1;t<=s/8;t++)
    {
        if(s%t) ans=(ans+1)%mod;
        else ans=(ans+(qpow(10,s/t)-qpow(10,s/t-1)-t+1))%mod;
    }
    ans=(ans+mod)%mod;
    printf("%lld\n",ans);
}