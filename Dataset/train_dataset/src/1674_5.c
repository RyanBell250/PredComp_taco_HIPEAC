#include<stdio.h>
#include<string.h>
#include<queue>
struct S{int x,y,c,a;S(int x,int y,int c,int a):x(x),y(y),c(c),a(a){}bool operator<(const S&s)const{return c>s.c;}};
int main()
{
	char m[66][36];	
	int d[66][36][2],h,w,x,y,z,a,i;
	int dx[]={1,1,1,1,1,2,2,2,3};
	int dy[]={2,1,0,-1,-2,1,0,-1,0};
	while(scanf("%d%d",&w,&h),w)
	{
		a=-1;
		memset(m,'X',sizeof(m));
		memset(d,127,sizeof(d));
		std::priority_queue<S>q;
		for(y=3;y<h+3;++y)
			for(x=3;x<w+3;++x)
			{
				scanf(" %c",&m[y][x]);
				if(m[y][x]=='S')
				{
					q.push(S(x,y,0,0));
					q.push(S(x,y,0,1));
					m[y][x]='0';
				}
			}
		while(!q.empty())
		{
			S p(q.top());q.pop();
			if(m[p.y][p.x]=='X')continue;
			if(m[p.y][p.x]=='T'){a=p.c;break;}
			p.c+=m[p.y][p.x]-'0';
			if(d[p.y][p.x][p.a]<=p.c)continue;
			d[p.y][p.x][p.a]=p.c;
			z=p.a*2-1;
			for(i=0;i<9;++i)
			{
				x=p.x+z*dx[i];
				y=p.y+dy[i];
				q.push(S(x,y,p.c,!p.a));
			}
		}
		printf("%d\n",a);
	}
	return 0;
}