#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include<cstdio>
#include<cstdlib>
#include<map>
#include<queue>
#include<set>

using namespace std;
typedef pair<int,int> PII;

int	card[40320];
vector<int> tmp(10);
queue<vector<int> > qu;

int perm2num(vector<int> perm){
	int num=0;
	for(int i=0;i<8;i++){
		num *= 8-i;
		num += perm[i];
		for(int j=i+1;j<8;j++) if(perm[j]>perm[i])perm[j]--;
	}
	return num;
}

void qu_push(int a){
		swap(tmp[tmp[8]],tmp[tmp[8]+a]);			
		tmp[9]++;
		tmp[8]+=a;
		int p2n=perm2num(tmp);
		if (card[p2n]==-1){
			qu.push(tmp);
			card[p2n] = tmp[9];
		}
		tmp[9]--;
		tmp[8]-=a;
		swap(tmp[tmp[8]],tmp[tmp[8]+a]);
}

void solve(){
	vector<int> bgn(10);
	for(int i=0;i<8;i++) bgn[i] = i;
	qu.push(bgn);
	while(!qu.empty()){
		tmp = qu.front();
		qu.pop();
		if(tmp[8]<4)qu_push(4);
		else qu_push(-4);
		if(tmp[8]%4>0)qu_push(-1);
		if(tmp[8]%4<3)qu_push(1);
	}
}

int main(){
	card[0] = 0;
	for(int i=1;i<40320;i++) card[i] = -1;
	solve();
	vector<int> perm(8);
	while(true){
		int i=0;
		for(;i<8;i++)if(!(scanf("%d",&perm[i])+1))break;
		if(i<8)break;
		printf("%d\n",card[perm2num(perm)]);
	}
  return 0;
}