#include<stdio.h>
#include<queue>
#include<algorithm>
using namespace std;
int zy[1000];
int zx[1000];
int x1[100];
int y1[100];
int x2[100];
int y2[100];
int t[300][300];
int y[300][300];
int v[300][300];
void bfs(int a,int b){
	queue<pair<int,int> >Q;
	v[a][b]=1;
	Q.push(make_pair(a,b));
	while(Q.size()){
		int row=Q.front().first;
		int col=Q.front().second;
		Q.pop();
		if(row<299&&!y[row][col]&&!v[row+1][col]){
			v[row+1][col]=1;
			Q.push(make_pair(row+1,col));
		}
		if(col<299&&!t[row][col]&&!v[row][col+1]){
			v[row][col+1]=1;
			Q.push(make_pair(row,col+1));
		}
		if(row&&!y[row-1][col]&&!v[row-1][col]){
			v[row-1][col]=1;
			Q.push(make_pair(row-1,col));
		}
		if(col&&!t[row][col-1]&&!v[row][col-1]){
			v[row][col-1]=1;
			Q.push(make_pair(row,col-1));
		}
	}
}
int main(){
	int a;
	while(scanf("%d",&a),a){
		for(int i=0;i<a;i++){
			scanf("%d%d%d%d",x1+i,y2+i,x2+i,y1+i);
			zx[i*2]=x1[i];
			zx[i*2+1]=x2[i];
			zy[i*2]=y1[i];
			zy[i*2+1]=y2[i];
		}
		std::sort(zx,zx+a*2);
		std::sort(zy,zy+a*2);
		for(int i=0;i<300;i++)for(int j=0;j<300;j++)t[i][j]=y[i][j]=v[i][j]=0;
		for(int i=0;i<a;i++){
			x1[i]=lower_bound(zx,zx+a*2,x1[i])-zx;
			x2[i]=lower_bound(zx,zx+a*2,x2[i])-zx;
			y1[i]=lower_bound(zy,zy+a*2,y1[i])-zy;
			y2[i]=lower_bound(zy,zy+a*2,y2[i])-zy;
			for(int j=x1[i]+1;j<=x2[i];j++){
				y[y1[i]][j]=y[y2[i]][j]=1;
			}
			for(int j=y1[i]+1;j<=y2[i];j++){
				t[j][x1[i]]=t[j][x2[i]]=1;
			}
		}
		int ret=0;
		for(int i=0;i<300;i++)for(int j=0;j<300;j++){
			if(!v[i][j]){
				ret++;
				bfs(i,j);
			}
		}
		printf("%d\n",ret);
	}
}