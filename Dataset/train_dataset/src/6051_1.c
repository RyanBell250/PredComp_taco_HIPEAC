#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<cstdio>
using namespace std;
const int MAX_N = 10;
int in[MAX_N][3];
int N;
vector<int>vec[10];
typedef pair<int,int>P;
const int INF = 1e8;
void input(){
  for(int i = 0 ; i < N ; i++){
    for(int j = 0 ; j < 3 ; j++){
      cin >> in[i][j];
    }
  }
}
int toTime(int h,int m,int s){
  return 3600*(h/5) + m*60 + s;
}
void printTime(int t){
  int h,m,s;
  h = t/3600;
  t %= 3600;
  m = t/60;
  t %= 60;
  s = t;
  printf("%02d:%02d:%02d",h,m,s);
}
void make(){
  int ind[3] = {0,1,2};
  for(int i = 0 ; i < N ; i++){
    do{
      for(int j = 0 ; j < 60 ; j++){
	int h,m,s;
	h = (in[i][ind[0]]+j)%60;
	m = (in[i][ind[1]]+j)%60;
	s = (in[i][ind[2]]+j)%60;	
	if(h/5*5 + m/12 != h)continue;
	vec[i].push_back(toTime(h,m,s));
      }
    }while(next_permutation(ind,ind+3));
    sort(vec[i].begin(),vec[i].end());
  }
}
void check(int s_id,int e_id,int s,int e,P& res){
  if(e < s)return;
  for(int i = 0 ; i < N ; i++){
    int id = lower_bound(vec[i].begin(),vec[i].end(),s) - vec[i].begin();
    if(id == vec[i].size())return;
    if(vec[i][id] > e)return;
  }
  res = min(res,P(e-s,s));
}
int main(){
  while(cin >> N,N){
    for(int i = 0 ; i < N ; i++)vec[i].clear();
    input();
    make();
    P res = P(INF,INF);
    for(int i = 0 ; i < N ; i++){
      for(int j = 0 ; j < N ; j++){
	if(i == j)continue;
	for(int ii = 0 ; ii < vec[i].size() ; ii++){
	  for(int jj = 0 ; jj < vec[j].size() ; jj++){
	    check(i,j,vec[i][ii],vec[j][jj],res);
	  }
	}
      }
    }
    printTime(res.second);
    cout << ' ';
    printTime(res.second + res.first);
    cout << endl;
  }
  return 0;
}