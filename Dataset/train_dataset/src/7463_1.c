#include <bits/stdc++.h>
#define Maxn 200007
using namespace std;
int last[Maxn],other[Maxn],pre[Maxn],cnt=0;
int father[Maxn],rk[Maxn];
bool flag[Maxn];
int a[Maxn],b[Maxn];
int pos[Maxn],dep[Maxn],val[Maxn],num[Maxn],r=0;
int mn[Maxn][21],p[Maxn][21];
int bin[Maxn];
int que[Maxn];
int stk[Maxn],top;
bool vis[Maxn];
vector<int> g[Maxn];
int n,m,tot=0;
int ans=0,w=0;
int find(int x)
{
    if (x==father[x]) return x;
    father[x]=find(father[x]);
    return father[x];
}
void mdf(int x,int y)
{
    x=find(x),y=find(y);
    if (x==y) return;
    if (rk[x]<rk[y]) swap(x,y);
    rk[x]+=rk[y];
    father[y]=x;
}
void insert(int u,int v)
{
    other[++cnt]=v,pre[cnt]=last[u],last[u]=cnt;
}
void pre_dfs(int u,int fa)
{
    ++r;
    num[r]=u;
    val[r]=dep[u];
    pos[u]=r;
    for (int q=last[u];q;q=pre[q])
    {
        int v=other[q];
        if (v!=fa)
        {
            dep[v]=dep[u]+1;
            pre_dfs(v,u);
            ++r;
            num[r]=u;
            val[r]=dep[u];
        }
    }
}
void pre_st()
{
    for (int i=1;i<=r;i++)
        mn[i][0]=val[i],p[i][0]=i;
    for (int k=1;k<=20;k++)
        for (int i=1;i<=r;i++)
        {
            mn[i][k]=mn[i][k-1],p[i][k]=p[i][k-1];
            if (i+(1<<(k-1))<=r&&mn[i+(1<<(k-1))][k-1]<mn[i][k])
            {
                mn[i][k]=mn[i+(1<<(k-1))][k-1];
                p[i][k]=p[i+(1<<(k-1))][k-1];
            }
        }
    bin[1]=0;
    for (int i=2;i<=r;i++)
        bin[i]=bin[i/2]+1;
}
int get_min(int a,int b)
{
    int k=bin[b-a+1];
    if (mn[a][k]<mn[b-(1<<k)+1][k]) return num[p[a][k]]; else return num[p[b-(1<<k)+1][k]];
}
int get_lca(int u,int v)
{
    return get_min(min(pos[u],pos[v]),max(pos[u],pos[v]));
}
bool cmp(int a,int b)
{
    return pos[a]<pos[b];
}
void process()
{
    int tmp=0;
    for (int i=1;i<=n;i++)
        if (flag[i]) que[++tmp]=i;
    sort(que+1,que+tmp+1,cmp);
    int ntmp=1;
    for (int i=2;i<=tmp;i++)
        if (que[i]!=que[ntmp]) que[++ntmp]=que[i];
    tmp=ntmp;
    top=1;
    stk[top]=1;
    for (int i=1;i<=tmp;i++)
    {
        if (que[i]==1) continue;
        int u=get_lca(stk[top],que[i]);
        if (u==stk[top])
        {
            stk[++top]=que[i];
            continue;
        }
        while (top>1&&dep[stk[top-1]]>=dep[u])
        {
            g[stk[top-1]].push_back(stk[top]);
            --top;
        }
        if (dep[stk[top]]>dep[u])
        {
            g[u].push_back(stk[top]);
            --top;
        }
        if (u!=stk[top]) stk[++top]=u;
        stk[++top]=que[i];
    }
    while (top>1)
    {
        g[stk[top-1]].push_back(stk[top]);
        --top;
    }
    cnt=0;
    memset(last,0,sizeof(last));
    memset(other,0,sizeof(other));
    memset(pre,0,sizeof(pre));
    memset(flag,false,sizeof(flag));
    for (int i=1;i<=n;i++)
    {
        int t=(int)g[i].size();
        for (int j=0;j<t;j++)
        {
            int v=g[i][j];
            insert(v,i),insert(i,v);
            ++w;
            flag[v]=true,flag[i]=true;
        }
    }
}
void dfs(int x,int u)
{
    vis[u]=true;
    for (int q=last[u];q;q=pre[q])
    {
        int v=other[q];
        if (!vis[v]&&v>=x) dfs(x,v);
        if (v==x) ++ans;
    }
    vis[u]=false;
}
void calc()
{
    for (int i=1;i<=tot;i++)
        insert(a[i],b[i]),insert(b[i],a[i]);
    w+=tot;
    ans=0;
    int tmp=0;
    for (int i=1;i<=n;i++)
        if (flag[i]) que[++tmp]=i;
    for (int i=1;i<=tmp;i++)
    {
        for (int j=i;j<=tmp;j++)
            vis[que[j]]=false;
        dfs(que[i],que[i]);
    }
    printf("%d\n",(ans-w)/2);
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        father[i]=i,rk[i]=1;
    for (int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        if (find(u)==find(v))
        {
            flag[u]=true;
            flag[v]=true;
            ++tot;
            a[tot]=u,b[tot]=v;
        } else
        {
            insert(u,v);
insert(v,u);
            mdf(u,v);
        }
    }
    pre_dfs(1,-1);
    pre_st();
    process();
    calc();
    return 0;
}
