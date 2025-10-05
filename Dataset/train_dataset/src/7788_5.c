#include<bits/stdc++.h>
#define inf 1<<29
#define linf 1e16
#define eps (1e-5)
#define mod 1000000007
#define pi acos(-1)
#define phi (1.0+sqrt(5))/2.0
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define all(a) (a).begin(),(a).end()
#define pd(a) printf("%.10f\n",(double)(a))
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define RFOR(i,a,b) for(int i=(a)-1;(b)<=i;i--)
#define equals(a,b) (fabs((a)-(b))<eps)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<int,double> pid;
typedef pair<double,int> pdi;
typedef vector<int> vi;
typedef vector<pii> vpi;
const int dx[8]={1,0,-1,0,1,1,-1,-1};
const int dy[8]={0,1,0,-1,1,-1,1,-1};

class Point{
public:
  double x,y;
  Point(double x=0,double y=0):x(x),y(y){}

  Point operator+(Point p){ return Point(x+p.x,y+p.y);}
  Point operator-(Point p){ return Point(x-p.x,y-p.y);}
  Point operator*(double k){ return Point(x*k,y*k);}
  Point operator/(double k){ return Point(x/k,y/k);}
  bool operator<(Point p)const{ 
       return x!=p.x ? x<p.x : y<p.y; }
  bool operator==(Point p)const{ 
       return fabs(x-p.x)<eps && fabs(y-p.y)<eps;}

  double abs(){ return sqrt(norm());}
  double norm(){ return (x*x+y*y);}
};
typedef Point Vector;
typedef vector<Point> Polygon;

class Segment{
public:
  Point p1,p2;
  Segment(Point p1=Point(),Point p2=Point()):p1(p1),p2(p2){}
};
typedef Segment Line;

double norm(Vector a){ return (a.x*a.x+a.y*a.y);}
double abs(Vector a){ return sqrt(norm(a));}
double dot(Vector a,Vector b){ return (a.x*b.x+a.y*b.y);}
double cross(Vector a,Vector b){ return (a.x*b.y-a.y*b.x);}

bool isParallel(Vector a,Vector b){
    return equals(cross(a,b),0.0);
}

bool isParallel(Segment s,Segment t){
    return equals(cross(s.p1-s.p2,t.p1-t.p2),0.0);
}

int ccw(Point p0,Point p1,Point p2){
  Vector a=p1-p0;
  Vector b=p2-p0;
  if(cross(a,b)>eps)return 1;
  if(cross(a,b)<-eps)return -1;
  if(dot(a,b)<-eps)return 2;
  if(a.norm()<b.norm())return -2;
  return 0;
}

bool intersect(Point p1,Point p2,Point p3,Point p4){
  return (ccw(p1,p2,p3)*ccw(p1,p2,p4)<=0 &&
          ccw(p3,p4,p1)*ccw(p3,p4,p2)<=0);
}

bool intersect(Segment s1,Segment s2){
  return intersect(s1.p1,s1.p2,s2.p1,s2.p2);
}

Point getCrossPointLL(Line a,Line b){
  double A=cross(a.p2-a.p1,b.p2-b.p1);
  double B=cross(a.p2-a.p1,a.p2-b.p1);
  if(abs(A)<eps || abs(B)<eps)return b.p1;
  return b.p1+(b.p2-b.p1)*(B/A);
}

int contains(Polygon g,Point p){
  int n=g.size();
  bool x=false;
  for(int i=0;i<n;i++){
    Vector a=g[i]-p,b=g[(i+1)%n]-p;
    if(abs(cross(a,b))<eps && dot(a,b)<eps)return 1;
    if(a.y>b.y)swap(a,b);
    if(a.y<eps && eps<b.y && cross(a,b)>eps)x=!x;
  }
  if(x)return 2;
  return 0;
}

bool merge_if_able(Segment &s,Segment t){
  if(!equals(0.0,cross(s.p2-s.p1,t.p2-t.p1)))return false;
  if(abs(ccw(s.p1,t.p1,s.p2))==1)return false;
  if(ccw(s.p1,s.p2,t.p1)==-2 || ccw(t.p1,t.p2,s.p1)==-2)
    return false;
  s=Segment(min(s.p1,t.p1),max(s.p2,t.p2));
  return true;
}

