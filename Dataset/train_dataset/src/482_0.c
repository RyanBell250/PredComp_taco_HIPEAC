#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
using namespace std;
#define reps(i,f,n) for(int i=f;i<int(n);i++)
#define rep(i,n) reps(i,0,n)
class Rule{
	public:
	vector<int> x;
	int y;
};
vector<int> A;
vector<int> B;
const int N = 26;
const int R = 60;
const int K = 10;
const int INF = 1000000000;
vector<Rule> rules;
bool input(){
	int n,m,r;
	cin>>n>>m>>r;
	if(n==0)return false;
	A = vector<int>(n);
	rep(i,n)cin>>A[i];
	B = vector<int>(m);
	rep(i,m)cin>>B[i];
	rules = vector<Rule>(r);
	rep(i,r){
		int m;
		cin>>m;
		rules[i].x = vector<int>(m);
		rep(j,m)cin>>rules[i].x[j];
		cin>>rules[i].y;
	}
	return true;
}
int tableA[N][N];
int tableB[N][N];
void printbit(int len, int state){
	reps(i,1,len+1){
		printf("%d",((state&(1<<i))>0));
	}
}
void printTable(vector<int>& vec, int table[N][N]){
	rep(i,vec.size()){
		rep(j,vec.size()){
			printbit(2, table[i][j]);
			printf(" ");
		}puts("");
	}puts("");
}
bool canConvert(int table[N][N], int st, int dist, Rule& rule, int c){
	bool dp[K][N]={false};
	rep(i,rule.x.size()){
		rep(j,dist+1){
			if(i==0)dp[i][j] = (table[st][(st+j)%c]&(1<<rule.x[i]))>0;
			else{
				rep(k,j){
					dp[i][j] |= dp[i-1][k] & ( (table[(st+k+1)%c][(st+j)%c]&(1<<rule.x[i]))>0 );
				}
			}
		}
	}
	return dp[rule.x.size()-1][dist];
}
int getTableVal(int table[N][N],int st, int dist,int c){
	int ret = 0;
	rep(i,rules.size()){
		if(canConvert(table, st, dist, rules[i], c)){
			ret |= (1<<rules[i].y);
		}
	}
	return ret;
}
void makeTable2(vector<int>& vec, int table[N][N]){
	int c = vec.size();
	rep(dist, c){
		rep(i,c){
			if(dist==0){
				table[i][i] = (1<<vec[i]);
			}else{
				table[i][(i+dist)%c] = getTableVal(table, i, dist, c);
			}
		}
	}
}
void makeTable(){
	makeTable2(A, tableA);
	makeTable2(B, tableB);
}
int solveDP2(int s,int t){
	int dp[N][N]={0};
	int n = A.size();
	int m = B.size();
	rep(i,n){
		rep(j,m){
			if(tableA[s][(s+i)%n]&tableB[t][(t+j)%m])dp[i][j]=1;
			rep(k,i){
				rep(p,j){
					if(dp[k][p]==0)continue;
					if(tableA[(s+k+1)%n][(s+i)%n]&tableB[(t+p+1)%m][(t+j)%m]){
						dp[i][j] = max(dp[i][j], dp[k][p]+1);
					}
				}
			}
		}
	}
	return dp[A.size()-1][B.size()-1];
}
int solveDP(){
	int ans = 0;
	rep(i,A.size()){
		rep(j,B.size()){
			ans = max(ans, solveDP2(i,j));
		}
	}
	if(ans==0)return -1;
	return ans;
}
int solve(){
	makeTable();
	return solveDP();
}
int main(){
	while(input()){
		printf("%d\n",solve());
	}
}
