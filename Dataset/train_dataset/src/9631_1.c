#include <bits/stdc++.h>
using namespace std;
namespace Computational_Geometry
{
	const long double eps=1e-10;
	struct Vector2
	{
		long double x,y;
		Vector2(long double X=0.0,long double Y=0.0):x(X),y(Y) {}
		Vector2 *read() {scanf("%Lf%Lf",&x,&y); return this;}
		void print() {printf("%.10Lf %.10Lf",x,y); return;}
		inline Vector2 operator - () const{return Vector2(-x,-y);}
		inline Vector2 operator + (const Vector2 &A) const{return Vector2(x+A.x,y+A.y);}
		inline Vector2 operator - (const Vector2 &A) const{return Vector2(x-A.x,y-A.y);}
		inline Vector2 operator * (const long double &k) const{return Vector2(x*k,y*k);}
		inline Vector2 operator / (const long double &k) const{return Vector2(x/k,y/k);}
		inline long double operator * (const Vector2 &A) const{return x*A.x+y*A.y;}
		inline long double operator ^ (const Vector2 &A) const{return x*A.y-y*A.x;}
		inline long double norm2() const{return x*x+y*y;}
		inline long double norm() const{return sqrtl(x*x+y*y);}
		inline bool operator < (const Vector2 &A) const{return (x<A.x-eps)||(x<=A.x+eps)&&(y<A.y-eps);}
		inline bool operator == (const Vector2 &A) const{return fabsl(x-A.x)<=eps&&fabsl(y-A.y)<=eps;}
		inline bool operator << (const Vector2 &A) const{return (y<-eps)^(A.y<-eps)?A.y<-eps:((*this^A)>eps)||((*this^A)>=-eps)&&(x>=-eps)&&(A.x<-eps);}
		inline Vector2 trans(long double a_11,long double a_12,long double a_21,long double a_22) const{return Vector2(x*a_11+y*a_12,x*a_21+y*a_22);}
	};
	#define Point Vector2
	
	Point Projection(Point P,Point L1,Point L2)
	{
		long double k1=(L2-L1)*(P-L1),k2=(L2-L1).norm2();
		return L1+((L2-L1)*(k1/k2));
	}
	
	Point Reflection(Point P,Point L1,Point L2)
	{
		long double k1=(L2-L1)*(P-L1),k2=(L2-L1).norm2();
		Point mid=L1+(L2-L1)*(k1/k2);
		return mid*2-P;
	}
	
/*
	COUNTER_CLOCKWISE 1
	CLOCKWISE 2
	ONLINE_BACK 3
	ONLINE_FRONT 4
	ON_SEGMENT 5
*/
	int Counter_Clockwise(Point S,Point T1,Point T2)
	{
		if(((T1-S)^(T2-S))>eps) return 1;
		else if(((T1-S)^(T2-S))<-eps) return 2;
		else if(((T1-S)*(T2-S))<-eps) return 3;
		else if(((T2-S).norm2()-(T1-S).norm2())>eps) return 4;
		else return 5;
	}
	int Counter_Clockwise_Bool(Point S,Point T1,Point T2)
	{
		if(((T1-S)^(T2-S))>eps) return 1;
		else if(((T1-S)^(T2-S))<-eps) return -1;
		else if(((T1-S)*(T2-S))<-eps) return -1;
		else if(((T2-S).norm2()-(T1-S).norm2())>eps) return 1;
		else return 0;
	}
	
	int Parallel(Point S1,Point T1,Point S2,Point T2)
	{
		return fabsl((T1-S1)^(T2-S2))<=eps;
	}
	int Orthogonal(Point S1,Point T1,Point S2,Point T2)
	{
		return fabsl((T1-S1)*(T2-S2))<=eps;
	}
/*
	PARALLEL 1
	ORTHOGONAL 2
	OTHER 3
*/
	int Parallel_Orthogonal(Point S1,Point T1,Point S2,Point T2)
	{
		if(Parallel(S1,T1,S2,T2)) return 1;
		else if(Orthogonal(S1,T1,S2,T2)) return 2;
		else return 3;
	}
	
	int Intersection(Point S1,Point T1,Point S2,Point T2)
	{
		return Counter_Clockwise_Bool(S1,T1,S2)*Counter_Clockwise_Bool(S1,T1,T2)<=0&&Counter_Clockwise_Bool(S2,T2,S1)*Counter_Clockwise_Bool(S2,T2,T1)<=0;
	}
	
	Point Crosspoint(Point S1,Point T1,Point S2,Point T2)
	{
		long double d1=fabsl((S1-S2)^(T2-S2)),d2=fabsl((T1-S2)^(T2-S2));
		return S1+(T1-S1)*(d1/(d1+d2));
	}
	
	long double DistanceLP(Point S,Point T,Point P)
	{
		return fabsl((P-S)^(T-S)/(T-S).norm());
	}
	long double DistanceSP(Point S,Point T,Point P)
	{
		if((P-S)*(T-S)<-eps) return (P-S).norm();
		else if((P-T)*(S-T)<-eps) return (P-T).norm();
		else return DistanceLP(S,T,P);
	}
	long double Distance(Point S1,Point T1,Point S2,Point T2)
	{
		if(Intersection(S1,T1,S2,T2)) return 0;
		else return min(min(DistanceSP(S1,T1,S2),DistanceSP(S1,T1,T2)),min(DistanceSP(S2,T2,S1),DistanceSP(S2,T2,T1)));
	}
	
	long double Area(Point *P,int N)
	{
		long double Ans=0;
		for(int i=1;i<=N;i++) Ans+=P[i]^P[i==N?1:i+1]/2;
		return Ans;
	}
	
	int Is_Convex(Point *P,int N)
	{
		P[N+1]=P[1],P[N+2]=P[2];
		for(int i=1;i<=N;i++)
			if(Counter_Clockwise(P[i],P[i+1],P[i+2])==2) return 0;
		return 1;
	}
};
using namespace Computational_Geometry;
Point p,p0,p1,s0,s1,t0,t1,p_[100009];
int q,n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) p_[i].read();
	printf("%d\n",Is_Convex(p_,n));
	return 0;
}
