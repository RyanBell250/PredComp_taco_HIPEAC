#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
typedef double Real;
typedef vector<int> Vector;
const Real inf=1e12;
const Real eps=1e-9;
template<class T> bool eq(T a, T b){
	return abs(a-b)<eps;
}
template<class T> int sgn(T a){
	if(eq(a,0.0)) return 0;
	if(a>0) return 1;
	return -1;
}
Vector crP(Vector v1,Vector v2){
	Vector res;
	for(int i=0;i<3;i++){
		Real val=0;
		val+=v1[(i+1)%3]*v2[(i+2)%3];
		val-=v1[(i+2)%3]*v2[(i+1)%3];
		res.push_back(val);
	}
	return res;
}
Vector subt(Vector v1,Vector v2){
	Vector res;
	for(int i=0;i<3;i++){
		res.push_back(v1[i]-v2[i]);
	}
	return res;
}
struct Prod:Vector{
	int val;
	Prod(){}
	Prod(Vector v):Vector(v){}
};
bool operator<(const Prod &p1,const Prod &p2){
	return p1.val<p2.val;
}
Prod prods[55];
int N,K;
int A,B,C;
vector<Vector> all;
void solve(vector<Prod> prods,int K){
	if(K==0){
		vector<int> vec;
		for(int i=0;i<3;i++) vec.push_back(0);
		all.push_back(vec);
		return;
	}
	for(int i=0;i<prods.size();i++){
		for(int j=0;j<prods.size();j++) for(int k=0;k<prods.size();k++){
			if(i==j||j==k||k==i) continue;
			Vector v1=subt(prods[j],prods[i]);
			Vector v2=subt(prods[k],prods[i]);
			Vector n=crP(v1,v2);
			Prod tmp[55];
			for(int l=0;l<prods.size();l++){
				tmp[l]=prods[l];
				tmp[l].val=0;
				for(int x=0;x<3;x++) tmp[l].val+=prods[l][x]*n[x];
			}
			bool out=false;
			if(i==0&&j==1&&k==2) out=true;
			sort(tmp,tmp+prods.size());
			int sum[3]={};
			for(int l=0;l<K;l++){
				for(int x=0;x<3;x++){
					sum[x]+=tmp[l][x];
				}
			}
			all.push_back(Vector(sum,sum+3));
		}
	}
	Prod tmp[55];
	for(int i=0;i<prods.size();i++){
		for(int l=0;l<prods.size();l++){
			tmp[l]=prods[l];
			tmp[l].val=0;
			for(int x=0;x<3;x++) tmp[l].val+=prods[l][x];
		}
		sort(tmp,tmp+prods.size());
		int sum[3]={};
		for(int l=0;l<K;l++){
			for(int x=0;x<3;x++){
				sum[x]+=tmp[l][x];
			}
		}
		all.push_back(Vector(sum,sum+3));
	}
}
int main(){
	scanf("%d%d",&N,&K);
	if(N==K){
		printf("0\n");
		return 0;
	}
	scanf("%d%d%d",&A,&B,&C);
	for(int i=0;i<N;i++){
		int x[3];
		for(int j=0;j<3;j++){
			scanf("%d",x+j);
		}
		Vector v=Vector(x,x+3);
		prods[i]=v;
	}
	vector<Prod> prods1=vector<Prod>(prods+1,prods+N);
	solve(prods1,K);
	long long e=-1;
	for(int i=0;i<all.size();i++){
		long long cur=1;
		for(int j=0;j<3;j++) cur*=all[i][j];
		if(e<0||e>cur){
			e=cur;
		}
	}
	all.clear();
	solve(prods1,K-1);
	Real ans=-1;
	for(int i=0;i<all.size();i++){
		int a[3];
		for(int j=0;j<3;j++) a[j]=all[i][j];
		for(int s=0;s<3;s++) for(int t=0;t<3;t++) for(int u=0;u<3;u++){
			int cnt=0;
			if(s==2) cnt++;
			if(t==2) cnt++;
			if(u==2) cnt++;
			if(cnt!=1) continue;
			Real val=0;
			Real x=prods[0][0];
			Real y=prods[0][1];
			Real z=prods[0][2];
			Real nochange=(x+a[0])*(y+a[1])*(z+a[2]);
			if(sgn(nochange-e)<=0){
				printf("0\n");
				return 0;
			}
			if(s==0){
				val+=A;
				x=0;
			}
			if(t==0){
				val+=B;
				y=0;
			}
			if(u==0){
				val+=C;
				z=0;
			}
			if(s==2){
				Real tmp=e/(y+a[1])/(z+a[2]);
				tmp-=a[0];
				if(sgn(tmp)<0||sgn(tmp-x)>0) val+=inf;
				else val+=(Real)A*(x-tmp)/x;
			}else if(t==2){
				Real tmp=e/(z+a[2])/(x+a[0]);
				tmp-=a[1];
				if(sgn(tmp)<0||sgn(tmp-y)>0) val+=inf;
				else val+=(Real)B*(y-tmp)/y;
			}else{
				Real tmp=e/(x+a[0])/(y+a[1]);
				tmp-=a[2];
				if(sgn(tmp)<0||sgn(tmp-z)>0) val+=inf;
				else val+=(Real)C*(z-tmp)/z;
			}
			if(val<inf/2){
				if(ans<0||ans>val) ans=val;
			}
		}
	}
	printf("%.9f\n",ans);
	return 0;
}