    #include <bits/stdc++.h>

                                            //    #include <boost/multiprecision/cpp_int.hpp>
 
                               	       #define int long long
                                                #define inf  1000000007
                                              #define pa pair<int,int>
                                               #define pad pair<double,double>
                                                #define ll long long
                                                #define pal pair<double,double>
                                                #define ppap pair<pa,int>
                                          #define PI 3.14159265358979323846
                                                #define paa pair<pa,pa>
                                                #define  mp make_pair
                                                #define  pb push_back
                                                #define EPS (1e-10)
                                                #define equals(a,b) (fabs((a)-(b))<EPS)
                                            //    #define double long double
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
                                                		//return x != p.x ? x<p.x: y<p.y;
                                                	}
                                       				bool operator > (const pa3 &p) const{
                                                		if(x!=p.x) return x>p.x;
                                                		if(y!=p.y) return y>p.y;
                                                		 return z>p.z;
                                                		//return x != p.x ? x<p.x: y<p.y;
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
                                                	int x;
                                                	int y,z,w;
                                                	pa4(int x=0,int y=0,int z=0,int w=0):x(x),y(y),z(z),w(w) {}
                                                	bool operator < (const pa4 &p) const{
                                                		if(x!=p.x) return x<p.x;
                                                		if(y!=p.y) return y<p.y;
                                                		if(z!=p.z)return z<p.z;
                                                		return w<p.w;
                                                		//return x != p.x ? x<p.x: y<p.y;
                                                	}
                                                	bool operator > (const pa4 &p) const{
                                                		if(x!=p.x) return x>p.x;
                                                		if(y!=p.y) return y>p.y;
                                                		if(z!=p.z)return z>p.z;
                                                		return w>p.w;
                                                		//return x != p.x ? x<p.x: y<p.y;
                                                	}
                                                	bool operator == (const pa4 &p) const{
                                                		return x==p.x && y==p.y && z==p.z &&w==p.w;
                                                	}
                                                	
                                                	bool operator != (const pa4 &p) const{
                                                		return !(x==p.x && y==p.y && z==p.z &&w==p.w);
                                                	}
                                                		
                                                
                                                };
                                                class pa2{
                                                	public:
                                                	int x,y;
                                                	pa2(int x=0,int y=0):x(x),y(y) {}
                                                	pa2 operator + (pa2 p) {return pa2(x+p.x,y+p.y);}
                                                	pa2 operator - (pa2 p) {return pa2(x-p.x,y-p.y);}
                                                	bool operator < (const pa2 &p) const{
                                                		return x!= p.x ? x<p.x: y<p.y;
                                                	}
                                                	bool operator > (const pa2 &p) const{
                                                		return x != p.x ? x>p.x: y>p.y;
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
                    //	if(abs(cross(a-b,d-c))<EPS)cout<<"dd "<<cross(a-b,d-c)<<endl;
                    	return abs(cross(a-b,d-c))<EPS;
                    }
                    double distance_ls_p(Point a, Point b, Point c) {
                      if ( dot(b-a, c-a) < EPS ) return (c-a).absv();
                      if ( dot(a-b, c-b) < EPS ) return (c-b).absv();
                      return abs(cross(b-a, c-a)) / (b-a).absv();
                    }
                    bool is_intersected_ls(Segment a,Segment b) {
                    	if(a.p1==b.p1||a.p2==b.p1||a.p1==b.p2||a.p2==b.p2) return 1;
                    	if(parareru((a.p2),(a.p1),(a.p1),(b.p2))&&parareru((a.p2),(a.p1),(a.p1),(b.p1))){
                    //		cout<<"sss"<<endl;
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
                                    	if(v==0) return b;
                                    	if(v>b) return gcd(b,v);
                                    	if(v==b) return b;
                                    	if(b%v==0) return v;
                                    	return gcd(v,b%v);
                                    }
                     
                                    double distans(double x1,double y1,double x2,double y2){
                                    	double rr=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
                                    	return sqrt(rr);
                                    	
                                    }
                                                        /*
        double bekid(double w,int r){
        	if(r==0) return 1.0;
        	if(r==1) return w;
        	if(r%2) return bekid(w,r-1)*w;
        	double f=bekid(w,r/2);
        	return f*f;
        }*/
                                    int mod;
                    int beki(int wa,int rr,int warukazu){
                    	if(rr==0) return 1%warukazu;
                    	if(rr==1) return wa%warukazu;
                    	if(rr%2==1) return (beki(wa,rr-1,warukazu)*wa)%warukazu;
                    	int zx=beki(wa,rr/2,warukazu);
                    	return (zx*zx)%warukazu;
                    }
                          /*          
                    int pr[401000];
                    int inv[401000];
                   
                   

                  
        			int comb(int nn,int rr){
        				int r=pr[nn]*inv[rr];
        				r%=mod;
        				r*=inv[nn-rr];
        				r%=mod;
        				
        				return r;
        			}
                  
                    void gya(int ert){
                    	pr[0]=1;
                    	for(int i=1;i<ert;i++){
                    		pr[i]=(pr[i-1]*i)%mod;
                    	}
                    	for(int i=0;i<ert;i++) inv[i]=beki(pr[i],mod-2,mod);
                    	
                    }
                    */
                    
                  //   cin.tie(0);
        		//	ios::sync_with_stdio(false);
        			//priority_queue<pa3,vector<pa3>,greater<pa3>> pq;            
                     //sort(ve.begin(),ve.end(),greater<int>());



struct segsum{
	//       1
	//   2        3
	// 4   5   6    7
	
	
	private:
	public:
	
	// 1<<10 = 1024
	// 1<<11 = 2048
	// 1<<12 = 4096
	// 1<<13 = 8192
	// 1<<14 = 16384
	// 1<<15 = 32768
	// 1<<16 = 65536
	// 1<<17 = 131072
	// 1<<18 = 262144
	
	int cor=(1<<17);
	
	vector<int> vec;
	vector<int> lazy;
	
	void shoki1(){
		vec.resize(2*cor+3, 0);
	}
		void shoki2(){
			for(int i=cor-1;i>0;i--) vec[i]=vec[2*i]+vec[2*i+1];
		}
			void clear(){
		    
	    	for(int i=0;i<(int)vec.size();i++)vec[i]=0;
    	}
	void updadd(int x,int w){
		//x 項目に w加算
		x+=cor;
		vec[x]+=w;
		while(1){
			x/=2;
			if(x==0) break;
			vec[x]=vec[2*x]+vec[2*x+1];
		}
		
	}
	
	void updchan(int x,int w){
		//x項目をwに変更
		x+=cor;
		vec[x]=w;
		while(1){
			x/=2;
			if(x==0) break;
			vec[x]=vec[2*x]+vec[2*x+1];
		}
		
	}
	// [a,b)
	// k-th node
	// k no kukanha [l,r)
	int sum(int a,int b,int k=1,int l=0,int r=-10){
		if(r<0)r=cor;
		
	//	cout<<a<<" "<<b<<" "<<k<<" "<<l<<" "<<r<<endl;
		
		if(a<=l && r<=b){
			return vec[k];
		}
		if(r<=a || b<=l){
			return 0;
		}
		
		int v1=sum(a,b,k*2,l,(l+r)/2),v2=sum(a,b,k*2+1,(l+r)/2,r);
		return v1+v2;
	}
	
};
segsum ss;

int high1[100020];
int high2[100020];
vector<pair<string,int>> ve1,ve2;
int a[100020];
int ans[100020]={0};
int aa[100020];
vector<pa3> ve[100020];
int gya[100020];
  signed main(){
 	              cin.tie(0);
   		ios::sync_with_stdio(false);
int n,q;
  	cin>>n>>q;
  	ss.shoki1();
  	ss.shoki2();
  	ve1.pb(mp("A",0));
  	ve2.pb(mp("A",0));
  	for(int i=0;i<n;i++){
  		string s;
  		cin>>s;
  		ve1.pb(mp(s,i));
  		reverse(s.begin(),s.end());
  		ve2.pb(mp(s,i));
  	}
  	sort(ve1.begin(),ve1.end());
  	
  	sort(ve2.begin(),ve2.end());
  	
  	for(int i=1;i<=n;i++)high1[ve1[i].second]=i;
  	for(int i=1;i<=n;i++)high2[ve2[i].second]=i;
  	for(int i=0;i<n;i++){
  		a[high1[i]]=high2[i];
  	}
  	a[0]=0;
  	aa[0]=0;
  	
  
  	for(int i=0;i<n;i++){
  		aa[high1[i]]=high2[i];
  	}
  	for(int i=0;i<=n;i++)gya[aa[i]]=i;
  //		for(int i=0;i<=n;i++)cout<<i<<"  "<<aa[i]<<endl;
  	for(int ii=0;ii<q;ii++){
  		string p,s;
  		cin>>p>>s;
  		reverse(s.begin(),s.end());
  		pair<string ,int> t1=mp(p,-100);
  		int x1=lower_bound(ve1.begin(),ve1.end(),t1)-ve1.begin();
  		t1.first+="~";
  		int x2=lower_bound(ve1.begin(),ve1.end(),t1)-ve1.begin();
 		
  		t1=mp(s,-100);
  		int y1=lower_bound(ve2.begin(),ve2.end(),t1)-ve2.begin();
  		t1.first+="~";
  		int y2=lower_bound(ve2.begin(),ve2.end(),t1)-ve2.begin();
 		
  	//	cout<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<endl;
  		if(x1==x2 || y1==y2 ) continue;
  		x1--;
  		x2--;
  		y1--;
  		y2--;
  		
  			ve[y1].pb((pa3){x1,ii,1});
  			ve[y1].pb((pa3){x2,ii,-1});  		
  			ve[y2].pb((pa3){x1,ii,-1});
  			ve[y2].pb((pa3){x2,ii,1});
  		
  	}
  	
  	for(int i=0;i<=n;i++){
  		ss.updadd(gya[i],1);
  	//	for(int j=0;j<=n;j++)cout<<ss.vec[ss.cor+j]<<" ";
  	//	cout<<endl;
  		for(auto v:ve[i]){
  			ans[v.y]+=v.z*(ss.sum(0,v.x+1));
  		}
  	}
  	
  	for(int i=0;i<q;i++)cout<<ans[i]<<endl;

  	return 0;
  	
               }
                
                
                