void merge_segments(vector<Segment> &s){
  for(int i=0;i<s.size();i++)
    if(s[i].p2<s[i].p1)swap(s[i].p2,s[i].p1);
  for(int i=0;i<s.size();i++){
    for(int j=i+1;j<s.size();j++){
      if(merge_if_able(s[i],s[j])){
        s[j--]=s.back();
        s.pop_back();
      }
    }
  }
}

typedef vector<vector<int> > Graph;

Graph SegmentArrangement(vector<Segment> v,vector<Point> &ps){
  for(int i=0;i<v.size();i++){
    ps.push_back(v[i].p1);
    ps.push_back(v[i].p2);
    for(int j=i+1;j<v.size();j++){
      if(!intersect(v[i],v[j]))continue;
      ps.push_back(getCrossPointLL(v[i],v[j]));
    }
  }
  Graph g(ps.size());
  for(int i=0;i<v.size();i++){
    vector<pair<double,int> > list;
    for(int j=0;j<ps.size();j++)
      if(ccw(v[i].p1,v[i].p2,ps[j])==0)
        list.push_back(mp(norm(v[i].p1-ps[j]),j));
    sort(list.begin(),list.end());
    for(int j=0;j+1<list.size();j++){
      int a=list[j].s,b=list[j+1].s;
      g[a].push_back(b);
    }
  }
  return g;
}

int n,r;
Polygon p;
Graph g;
vector<Point> ps;

void init(){
  p.clear();
  ps.clear();
}

vector<Point> getS(Point a){
  vector<Point> res;
  res.pb(Point(a.x+r,a.y));
  res.pb(Point(a.x,a.y+r));
  res.pb(Point(a.x-r,a.y));
  res.pb(Point(a.x,a.y-r));
  return res;
}

double getDis(Segment s,Point a){
  double res=abs(s.p1.x-a.x)+abs(s.p1.y-a.y);
  res=min(res,abs(s.p2.x-a.x)+abs(s.p2.y-a.y));
  Segment t;
  t=Segment(Point(-inf,a.y),Point(inf,a.y)); 
  if(intersect(s,t)){
    Point b=getCrossPointLL(s,t);
    res=min(res,abs(a-b));
  }
  t=Segment(Point(a.x,-inf),Point(a.x,inf)); 
  if(intersect(s,t)){
    Point b=getCrossPointLL(s,t);
    res=min(res,abs(a-b));
  }
  return res;
}

bool check(Point a){
  double dis=inf;
  FOR(i,0,n){
    Segment s(p[i],p[(i+1)%n]);
    dis=min(dis,getDis(s,a));
  }
  return equals(dis,r);
}

bool check(Point a,Point b){
  if(!check(a+(b-a)/2.0))return false;
  if(contains(p,a)!=2)return false;
  if(contains(p,b)!=2)return false;
  return true;
}

double solve(){
  double res=0;
  vector<Segment> vs;
  vector<vector<Point> > vp;
  FOR(i,0,n)vp.pb(getS(p[i]));
  FOR(i,0,n){
    vector<Point> a=vp[i],b=vp[(i+1)%n];
    FOR(j,0,4){
      vs.pb(Segment(a[j],b[j]));
      vs.pb(Segment(a[j],a[(j+1)%4]));
      vs.pb(Segment(b[j],b[(j+1)%4]));
    }
  }
  merge_segments(vs);
  g=SegmentArrangement(vs,ps);
  FOR(i,0,g.size()){
    FOR(j,0,g[i].size()){
      Point a=ps[i],b=ps[g[i][j]];
      if(check(a,b))res+=abs(b-a);
    }
  }
  return res;
}

int main()
{
  while(cin>>n>>r && n){
    init();
    FOR(i,0,n){
      int x,y;
      cin>>x>>y;
      p.pb(Point(x,y));
    }
    pd(solve());
  }
  return 0;
}