#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
#define nmax 200500
typedef long long ll;

int n;
set<pair<int, ll> > g[2*nmax];
set<pair<int, ll> > gs[nmax];
vector<pair<int, ll> > gv[2*nmax];
int cur[nmax];
queue<int> listiki;
ll x[nmax];
ll xs[nmax];
vector<int> procrastinate;

ll d[2*nmax];
const int C = 500;









bool alr[nmax];
int state [2*nmax];
deque<int> q;
void dijkstra(bool first = false)
{


























    if (first)
    {
        for (int i=1; i<=2*n; i++)
            d[i]=1e18;
        d[0]=0;
    }
    for (int i=1; i<=2*n; i++)
        state[i]=2;
    state[0] = 1;
    q.clear();
    q.push_back (0);
    while (!q.empty())
    {
        int vertex = q.front();
        q.pop_front();
        state[vertex] = 0;
        for (size_t i = 0; i < gv[vertex].size(); ++i)
        {
            int to = gv[vertex][i].first;
              ll length = gv[vertex][i].second;
            if (d[to] > d[vertex] + length)
            {
                d[to] = d[vertex] + length;
                if (state[to] == 2)
                    q.push_back (to);
                else if (state[to] == 0)
                    q.push_front (to);
                state[to] = 1;
            }
        }
    }
}
ll dist_to_root[nmax];
int dep[nmax];
void dfs(int v, int p=-1, ll d=0, int depth=0)
{
    dist_to_root[v]=d;
    dep[v]=depth;

    for (auto pa:gs[v])
        if (pa.fi != p)
            dfs(pa.fi, v, d+pa.se, depth+1);
}
int lcaf(int u, int v);


















ll dist(int u, int v)
{
    return dist_to_root[u] + dist_to_root[v] - 2*dist_to_root[lcaf(u, v)];
}
vector<pair<signed, signed> > eul;
int tin[nmax];
#define log2 notlog2
int log2[2*nmax];
void dfs2(int v, int p=-1, int d=0)
{
    tin[v]=eul.size();
    eul.pb({d, v});
    for (auto pa:gs[v])
        if (pa.fi != p)
        {
            dfs2(pa.fi, v, d+1);
            eul.pb({d, v});
        }
}
pair<signed, signed> sparse[2*nmax][20];
void build()
{
    log2[1]=0;
    for (size_t i=2; i<=eul.size(); i++)
        log2[i]=log2[i/2]+1;
    for (size_t i=0; i<eul.size(); i++)
        sparse[i][0]=eul[i];
    for (int j=1; j<20; j++)
        for (size_t i=0; i+(1<<j)-1<eul.size(); i++)
    {
        sparse[i][j]=min(sparse[i][j-1], sparse[i+(1<<(j-1))][j-1]);
    }
}
pair<int, int> get(int l, int r)
{
    if (l>r)
        swap(l, r);
    int j=log2[r-l+1];
    return min(sparse[l][j], sparse[r-(1<<j)+1][j]);
}
int lcaf(int u, int v){
    int x=get(tin[u], tin[v]).second;

    return x;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for (int i=1; i<=n; i++)
        cin>>x[i], xs[i]=x[i];



    for (int i=1; i<=n; i++)
        cur[i]=i;
    for (int i=1; i<n; i++)
    {
        int x, y;
        ll w;
        cin>>x>>y>>w;



        g[x].insert({y, w});
        g[y].insert({x, w});
        gs[x].insert({y, w});
        gs[y].insert({x, w});
        gv[x].pb({y, w});
        gv[y].pb({x, w});
    }
    for (int i=1; i<=n; i++)
        if (g[i].size()==1)
            listiki.push(i);
    for (int _=1; _<n; _++)
    {
        int s=listiki.front();
        listiki.pop();
        int t=g[s].begin()->fi;
        ll w=g[s].begin()->se;

        if (x[t] <= x[s] + w)
        {
            procrastinate.push_back(cur[s]);
        }
        else
        {
            procrastinate.push_back(cur[t]);
            cur[t]=cur[s];
            x[t] = x[s] + w;
        }
        g[t].erase({s, w});
        if (g[t].size()==1)
            listiki.push(t);
    }
    for (int i=1; i<=n; i++)
        x[i]=xs[i];
    alr[cur[listiki.front()]]=1;
    reverse(procrastinate.begin(), procrastinate.end());



    dfs(1);
    dfs2(1);
    build();










    ll ans=0;






    int counter=0;
    set<int> buffer = {cur[listiki.front()]};
    for (int i:procrastinate)
    {
        if ((counter++)%C == 0)
        {
            for (int i:buffer)
            {
                
                gv[n+i].pb({i, x[i]});
                gv[0].pb({n+i, 0});
            }
            dijkstra(counter == 1);
            buffer.clear();
        }
        ll mindist=d[i];
        for (int j: buffer)
        {
            mindist=min(mindist, dist(i, j)+xs[j]);
        }

        ans += mindist + xs[i];
        alr[i]=1;
        buffer.insert(i);
    }
    cout<<ans<<"\n";
}
