
#include <bits/stdc++.h> 
using namespace std;
typedef long long ll; 
#define fori(i, n) for (ll(i) = 0; (i) < (n); (i)++) 
#define foria(i, a, b) for (ll(i) = (a); (i) <= (b); (i)++) 
#define foriar(i, a, b) for (ll(i) = (a); (i) >= (b); (i)--)  
#define ff first 
#define ss second 
#define pb push_back 
#define endl '\n'
const ll mod = 1e9 + 7;
const ll imx = INT_MAX;
const ll imn = INT_MIN;
int static dp[1001][1001];
void solve()
{
    ll n;
    cin >> n;
    ll a[n];
    set<ll> s, s1;
    fori(i, n)
    {
        cin >> a[i];
        s.insert(i+1);
        s1.insert(i+1);
    }
    fori(i, n)
    {
        if(s.find(a[i]) != s.end())
        {
            s.erase(a[i]);
            s1.erase(a[i]);
        }
    }
    ll ans1[n];
    ans1[0] = a[0];
    foria(i, 1, n-1)
    {
        if(a[i] != a[i-1])
        {
            ans1[i] = a[i];
        }
        else
        {
            ans1[i] = *s.begin();
            s.erase(s.begin());
        }
    }
    fori(i, n)
    {
        cout << ans1[i] << " ";
    }
    cout << endl;
    s1.insert(n+1);
    ll ans2[n];
    ans2[0] = a[0];
    foria(i, 1, n-1)
    {
        if(a[i] != a[i-1])
        {
            ans2[i] = a[i];
        }
        else
        {
            auto x = s1.lower_bound(a[i]);
            x--;
            ans2[i] = *x;
            s1.erase(*x);
        }
    }
    fori(i, n)
    {
        cout << ans2[i] << " ";
    }
    cout << endl;
}
int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    int t = 1;
    cin >> t;
    fori(_, t)
    {
        solve();
    }
    return 0;
}
