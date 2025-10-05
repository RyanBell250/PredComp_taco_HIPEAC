#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<vector>
#include<utility>
#define INF 1e9
using namespace std;
typedef pair<string,int>P;
map<string,int >m;
int d[4]={1,-1,4,-4};
void bfs()
{
    int i;
    queue <P> que;
    que.push(P ("01234567",0));
    m["01234567"]=0;
    while(!que.empty())
    {
        P p=que.front();
        que.pop();
        for(i=0;i<4;i++)
        {
            string s=p.first;
            int x=p.second,xx=m[s];
            swap(s[x],s[x+d[i]]);
            if(x+d[i]>=0&&x+d[i]<8&&!(x==3&&i==0)&&!(x==4&&i==1)&&m[s]==0)
            {
                que.push(P(s,x+d[i]));
                m[s]=xx+1;
            }
        }
    }
}
int main()
{
    string pp;
    bfs();
    m["01234567"]=0;
    while(getline(cin,pp))
    {
        pp.erase(remove(pp.begin(), pp.end(), ' '), pp.end());
        cout<<m[pp]<<endl;
    }
    return 0;
}