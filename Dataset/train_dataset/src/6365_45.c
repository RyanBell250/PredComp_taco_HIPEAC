 #include <bits/stdc++.h>
                                        #include<iostream>
                                        #include<cstdio>
                                        #include<vector>
                                        #include<queue>
                                        #include<map>
                                        #include<cstring>
                                        #include<string>
                                        #include <math.h>
                                        #include<algorithm>
                                        #include<functional>
                               #define int long long
                                        #define inf  1000000007
                                        #define pa pair<int,int>
                                        #define ll long long
                                        #define pal pair<double,pa>
                                        #define ppap pair<pa,int>
                                        #define ssa pair<string,int>
                                        #define  mp make_pair
                                        #define  pb push_back
                                        #define EPS (1e-10)
                                        #define equals(a,b) (fabs((a)-(b))<EPS)
int dx[4]={0,-1,0,1};
int dy[4]={1,0,-1,0};
                                        using namespace std;
                               			class pa3{
                                        	public:
                                        	int x,y,z;
                                        	pa3(int x=0,int y=0,int z=0):x(x),y(y),z(z) {}
                                        	bool operator < (const pa3 &p) const{
                                        		if(x!=p.x) return x<p.x;
                                        		if(y!=p.y) return y<p.y;
                                        		 return z<p.z;
                                        	}
                               				bool operator > (const pa3 &p) const{
                                        		if(x!=p.x) return x>p.x;
                                        		if(y!=p.y) return y>p.y;
                                        		 return z>p.z;
                                        	}
                                        	bool operator == (const pa3 &p) const{
                                        		return x==p.x && y==p.y && z==p.z;
                                        	}
                                        		bool operator != (const pa3 &p) const{
                                        			return !( x==p.x && y==p.y && z==p.z);
                                        	}
                                        };
                                        class pa4{
                                        	public:
                                        	double x;
                                        	int y,z,w;
                                        	pa4(double x=0,int y=0,int z=0,int w=0):x(x),y(y),z(z),w(w) {}
                                        	bool operator < (const pa4 &p) const{
                                        		if(x!=p.x) return x<p.x;
                                        		if(y!=p.y) return y<p.y;
                                        		if(z!=p.z)return z<p.z;
                                        		return w<p.w;
                                        	}
                                        	bool operator > (const pa4 &p) const{
                                        		if(x!=p.x) return x>p.x;
                                        		if(y!=p.y) return y>p.y;
                                        		if(z!=p.z)return z>p.z;
                                        		return w>p.w;
                                        	}
                                        	bool operator == (const pa4 &p) const{
                                        		return x==p.x && y==p.y && z==p.z &&w==p.w;
                                        	}
                                        };
                                        class pa2{
                                        	public:
                                        	int x,y;
                                        	pa2(int x=0,int y=0):x(x),y(y) {}
                                        	pa2 operator + (pa2 p) {return pa2(x+p.x,y+p.y);}
                                        	pa2 operator - (pa2 p) {return pa2(x-p.x,y-p.y);}
                                        	bool operator < (const pa2 &p) const{
                                        		return x != p.x ? x<p.x: y<p.y;
                                        	}
                                        	bool operator == (const pa2 &p) const{
                                        		return abs(x-p.x)==0 && abs(y-p.y)==0;
                                        	}
                                        	bool operator != (const pa2 &p) const{
                                        		return !(abs(x-p.x)==0 && abs(y-p.y)==0);
                                        	}
                                        };
                                               #define ppa pair<int,pas>
                                        class Point{
                                        	public:
                                        	double x,y;
                                        	Point(double x=0,double y=0):x(x),y(y) {}
                                        	Point operator + (Point p) {return Point(x+p.x,y+p.y);}
                                        	Point operator - (Point p) {return Point(x-p.x,y-p.y);}
                                        	Point operator * (double a) {return Point(x*a,y*a);}
                                        	Point operator / (double a) {return Point(x/a,y/a);}
                                        	double absv() {return sqrt(norm());}
                                        	double norm() {return x*x+y*y;}
                                        	bool operator < (const Point &p) const{
                                        		return x != p.x ? x<p.x: y<p.y;
                                        	}
                                        	bool operator == (const Point &p) const{
                                        		return fabs(x-p.x)<EPS && fabs(y-p.y)<EPS;
                                        	}
                                        };
                                        typedef Point Vector;
                                 #define pl pair<int,pas>
                                        struct Segment{
                                        Point p1,p2;
                                        };
                                         double dot(Vector a,Vector b){
                                        	return a.x*b.x+a.y*b.y;
                                        }
                                        double cross(Vector a,Vector b){
                                        	return a.x*b.y-a.y*b.x;
                                        }
            bool parareru(Point a,Point b,Point c,Point d){
            	return abs(cross(a-b,d-c))<EPS;
            }
            double distance_ls_p(Point a, Point b, Point c) {
              if ( dot(b-a, c-a) < EPS ) return (c-a).absv();
              if ( dot(a-b, c-b) < EPS ) return (c-b).absv();
              return abs(cross(b-a, c-a)) / (b-a).absv();
            }
            bool is_intersected_ls(Segment a,Segment b) {
            	if(a.p1==b.p1||a.p2==b.p1||a.p1==b.p2||a.p2==b.p2) return false;
            	if(parareru((a.p2),(a.p1),(a.p1),(b.p2))&&parareru((a.p2),(a.p1),(a.p1),(b.p1))){
            		if(dot(a.p1-b.p1,a.p1-b.p2)<EPS) return true;
            		if(dot(a.p2-b.p1,a.p2-b.p2)<EPS) return true;
            		if(dot(a.p1-b.p1,a.p2-b.p1)<EPS) return true;
            		if(dot(a.p1-b.p2,a.p2-b.p2)<EPS) return true;
            		return false;
            	}
              else return ( cross(a.p2-a.p1, b.p1-a.p1) * cross(a.p2-a.p1, b.p2-a.p1) < EPS ) && ( cross(b.p2-b.p1, a.p1-b.p1) * cross(b.p2-b.p1, a.p2-b.p1) < EPS );
            }
            double segment_dis(Segment a,Segment b){
            	if(is_intersected_ls(a,b))return 0;
            	double r=distance_ls_p(a.p1, a.p2, b.p1);
            	r=min(r,distance_ls_p(a.p1, a.p2, b.p2));
            	r=min(r,distance_ls_p(b.p1, b.p2, a.p2));
            	r=min(r,distance_ls_p(b.p1, b.p2, a.p1));
            	return r;
            }
            Point intersection_ls(Segment a, Segment b) {
              Point ba = b.p2-b.p1;
              double d1 = abs(cross(ba, a.p1-b.p1));
              double d2 = abs(cross(ba, a.p2-b.p1));
              double t = d1 / (d1 + d2);
              return a.p1 + (a.p2-a.p1) * t;
            }
                            string itos( int i ) {
                            ostringstream s ;
                            s << i ;
                            return s.str() ;
                            }
                            int gcd(int v,int b){
                            	if(v>b) return gcd(b,v);
                            	if(v==b) return b;
                            	if(b%v==0) return v;
                            	return gcd(v,b%v);
                            }
                            double distans(double x1,double y1,double x2,double y2){
                            	double rr=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
                            	return sqrt(rr);
                            }
            int beki(int wa,int rr,int warukazu){
            	if(rr==0) return 1ll;
            	if(rr==1) return wa%warukazu;
            	if(rr%2==1) return (beki(wa,rr-1,warukazu)*wa)%warukazu;
            	int zx=beki(wa,rr/2,warukazu);
            	return (zx*zx)%warukazu;
            }
