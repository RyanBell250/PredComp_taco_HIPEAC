
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define  P pair<ll,ll>
#define FOR(i,n,m) for(ll i=n; i<(ll)m;i++)
#define FORr(i,m,n) for(ll i=n; i>=(ll)m; i--)
#define FORm(i,m) for(auto i=m.begin();i!=m.end();i++)
#define sortAl(v) sort(v.begin(),v.end())
#define sortAlr(v) sort(v.begin(),v.end()); reverse(v.begin(),v.end())
#define cout(n) cout<<fixed<<setprecision(n)
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll r,s,p;
    cin>>r>>s>>p;
    vector<ll> v(600000);
    FOR(i,0,p){
        ll x,y;
        cin>>x>>y;
        if(y>s) y = y-s;
        else y = s+1-y;
        x = r-x+1;
        v[x+y]++; 
    }
    ll res = 0;
    FOR(i,0,599999){
        if(v[i] != 0){
            v[i+1] = v[i+1] + v[i] - 1;
            res = i;
        }
    }
    cout<<res<<endl;
}
