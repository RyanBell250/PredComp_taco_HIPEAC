#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;

map<string, int> dp;
int dir[4]={1,-1,4,-4};

void bfs()
{
    queue<string> q;
    q.push("01234567");
    dp["01234567"]=0;
    while(!q.empty())
    {
      string now = q.front();
      q.pop();
      int p=0;
      for(int j=0; j<8; j++)
      {
          if(now[j]=='0')
          {
              p=j; break;
          }
      }
      for(int i=0; i<4; i++)
      {
          int n=p+dir[i];
          if(n>=0 &&n<8 && !(p==3&&i==0)&&!(p==4&&i==1))
          {
              string next = now;
              swap(next[p], next[n]);
              if(dp.find(next)==dp.end())
              {
                  dp[next]=dp[now]+1;
                  q.push(next);
              }
          }
      }
    }
}


int main()
{
    bfs();
    string s;
    while(getline(cin, s))
    {
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        cout<<dp[s]<<endl;
    }

}