int m,n;
string str[130];
map<string ,int>ma;
string emp="";
int dfs(string s){
	if(ma.find(s)!=ma.end()) return ma[s];
	int ans=inf;
	for(int i=0;i<m;i++){
		string emp1=emp;
		string emp2=emp;
		bool bo1=0,bo2=0;
		for(int j=0;j<n;j++)if(s[j]=='1'){
			if(str[j][i]=='0')emp1[j]='1',bo1=1;
			if(str[j][i]=='1')emp2[j]='1',bo2=1;
		}
		if(bo1==0 || bo2==0) continue;
		ans=min(ans,1+max(dfs(emp1),dfs(emp2)));
	}
	ma[s]=ans;
	return ans;
}
   signed main(){
   	while(1){
   	cin>>m>>n;
   		if(m==0) return 0;
   		for(int i=0;i<n;i++)	cin>>str[i];
   		if(n==1){
   			cout<<0<<endl;
   			continue;
   		}
   		ma.clear();
   		string s="",t="";
   		emp="";
   		for(int i=0;i<n;i++)emp+="0";
   		for(int i=0;i<n;i++)t+="0";
   		ma[t]=0;
   		for(int i=0;i<n;i++){
   			t[i]='1';
   			ma[t]=0;
   			t[i]='0';
   		}
   		for(int i=0;i<n;i++)s+="1";
   		cout<<dfs(s)<<endl;
   	}
   	return 0;
        }
