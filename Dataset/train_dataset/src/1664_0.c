#include <bits/stdc++.h>
using namespace std;
int N;
vector<vector<int>> graph(222222);
vector<int> color(222222,-1);
vector<int> ans(222222,0);
void DFS(int f,int t){
	if(f==-1)color[t]=0;
	for(auto x:graph[t]){
		if(color[x]==-1){
			color[x]=(color[t]+1)%2;
			DFS(t,x);
		}
	}
}
int main(){
	cin >> N;
	for(int i=0;i<N-1;i++){
		int a,b;
		cin >> a >> b;
		a--;
		b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	DFS(-1,0);
	int c=accumulate(color.begin(),color.begin()+N,0);
	if(c<=N/3){
		int used3=0;
		int used12=0;
		for(int i=0;i<N;i++){
			if(color[i]==1)ans[i]=3*(++used3);
		}
		for(int i=0;i<N;i++){
			if(ans[i]==0){
				if(used3<N/3)ans[i]=3*(++used3);
				else{
					ans[i]=3*(used12/2)+((used12)%2)+1;
					used12++;
				}
			}
		}
	}else if((N-c)<=N/3){
		int used3=0;
		int used12=0;
		for(int i=0;i<N;i++){
			if(color[i]==0)ans[i]=3*(++used3);
		}
		for(int i=0;i<N;i++){
			if(ans[i]==0){
				if(used3<N/3)ans[i]=3*(++used3);
				else{
					ans[i]=3*(used12/2)+((used12)%2)+1;
					used12++;
				}
			}
		}
	}else{
		int used1=0;
		int used2=0;
		int used3=0;
		for(int i=0;i<N;i++){
			if(color[i]==0 && used1<(N+2)/3)ans[i]=1+3*(used1++);
			else if(color[i]==1 && used2<(N+1)/3)ans[i]=2+3*(used2++);
			else ans[i]=3*(++used3);
		}
	}
	for(int i=0;i<N;i++)printf("%d%c",ans[i],((i<N-1)?(' '):('\n')));
	return 0;
}
