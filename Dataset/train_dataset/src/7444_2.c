#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
typedef long long ll;
const int MaxN=200010,mod=1000000007;
int N,X,Y,c[MaxN],w[MaxN],list[MaxN];
std::vector<int>V[MaxN];
int cur[MaxN];
bool cmp(int i,int j){return w[i]<w[j];}
struct item{
	int x;
	bool operator<(const item&it)const{
		int i=V[x][cur[x]],j=V[it.x][cur[it.x]];
		return w[i]!=w[j]?w[i]<w[j]:i<j;
	}
};
std::set<item>S;
int col[MaxN],len;
int top(int i){return cur[i]<V[i].size()?V[i][cur[i]]:-1;}
void dfs(int i){
	int t=col[len++]=c[i],to;
	S.erase((item){t});
	if(++cur[t]<V[t].size())S.insert((item){t});
	while(S.size()){
		if(top(t)>-1&&w[i]+w[to=top(t)]<=X)dfs(to);
		else{
			std::set<item>::iterator it=S.begin();
			if((to=it->x)==c[i])to=S.size()>1?(++it)->x:-1;
			if(to>-1&&w[i]+w[top(to)]<=Y)dfs(top(to));
			else return;
		}
	}
}
ll fac[MaxN],ifac[MaxN];
ll inv(int a,int p=mod){return a==1?1:(1+p*(a-inv(p%a,a)))/a%p;}
int main(){
	scanf("%d%d%d",&N,&X,&Y);
	for(int i=0;i<N;i++)scanf("%d%d",c+i,w+i),list[i]=i;
	std::sort(list,list+N,cmp);
	for(int*i=list;i<list+N;i++)V[c[*i]].push_back(*i);
	for(int i=1;i<=N;i++)if(top(i)>-1)S.insert((item){i});
	for(int i=*fac=1;i<=N;i++)fac[i]=fac[i-1]*i%mod;
	ifac[N]=inv(fac[N]);
	for(int i=N;i;i--)ifac[i-1]=ifac[i]*i%mod;
	int ans=1;
	while(S.size()){
		len=0;
		dfs(top(S.begin()->x));
		std::sort(col,col+len);
		ans=ans*fac[len]%mod;
		for(int i=0,j=0;i<len;i=j){
			while(j<len&&col[i]==col[j])j++;
			ans=ans*ifac[j-i]%mod;
		}
	}
	printf("%d\n",ans);
}