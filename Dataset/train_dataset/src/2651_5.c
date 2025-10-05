#include "bits/stdc++.h"
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define ll long long int
#define pb push_back
#define f(a) for(ll i = 0;i<a;i++)
#define ffor(i,a,b) for(ll i = a;i<b;i++)
#define rfor(i,a,b) for(ll i = a;i>b;i--)
#define sll set<ll>
#define mll map<ll,ll>
#define vll vector<ll>
#define pll pair<ll,ll>
#define mcl map<char,ll>
#define usll unordered_set<ll,ll>
#define umll unordered_map<ll,ll>
#define umcl unordered_map<char,ll>
#define pqg priority_queue<ll>
#define pqs priority_queue<ll,vll,greater<ll> >
#define T ll t; cin>>t; while(t--)
#define freeopen freopen("input.txt","r",stdin);
#define freeclose freopen("output.txt","w",stdout);
#define MOD 1000000007
#define setbits(x) __builtin_popcountll(x)
#define INF 1000000000000000000
#define all(x) x.begin(), x.end()
using namespace std;
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }
ll modpower(ll x,ll y,ll m){if(y==0)return 1;ll p=modpower(x,y/2,m)%m;p=(p*p)%m;return (y%2==0)?p:(x*p)%m;}
ll power(ll a,ll b)
{
    ll ans = 1;
    while(b) {
        if(b&1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}
bool isPrime(ll n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (ll i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}
void solve()
{
}
int main()
{
    faster
    T
    {
        ll n;
        cin>>n;
        ll a[n];
        vll v;
        map<ll,ll> m;
        f(n){
            cin>>a[i];
            v.pb(a[i]);
            m[a[i]]++;
        }
            ll si=v.size();
            ll tf=1;
            for(ll i=0;i<si;i++)
            {
                for(ll j=0;j<si;j++)
                {
                    if(i!=j)
                    {
                        if(m[(ll)abs(v[i]-v[j])]==0)
                        {
                            if(v.size()>300 || abs(v[i]-v[j])>1000000000)
                            {
                                tf=0;
                                break;
                            }
                            v.pb(abs(v[i]-v[j]));
                            m[(ll)abs(v[i]-v[j])]++;
                            si=v.size();
                        }
                    }
                }
            }
        if(tf)
        {
            cout<<"yes\n"<<v.size()<<"\n";
            for(ll i=0;i<v.size();i++)
                cout<<v[i]<<" ";
            cout<<"\n";
        }
        else
            cout<<"no\n";
    }
}
