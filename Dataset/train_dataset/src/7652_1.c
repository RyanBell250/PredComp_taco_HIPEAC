#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define rep(i,n)   FOR(i,0,n)
#define pb emplace_back
typedef long long ll;
typedef pair<int,int> pint;

int n,m;
string s;
vector<int> g[200001];
int deg[200001][2];
bool used[200001];
int main(){
    cin>>n>>m>>s;
    int ai,bi;
    rep(i,m){
        cin>>ai>>bi;
        --ai,--bi;
        g[ai].pb(bi);
        g[bi].pb(ai);
        ++deg[ai][s[bi]-'A'];
        ++deg[bi][s[ai]-'A'];
    }
    queue<int> q;
    rep(i,n)if(deg[i][0]==0||deg[i][1]==0) q.push(i);
    int cnt=0;
    while(!q.empty()){
        int v=q.front();q.pop();
        if(!used[v]){
            ++cnt;
            used[v]=true;
            rep(i,g[v].size()){
                --deg[g[v][i]][s[v]-'A'];
                if(deg[g[v][i]][s[v]-'A']==0||deg[g[v][i]][1-(s[v]-'A')]==0) q.push(g[v][i]);
            }
        }
    }
    if(cnt==n) cout<<"No"<<endl;
    else cout<<"Yes"<<endl;
    return 0;
}