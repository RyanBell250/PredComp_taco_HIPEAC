#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <complex>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <sstream>
using namespace std;
#define EPS (1e-10)
#define EQ(a,b) (abs((a) - (b)) < EPS)
#define EQV(a,b) (EQ((a).real(),(b).real()) && EQ((a).imag(),(b).imag()))
typedef complex<double> P;
typedef long long ll;
const double PI=4*atan(1.0);
const int MAX_SIZE = 10000;
double dot(P a, P b) {
  return (a.real() * b.real() + a.imag() * b.imag());
}
double cross(P a, P b) {
  return (a.real() * b.imag() - a.imag() * b.real());
}
double calcPolygonArea(vector<P> p){
  double sum=0;
  for(int i = 0; i < p.size(); i++)
    sum+=cross(p[i],p[(i+1)%(p.size())]);
  return sum/2;
}
P points[50];
int n,m;
double dp[41][41][41][41];
const double INF=1000000;
double calcMaxS(int idx,int left,int prvSelIdx,int firstIdx){
  if(!EQ(dp[idx][left][prvSelIdx][firstIdx],0))
    return dp[idx][left][prvSelIdx][firstIdx];
  double maxSum=-INF;
  bool ok=false;
  if(left==0){
    maxSum=(cross(points[prvSelIdx],points[firstIdx]));
    ok=true;
  }
  else if(idx==n){
    maxSum=INF;
    ok=true;
  }
  else{
    double res=calcMaxS(idx+1,left-1,idx,firstIdx);
    if(!EQ(res,INF)){
      maxSum=max(maxSum,res+(cross(points[prvSelIdx],points[idx])));
      ok=true;
    }
    double res2=calcMaxS(idx+1,left,prvSelIdx,firstIdx);
    if(!EQ(res2,INF)){
      maxSum=max(maxSum,res2);
      ok=true;
    }
  }
  if(!ok)maxSum=INF;
  return dp[idx][left][prvSelIdx][firstIdx]=maxSum;
}
int main(){
  while(cin>>n>>m&&!(n==0&&m==0)){
    double maxS=0;
    memset(dp,0,sizeof(dp));
    vector<double>tmp;
    for(int i = 0; i < n; i++){
      double p;
      cin>>p;
      tmp.push_back(p);
    }
    sort(tmp.begin(),tmp.end());
    for(int i = 0; i < n; i++)
      points[i]=P(cos(tmp[i]*2*PI),sin(tmp[i]*2*PI));
    for(int i = 0; i < n-m+1; i++){
      double res=abs(calcMaxS(i+1,m-1,i,i));
      if(!EQ(res,INF))
	maxS=max(maxS,res/2);
    }
    printf("%.6f\n",maxS);
  }
  return 0;
}