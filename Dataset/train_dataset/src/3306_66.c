#include <bits/stdc++.h>
#define uset unordered_set
#define umap unordered_map
#define debug cout<<"ok"<<endl
#define ll long long
#define ii pair<ll, ll>
#define fi first
#define se second
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvl vector<vector<ll>>
#define vl vector<ll>
#define mod 1000000007
#define inf 0x3f3f3f3f
#define For(i, n) for (int i = 0; i < n; i++)
#define forn(i, a, b) for(int i=a;i<=b;i++)
#define pb(a) push_back(a)
#define all(a) a.begin(),a.end()
#define lowbit(x) x&(-x)
using namespace std;
class A {
public:
    void solve() {
        int t;
        cin>>t;
        while(t--){
            int x,y;
            cin>>x>>y;
            string s;
            cin>>s;
            int u=0,d=0,r=0,l=0;
            for(char c:s) {
                if(c=='U') u++;
                if(c=='D') d++;
                if(c=='R') r++;
                if(c=='L') l++;
            }
            bool ok=true;
            if(x>=0){
                if(r<x) ok=false;
            }
            else if(abs(l)<abs(x)) ok=false;
            if(y>=0) {
                if(u<y) ok=false;
            }
            else if(abs(d)<abs(y)) ok=false;
            if(ok) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
};
class B {
public:
    void solve() {
        int t;
        cin>>t;
        while(t--){
            ll n,k;
            cin>>n>>k;
            vl h(n+1);
            forn(i,1,n) cin>>h[i];
            int res=0;
            while(k){
                bool change=false;
                res=1;
                for(int i=1;i<n;i++){
                    if(h[i]>=h[i+1]) res=i+1;
                    else {
                        h[i]++;
                        res=i;
                        k--;
                        change=true;
                        break;
                    }
                }
                if(!change) break;
            }
            if(res==n) cout<<-1<<endl;
            else cout<<res<<endl;
        }
    }
};
class C {
public:
    void solve() {
        int t;
        cin>>t;
        while(t--){
            int n,m;
            cin>>n>>m;
            vi res(m+1,0),a(n+1),b(n+1),c(m+1);
            vi matched(n+1,0);
            unordered_map<int,vector<int>> umc;
            forn(i,1,n) cin>>a[i];
            forn(i,1,n) {
                cin>>b[i];
                if(a[i]==b[i]) matched[a[i]]=i;
                else umc[b[i]].pb(i);
            }
            forn(i,1,m) cin>>c[i];
            vector<int> np;
            for(int i=1;i<=m;i++){
                if(!umc[c[i]].empty()) {
                    res[i]=umc[c[i]].back();
                    matched[c[i]]=res[i];
                    umc[c[i]].pop_back();
                }
                else {
                    if(matched[c[i]]!=0) res[i]=matched[c[i]];
                }
                if(res[i]==0) np.pb(i);
                else{
                    while(!np.empty()) {
                        res[np.back()]=res[i];
                        np.pop_back();
                    }
                }
            }
            int cnt=0;
            for(auto it:umc) cnt+=umc[it.first].size();
            if(!np.empty()||cnt!=0) cout<<"NO"<<endl;
            else{
                cout<<"YES"<<endl;
                forn(i,1,m) cout<<res[i]<<" ";
                cout<<endl;
            }
        }
    }
};
class D {
public:
    void solve(){
        int t;
        cin>>t;
        while(t--){
            int n,m;
            cin>>n>>m;
            vector<string> g(n);
            vector<int> a(3,-1);
            vector<vvi> cnt(n,vvi(2));
            For(i,n) cin>>g[i];
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(j==i) continue;
                    if(cnt[i][g[i][j]-'a'].size()<2)cnt[i][g[i][j]-'a'].pb(j);
                    if(g[i][j]==g[j][i]) {
                        a[0]=i;
                        a[1]=j;
                    }
                }
            }
            if(a[0]!=-1&&a[1]!=-1){
                cout<<"YES"<<endl;
                for(int i=0;i<=m;i++){
                    cout<<a[i%2]+1<<' ';
                }
                cout<<endl;
                continue;
            }
            if(m%2==0){
                bool select=(m/2)%2==0?1:0;
                for(int i=0;i<n;i++){
                    for(int k=0;k<2;k++){
                        for(int p:cnt[i][k]){
                            int next=select?i:p;
                            int flag=select?1-k:k;
                            for(int q:cnt[next][flag]){
                                if(p==q) continue;
                                cout<<"YES"<<endl;
                                a[0]=i+1;
                                a[1]=p+1;
                                a[2]=q+1;
                                for(int r=0;r<=m/2;r++){
                                    cout<<a[r%2]<<" ";
                                }
                                if(select){
                                    a[1]=a[2];
                                }
                                else {
                                    a[0]=a[1];
                                    a[1]=a[2];
                                }
                                for(int r=m/2+1,cur=1;r<=m;r++,cur^=1){
                                     cout<<a[cur]<<" ";
                                }
                                goto GG;
                            }
                        }
                    }
                }
                cout<<"NO";
                GG:cout<<endl;
            }
            else{
                cout<<"YES"<<endl;
                for(int i=0;i<=m;i++){
                    cout<<i%2+1<<' ';
                }
            }
        }
    }
};
class E {
public:
    int solve() {
        int n;
        cin>>n;
        vi a(n+1);
        forn(i,1,n) cin>>a[i];
        int maxn=5e5+10;
        vi cnt(maxn,0);
        vi l(maxn),r(maxn);
        vi dp(n+10,0);
        for(int i=1;i<=n;i++){
            r[a[i]]=i;
        }
        for(int i=n;i>=1;i--){
            l[a[i]]=i;
        }
        dp[n]=1;
        cnt[a[n]]++;
        for(int i=n-1;i>=1;i--){
            cnt[a[i]]++;
            if(i==l[a[i]]){
                dp[i]=max(dp[i],cnt[a[i]]+dp[r[a[i]]+1]);
            }
            dp[i]=max(dp[i],cnt[a[i]]);
            dp[i]=max(dp[i],dp[i+1]);
        }
        cout<<n-dp[1]<<endl;
        return 0;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    E ans;
    ans.solve();
    return 0;
}
