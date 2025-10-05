#include<iostream>
#include<vector>
#include<map>
#include<cstdio>
#include<deque>
#include<cmath>
#include<algorithm>
#define F first
#define S second
#define pb push_back
using namespace std;
typedef pair<int,int> P;
typedef pair<P,P> PP;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<P> VP;
typedef pair<VVI,VP> VVIVP;
map<VVI,int> memo,bidirectional;
VVI final;
VP ini;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
P Fpos[] = {P(0,0),P(1,1),P(2,1),P(3,1),P(0,2),P(1,2),P(2,2),P(3,2),P(4,2),P(1,3),P(2,3),P(3,3)};
class Puzzle
{
public:
  VVI state;
  int Manhattan;
  VP vp;
  Puzzle():Manhattan(0){}
  Puzzle(VVI s)
  {
    vp.clear();
    state = s;
    Manhattan_calc(false);
  }
  void Manhattan_calc(bool b)
  {
    Manhattan = 0; 
    for(int i=0;i<5;i++)
      for(int j=0;j<state[i].size();j++)
	if(state[i][j] != 0 && state[i][j] != -1)
	  Manhattan += abs(j-Fpos[state[i][j]].F) + abs(i-Fpos[state[i][j]].S);
	else if(state[i][j] == 0 && !b)
	  vp.push_back(P(j,i)); 
  }
  void print()
  {
    for(int i=0;i<state.size();i++)
      {
	for(int j=0;j<state[i].size();j++)
	  {
	    if(state[i][j] == -1)
	      cout << "  ";
	    else 
	      cout << state[i][j] << " ";
	  }
	cout << endl;
      }
    cout << endl;
  }
};
bool Input(VVI& puzzle)
{
  puzzle.clear();
  puzzle.resize(5);
  puzzle[0].resize(3),puzzle[1].resize(4),puzzle[2].resize(5),puzzle[3].resize(4),puzzle[4].resize(3);
  puzzle[0][0] = puzzle[0][1] = puzzle[1][0] = puzzle[3][0] = puzzle[4][0] = puzzle[4][1] = -1;
  scanf("%d",&puzzle[0][2]);
  if(puzzle[0][2] == -1)
    return false; 
  scanf("%d %d %d",&puzzle[1][1],&puzzle[1][2],&puzzle[1][3]);
  scanf("%d %d %d %d %d",&puzzle[2][0],&puzzle[2][1],&puzzle[2][2],&puzzle[2][3],&puzzle[2][4]);
  scanf("%d %d %d",&puzzle[3][1],&puzzle[3][2],&puzzle[3][3]);
  scanf("%d",&puzzle[4][2]);
    return true;
}
void print(VVI vvi)
{
  cout << "--- print ---" << endl;
  for(int i=0;i<vvi.size();i++)
    {
      for(int j=0;j<vvi[i].size();j++)
	{
	  cout << vvi[i][j] << " ";
	}
      cout << endl;
    }
  cout << endl;
}
VVI change(VVI vec,P p1,P p11)
{
  int tmp = vec[p1.S][p1.F];
  vec[p1.S][p1.F] = vec[p11.S][p11.F];
  vec[p11.S][p11.F] = tmp;
  return vec;
}
void Init()
{
  final.resize(5);
  final[0].pb(-1),final[0].pb(-1),final[0].pb(0);
  final[1].pb(-1),final[1].pb(1),final[1].pb(2),final[1].pb(3);
  final[2].pb(4),final[2].pb(5),final[2].pb(6),final[2].pb(7),final[2].pb(8);
  final[3].pb(-1),final[3].pb(9),final[3].pb(10),final[3].pb(11);
  final[4].pb(-1),final[4].pb(-1),final[4].pb(0);
  Puzzle puz(final); 
  deque<Puzzle> deq;
  deq.push_back(puz);
  bidirectional[final] = 0;
  while(!deq.empty())
    {
      Puzzle p = deq.front(); deq.pop_front();
      int cost = bidirectional[p.state];
      if(cost >= 8)
	continue;
      for(int i=0;i<2;i++)
	{
	  for(int j=0;j<4;j++)
	    {
	      int nx = p.vp[i].F + dx[j];
	      int ny = p.vp[i].S + dy[j];
	      if(!(0<=ny && ny<p.state.size() && 0<=nx && nx<p.state[ny].size() && p.state[ny][nx] != -1))
		continue;
	      VVI next = change(p.state,p.vp[i],P(nx,ny));
	      map<VVI,int>::iterator it = bidirectional.find(next);
	      if(it == bidirectional.end() || (it != bidirectional.end() && bidirectional[next] > cost + 1))
		{
		  bidirectional[next] = cost + 1;
		  deq.push_back(Puzzle(next));
		}
	    }
	}      
    }
}
int main()
{
  VVI puzzle;
  Init();
  while(Input(puzzle))
    {
      Puzzle puz(puzzle);
      int men = (1<<28);
      deque<Puzzle> deq;
      deq.push_back(puz);
      memo.clear();
      memo[puzzle] = 0;
      while(!deq.empty())
	{
	  Puzzle p = deq.front(); deq.pop_front();
	  int cost = memo[p.state];
	  if(cost + p.Manhattan > min(20,men))
	    continue;
	  if(p.state == final)
	    {
	      men = min(men,cost);
	      continue;
	    }
	  else if(bidirectional.find(p.state) != bidirectional.end() && cost + bidirectional[p.state] <= 20)
	    {
	      men = min(men,cost+bidirectional[p.state]);
	      continue;
	    }
	  for(int i=0;i<2;i++)
	    {
	      for(int j=0;j<4;j++)
		{
		  int nx = p.vp[i].F + dx[j];
		  int ny = p.vp[i].S + dy[j];
		  if(!(0<=ny && ny<p.state.size() && 0<=nx && nx<p.state[ny].size() && p.state[ny][nx] != -1))
		    continue;
		  VVI next = change(p.state,p.vp[i],P(nx,ny));
		  map<VVI,int>::iterator it = memo.find(next);
		  if(it == memo.end() || (it != memo.end() &&  memo[next] > cost + 1) )
		    {
		      memo[next] = cost + 1;
		      deq.push_back(Puzzle(next));
		    }
		}
	    }
	}
      if(men == (1<<28))
	cout << "NA" << endl;
      else 
	cout << men << endl;
    }  
  return 0;
}
