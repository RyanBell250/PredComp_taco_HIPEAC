#include<stdio.h>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
char str[60][60];
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
int bfs[60][60];
int ijk[60][60][4];
int v[60][60][4];
int dis[2][2];
int a,b;
int calc(vector<pair<int,int> >st,vector<pair<int,int> >go,int xr,int xc){
	for(int l=0;l<2;l++){
		for(int j=0;j<a;j++)for(int k=0;k<b;k++)bfs[j][k]=99999999;
		bfs[st[l].first][st[l].second]=0;
		queue<pair<int,int> >Q;
		Q.push(make_pair(st[l].first,st[l].second));
		while(Q.size()){
			int row=Q.front().first;
			int col=Q.front().second;
			Q.pop();
			for(int j=0;j<4;j++){
				int tr=row+dx[j];int tc=col+dy[j];
				if(tr<0||tc<0||tr>=a||tc>=b)continue;
				if(str[tr][tc]=='*')continue;
				if(tr==xr&&tc==xc)continue;
				if(tr==xr+1&&tc==xc)continue;
				if(tr==xr&&tc==xc+1)continue;
				if(tr==xr+1&&tc==xc+1)continue;
				if(bfs[tr][tc]>bfs[row][col]+1){
					bfs[tr][tc]=bfs[row][col]+1;
					Q.push(make_pair(tr,tc));
				}
			}
		}
		dis[l][0]=bfs[go[0].first][go[0].second];
		dis[l][1]=bfs[go[1].first][go[1].second];
	}
	return min(dis[0][0]+dis[1][1],dis[0][1]+dis[1][0]);
}
int main(){
	while(scanf("%d%d",&a,&b),a){
		for(int i=0;i<a;i++)scanf("%s",str[i]);
		for(int i=0;i<a;i++)for(int j=0;j<b;j++)for(int k=0;k<4;k++){
			ijk[i][j][k]=999999999;
			v[i][j][k]=0;
		}
		int sr,sc;
		for(int i=0;i<a;i++)for(int j=0;j<b;j++){
			if(str[i][j]=='X'){
				sr=i;sc=j;
			}
		}
		sr--;sc--;
		priority_queue<pair<int,pair<pair<int,int>,int> > >Q;
		for(int i=0;i<4;i++){
			vector<pair<int,int> >st;
			for(int j=0;j<a;j++)for(int k=0;k<b;k++)if(str[j][k]=='.'){
				st.push_back(make_pair(j,k));
			}
			vector<pair<int,int> >go;
			if(i==0){go.push_back(make_pair(sr,sc+2));go.push_back(make_pair(sr+1,sc+2));}
			if(i==1){go.push_back(make_pair(sr+2,sc));go.push_back(make_pair(sr+2,sc+1));}
			if(i==2){go.push_back(make_pair(sr,sc-1));go.push_back(make_pair(sr+1,sc-1));}
			if(i==3){go.push_back(make_pair(sr-1,sc));go.push_back(make_pair(sr-1,sc+1));}
			int co=calc(st,go,sr,sc);
			if(co<99999999){
				ijk[sr][sc][i]=co;
				Q.push(make_pair(-co,make_pair(make_pair(sr,sc),i)));
			}
		}
		while(Q.size()){
			int cost=-Q.top().first;
			int row=Q.top().second.first.first;
			int col=Q.top().second.first.second;
			int dir=Q.top().second.second;
			Q.pop();
			if(v[row][col][dir])continue;
			v[row][col][dir]=1;
			vector<pair<int,int> >st;
			if(dir==0){st.push_back(make_pair(row,col+2));st.push_back(make_pair(row+1,col+2));}
			if(dir==1){st.push_back(make_pair(row+2,col));st.push_back(make_pair(row+2,col+1));}
			if(dir==2){st.push_back(make_pair(row,col-1));st.push_back(make_pair(row+1,col-1));}
			if(dir==3){st.push_back(make_pair(row-1,col));st.push_back(make_pair(row-1,col+1));}
			for(int i=0;i<4;i++){
				if(v[row][col][i])continue;
				vector<pair<int,int> >go;
				if(i==0){go.push_back(make_pair(row,col+2));go.push_back(make_pair(row+1,col+2));}
				if(i==1){go.push_back(make_pair(row+2,col));go.push_back(make_pair(row+2,col+1));}
				if(i==2){go.push_back(make_pair(row,col-1));go.push_back(make_pair(row+1,col-1));}
				if(i==3){go.push_back(make_pair(row-1,col));go.push_back(make_pair(row-1,col+1));}
				int co=calc(st,go,row,col);
				if(!v[row][col][i]&&ijk[row][col][i]>cost+co){
					ijk[row][col][i]=cost+co;
					Q.push(make_pair(-cost-co,make_pair(make_pair(row,col),i)));
				}
			}
			if(!v[row+dx[dir]][col+dy[dir]][dir^2]&&ijk[row+dx[dir]][col+dy[dir]][dir^2]>cost+1){
				ijk[row+dx[dir]][col+dy[dir]][dir^2]=cost+1;
				Q.push(make_pair(-cost-1,make_pair(make_pair(row+dx[dir],col+dy[dir]),dir^2)));
			}
		}
		int ret=999999999;
		for(int i=0;i<4;i++){
			ret=min(ret,ijk[0][0][i]);
		}
		if(ret>9999999)printf("-1\n");
		else printf("%d\n",ret);
	}
}
