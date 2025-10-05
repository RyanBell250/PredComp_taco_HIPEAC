#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
#define REP(i,b,n) for(int i=b;i<n;i++)
#define rep(i,n)   REP(i,0,n)
#define ALL(C)     (C).begin(),(C).end()
#define pb         push_back
#define mp         make_pair
#define RANK       first
#define NUM        second
typedef long long ll;
typedef pair<int,int> pii;
class Team{
public:
  int rank;
  int num;
  int point,diff,goal;
  bool operator<(const Team &a)const{
    if (rank != a.rank)return rank < a.rank;
    if (point != a.point)return point > a.point;
    if (diff != a.diff)return diff > a.diff;
    if (goal != a.goal)return goal > a.goal;
    return false;
  }
  bool operator==(const Team & a)const{
    if (rank != a.rank )return false;
    if (point!= a.point)return false;
    if (diff != a.diff )return false;
    if (goal != a.goal )return false;
    return true;
  }
};
double ans;
void count_up(Team *in,int tar,double prob){
  double total=0,adv=0;
  int ind[4]={0};
  rep(i,4)ind[i]=i;
  do{
    int wheretar=100;
    bool isvalid=true;
    rep(i,3){
      if (in[ind[i]].rank > in[ind[i+1]].rank){
	isvalid=false;
	break;
      }
    }
    if(!isvalid)continue;
    rep(i,4)if (in[ind[i]].num==tar){wheretar=i;break;}
    if (wheretar < 2)adv+=1;
    total+=1;
  }while(next_permutation(ind,ind+4));
  ans+=prob*(adv/total);
}
int score[4][4]={0};
void make_rank(int tar,double prob){
  static Team in[4];
  rep(i,4){
    in[i].rank=0;
    in[i].num=i;
  }
  static Team cpy[4];
  rep(i,4){
    cpy[i].rank=-1;
    cpy[i].num=-1;
  }
  while(true){
    rep(i,4){
      in[i].point=0;
      in[i].diff=0;
      in[i].goal=0;
    }
    rep(i,4){
      rep(j,4){
	if (i == j)continue;
	if (in[i].rank != in[j].rank)continue;
	in[i].goal+=score[in[i].num][in[j].num];
	in[i].diff+=score[in[i].num][in[j].num]-score[in[j].num][in[i].num];
	if (score[in[i].num][in[j].num] > score[in[j].num][in[i].num])
	  in[i].point+=3;
	else if (score[in[i].num][in[j].num] == score[in[j].num][in[i].num])
	  in[i].point+=1;
      }
    }
    sort(in,in+4);
    for(int i=0;i<4;i++){
      int j=i+1;
      for(;j<4;j++){
	if (in[i] == in[j])in[j].rank=i;
	else break;
      }
      in[i].rank=i;
      i=j-1;
    }
    bool isend=true;
    rep(i,4){
      if (in[i].rank==cpy[i].rank&&in[i].num==cpy[i].num
	  &&in[i]==cpy[i]){
      }else isend=false;
      cpy[i]=in[i];
    }
    if (isend)break;
  }
  count_up(in,tar,prob);
}
double scoretable[9];
bool isdecided[4][4];
void solve(int now,double prob,int tar){
  if (now == 4){
    make_rank(tar,prob);
    return;
  }
  rep(i,4){
    if (isdecided[now][i])continue;
    rep(j,9){
      score[now][i]=j;
      solve(now+1,prob*scoretable[j],tar);
    }
    return;
  }
}
void make_table(){
  int fact[9];
  double qua[9];
  double qu3[9];
  fact[0]=1;
  REP(i,1,9)fact[i]=i*fact[i-1];
  qua[0]=1;
  REP(i,1,9)qua[i]=1/4.*qua[i-1];
  qu3[0]=1;
  REP(i,1,9)qu3[i]=3/4.*qu3[i-1];
  rep(i,9){
    scoretable[i]=fact[8]/((double)fact[i]*fact[8-i])*qua[i]*qu3[8-i];
  }
}
int getdata(){
  int tar;
  string in[5];
  rep(i,5)cin>>in[i];
  REP(i,1,5){
    if (in[i][0] == '*')tar=i-1;
  }
  if (in[1][11] != '_'){
    score[0][1]=in[1][11]-'0';
    score[1][0]=in[1][13]-'0';
    isdecided[0][1]=isdecided[1][0]=true;
  }
  if (in[1][16] != '_'){
    score[0][2]=in[1][16]-'0';
    score[2][0]=in[1][18]-'0';
    isdecided[0][2]=isdecided[2][0]=true;
  }
  if (in[1][21] != '_'){
    score[0][3]=in[1][21]-'0';
    score[3][0]=in[1][23]-'0';
    isdecided[0][3]=isdecided[3][0]=true;
  }
  if (in[2][16] != '_'){
    score[1][2]=in[2][16]-'0';
    score[2][1]=in[2][18]-'0';
    isdecided[1][2]=isdecided[2][1]=true;
  }
  if (in[2][21] != '_'){
    score[1][3]=in[2][21]-'0';
    score[3][1]=in[2][23]-'0';
    isdecided[1][3]=isdecided[3][1]=true;
  }
  if (in[3][21] != '_'){
    score[2][3]=in[3][21]-'0';
    score[3][2]=in[3][23]-'0';
    isdecided[2][3]=isdecided[3][2]=true;
  }
  return tar;
}
int main(){
  make_table();
  int te;
  cin>>te;
  while(te--){
    rep(i,4){
      rep(j,4){
	score[i][j]=-1;
	isdecided[i][j]=false;
      }
      score[i][i]=0;
      isdecided[i][i]=true;
    }
    int tar=getdata();
    ans=0;
    solve(0,1,tar);
    printf("%.7lf\n",ans);
  }
  return false;
}