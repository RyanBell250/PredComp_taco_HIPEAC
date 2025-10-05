#include <cstdio>
#include <set>
#include <queue>
#include <cstdlib>
using namespace std;
#define REP(i,n) for(int i=0; i<n; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define QCLR(q) while(!q.empty()) q.pop();
int dx[]={0,0,-1,1,-1,1};
int dy[]={-1,1,0,-1,1,0};
int N,K,rx[100],ry[100],gx,gy;
class Hex
{
public:
	int px[8], py[8];
	Hex(int tpx[8], int tpy[8])
	{
		REP(i,N) 
		{
			px[i]=tpx[i];
			py[i]=tpy[i];
		}
	}
	bool operator<(const Hex& h) const
	{
		REP(i,N)
		{
			if(px[i]!=h.px[i]) return px[i]<h.px[i];
			if(py[i]!=h.py[i]) return py[i]<h.py[i];
		}
		return false;
	}
};
class State
{
public:
	Hex h;
	int c;
	State(Hex h, int c)
	:h(h),c(c)
	{}
};
queue<State> q;
set<Hex> s;
int dist60(int x1, int y1, int x2, int y2)
{
	return (abs(x1-x2)+abs(y1-y2)+abs((x1+y1)-(x2+y2)))/2;
}
bool crash(Hex& h, int p)
{
	REP(i,K) if(h.px[p]==rx[i]&&h.py[p]==ry[i]) return true;
	return false;
}
bool connect(Hex& h, int j)
{
	REP(i,j)
	{
		if(h.px[i]==h.px[j]&&h.py[i]==h.py[j]) return false;
		int cnt=0;
		REP(k,6)
		{
			int tx=h.px[i]+dx[k], ty=h.py[i]+dy[k];
			if(h.px[j]==tx&&h.py[j]==ty) 
			{
				cnt++;
				break;
			}
		}
		if(j-i==1&&cnt!=1) return false;
		if(j-i!=1&&cnt==1) return false;
	}
	return true;
}
bool create(int p, Hex& h, int c, bool sk)
{
	if(p==N) 
	{
		int dist=dist60(gx,gy,h.px[0],h.py[0]);
		if(dist>1) dist=(dist-1)*2+1;
		if(dist > 20-c) return false;
		if(!s.count(h)) 
		{
			s.insert(h);
			q.push(State(h,c+1));
			return true;
		}
		return false;
	}
	int cnt=0;
	if(connect(h,p)) create(p+1,h,c,false);
	if(!sk)
	{
		REP(i,6)
		{	
			h.px[p]+=dx[i], h.py[p]+=dy[i];
			if(crash(h,p) || !connect(h,p))
			{
				h.px[p]-=dx[i], h.py[p]-=dy[i];
				continue;
			}
			if(create(p+1,h,c,true)) cnt++;
			h.px[p]-=dx[i], h.py[p]-=dy[i];
			if(p==0||p==N-1) { if(cnt==2) break; }
			else { if(cnt==1) break; }
		}
	}
	return false;
}
int bfs(int ix[8], int iy[8])
{
	q.push(State(Hex(ix,iy), 0));
	while(1)
	{
		State s=q.front(); q.pop();
		if(s.h.px[0]==gx&&s.h.py[0]==gy) return s.c;
		create(0,s.h,s.c,false);
	}
	return 0;
}
int main()
{
	while(scanf("%d", &N),N)
	{
		QCLR(q);
		s.clear();
		int px[8], py[8];
		REP(i,N) scanf("%d %d", &px[i], &py[i]);
		scanf("%d", &K);
		REP(i,K) scanf("%d %d", &rx[i], &ry[i]);
		scanf("%d%d", &gx,&gy);
		printf("%d\n", bfs(px,py));
	}
}
