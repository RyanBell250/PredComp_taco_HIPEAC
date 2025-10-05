#include <bits/stdc++.h>
#define repa(x,y,z) for(int x=y;x<z;x++)
#define ll long long int
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define all(a) a.begin(),a.end()
#define memf(a) memset(a,false,sizeof(a))
#define F first
#define S second
#define ot(a) cout<<a<<endl;
#define endl "\n"
#define godspeed ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define vi vector<int>
#define vl vector<long long int>
#define pi 3.141592653589793238
using namespace std;
int M=1e9+7;
ll INF=1e18+7;
ll power( ll b, ll e)
{
    if (e == 0) return 1;
    if (e & 1) return b * power(b * b, e / 2);
    return power(b * b, e / 2);
}
ll powmod(ll a, ll b) {
    if (b == 0)
        return 1;
    ll res = powmod(a, b / 2)%M;
    if (b % 2)
        return ((((ll)res * (ll)res) %M)* (ll)a)%M;
    else
        return ((ll)res * (ll)res)%M;
}
bool comp(const pair<ll, ll>&i, const pair<ll, ll>&j)
{
    return i.first < j.first;
}
void howzat(){
    int n,l,r; cin>>n>>l>>r;
    int a[n];
    repa(i,0,n) cin>>a[i];
    sort(a,a+n);
    ll ans=0;
    repa(i,0,n)
    {
        int x=l-a[i],y=r-a[i];
        auto it1=lower_bound(a+i+1,a+n,x);
        auto it2=upper_bound(a+i+1,a+n,y);
        ans+=it2-it1;
    }
    cout<<ans<<endl;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    godspeed
    #ifdef NCR
        init();
    #endif
    ll t = 1;
    cin >> t;
    repa(i, 0, t)
    {
        howzat();
    }
}
