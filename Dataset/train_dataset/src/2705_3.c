#include<iostream>
#include<cstdio>
#include<stack>

using namespace std;

#define WALL 0
#define FLOO 1
#define HITO 2
#define HWMAX 50
#define DMAX 10

struct point{
	int x,y;
};

int main(){

	int h,w,d,n;
	int x,y,s;
	int mize[HWMAX][HWMAX];
	int cnt[HWMAX][HWMAX]={0};
	int r[DMAX+2];
	int Dx,Dy;
	char cinp;
	stack<point> Dhito;
	point xy;
	point ptmp;
	int dy[]={0,0,1,-1};
	int dx[]={1,-1,0,0};
	bool yes=false,no=false;

	cin>>h>>w>>d>>n;

	for(int i=0;i<h;i++){
		getchar();
		for(int j=0;j<w;j++){
			cinp=getchar();
			if(cinp=='#') mize[i][j]=WALL;
			if(cinp=='.') mize[i][j]=FLOO;
			if(cinp=='D') mize[i][j]=HITO,Dy=i,Dx=j;
		}
	}

	xy.x=Dx,xy.y=Dy;
	Dhito.push(xy);
	while(!Dhito.empty()){
		xy=Dhito.top();
		Dhito.pop();
		mize[xy.y][xy.x]=HITO;
		for(int i=0;i<4;i++){
			if(xy.y+dy[i]>=0&&xy.y+dy[i]<h&&xy.x+dx[i]>=0&&xy.x+dx[i]<w){
				if(mize[xy.y+dy[i]][xy.x+dx[i]]==FLOO){
					mize[xy.y+dy[i]][xy.x+dx[i]]=HITO;
					ptmp.y=xy.y+dy[i],ptmp.x=xy.x+dx[i];
					Dhito.push(ptmp);
				}
			}
		}

	}

	for(int i=1;i<=d;i++){
		cin>>r[i];
	}
	r[0]=0;
	r[d+1]=55;

	for(int i=0;i<n;i++){
		cin>>x>>y>>s;
		for(int j=-r[s];j<=r[s];j++){
			for(int k=-r[s];k<=r[s];k++){
				if(y+j>=0&&y+j<h&&x+k>=0&&x+k<w){
					cnt[y+j][x+k]--;
				}
			}
		}
		for(int j=-r[s+1];j<=r[s+1];j++){
			for(int k=-r[s+1];k<=r[s+1];k++){
				if(y+j>=0&&y+j<h&&x+k>=0&&x+k<w){
					cnt[y+j][x+k]++;
				}
			}
		}
		if(s==0) cnt[y][x]++;
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(cnt[i][j]==n){
				if(mize[i][j]==HITO) yes=true;
				else if(mize[i][j]==FLOO) no=true;
			}
		}
	}

	if(yes&&no) cout<<"Unknown"<<endl;
	else if(yes) cout<<"Yes"<<endl;
	else if(no) cout<<"No"<<endl;
	else cout<<"Broken"<<endl;

	return 0;
}