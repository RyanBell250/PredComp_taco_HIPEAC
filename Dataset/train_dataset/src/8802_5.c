#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
vector<pair<int,int> >B[510][510];
int dx[]={1,1,1,0,0,0,-1,-1,-1};
int dy[]={1,0,-1,1,0,-1,1,0,-1};
int ax[110000];
int ay[110000];
int main(){
	int a,b,c;
	while(scanf("%d%d%d",&a,&b,&c),a+b){
		for(int i=0;i<510;i++)
			for(int j=0;j<510;j++){
				B[i][j].clear();
			}
		for(int i=0;i<a;i++){
			int x,y;scanf("%d%d",&x,&y);
			ax[i]=x;ay[i]=y;
		}
		for(int i=0;i<b;i++){
			int x,y;scanf("%d%d",&x,&y);
			B[x/40][y/40].push_back(make_pair(x,y));
		}
		int ret=0;
		for(int i=0;i<a;i++){
			int x=ax[i]/40;
			int y=ay[i]/40;
			for(int j=0;j<9;j++){
				int nx=x+dx[j];
				int ny=y+dy[j];
				if(nx<0||ny<0||nx>=250||ny>=250)continue;
				for(int k=0;k<B[nx][ny].size();k++){
					if((ax[i]-B[nx][ny][k].first)*(ax[i]-B[nx][ny][k].first)+
					(ay[i]-B[nx][ny][k].second)*(ay[i]-B[nx][ny][k].second)<=c*c*16)ret++;
				}
			}
		}
		printf("%d\n",ret);
	}
}