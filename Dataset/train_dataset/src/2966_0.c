#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
int dat[501][501];
int dx[]={0,0,1,1,-1,-1};
int dy[]={1,-1,-1,0,0,+1};
int bfs[501][501];
int main(){
	int a,b;
	scanf("%d%d",&b,&a);
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(j+1+a-(i+1)/2<0)printf("dededon\n");
			scanf("%d",&dat[i+1][j+1+a-(i+1)/2]);
		}
	}
	queue<pair<int,int> > Q;
	Q.push(make_pair(0,0));
	bfs[0][0]=1;
	while(Q.size()){
		int row=Q.front().first;
		int col=Q.front().second;
		Q.pop();
		for(int i=0;i<6;i++){
			if(0<=row+dx[i]&&row+dx[i]<=500&&0<=col+dy[i]&&col+dy[i]<=500&&!dat[row+dx[i]][col+dy[i]]&&!bfs[row+dx[i]][col+dy[i]]){
				bfs[row+dx[i]][col+dy[i]]=1;
				Q.push(make_pair(row+dx[i],col+dy[i]));
			}
		}
	}
	int ret=0;
	for(int i=1;i<500;i++){
		for(int j=1;j<500;j++){
			for(int k=0;k<6;k++){
				if(dat[i][j]&&bfs[i+dx[k]][j+dy[k]])ret++;
			}
		}
	}
	printf("%d\n",ret);
}
