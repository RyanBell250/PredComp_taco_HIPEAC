#include<bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pi M_PI
#define inf 1e14
#define eps (1e-8)
#define MAX 1000
#define equals(a,b) (fabs((a)-(b))<eps)
using namespace std;

class Point{
public:
  double x,y;
  Point(double x=0,double y=0):x(x),y(y){}

  Point operator+(Point p){ return Point(x+p.x,y+p.y);}
  Point operator-(Point p){ return Point(x-p.x,y-p.y);}
  Point operator*(double k){ return Point(x*k,y*k);}
  Point operator/(double k){ return Point(x/k,y/k);}
  bool operator<(Point p)const{ return (x!=p.x ? x<p.x : y<p.y);}
  bool operator==(Point p)const{ return fabs(x-p.x)<eps && fabs(y-p.y)<eps;}

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

bool merge_if_able(Segment &s,Segment t) {
  if(!isParallel(s,t))return false;
  if(ccw(s.p1,t.p1,s.p2)==1 ||
     ccw(s.p1,t.p1,s.p2)==-1)return false;
  if(ccw(s.p1,s.p2,t.p1)==-2 ||
     ccw(t.p1,t.p2,s.p1)==-2)return false;
  s=Segment(min(s.p1,t.p1),max(s.p2,t.p2));
  return true;
}

void merge(vector<Segment>& v) {
  for(int i=0;i<v.size();i++){
    if(v[i].p2<v[i].p1)swap(v[i].p2,v[i].p1);
  }
  for(int i=0;i<v.size();i++)
    for(int j=i+1;j<v.size();j++)
      if(merge_if_able(v[i],v[j]))
        v[j--]=v.back(),v.pop_back();
}

typedef vector<vector<int> > Graph;

Graph SegmentArrangement(vector<Segment> v,vector<Point> &ps){
  for(int i=0;i<v.size();i++){
    ps.push_back(v[i].p1);
    ps.push_back(v[i].p2);
    for(int j=i+1;j<v.size();j++){
      if(intersect(v[i],v[j]))ps.push_back(getCrossPointLL(v[i],v[j]));
    }
  }
  sort(ps.begin(),ps.end());
  ps.erase(unique(ps.begin(),ps.end()),ps.end());
  Graph g(ps.size());
  for(int i=0;i<v.size();i++){
    vector<pair<double,int> > list;
    for(int j=0;j<ps.size();j++)
      if(ccw(v[i].p1,v[i].p2,ps[j])==0)
        list.push_back(mp(norm(v[i].p1-ps[j]),j));
    sort(list.begin(),list.end());
    for(int j=0;j<list.size()-1;j++){
      int a=list[j].s,b=list[j+1].s;
      g[a].push_back(b);
      g[b].push_back(a);
    }
  }
  return g;
}

class State{
  public:
    int n,b;
    double cost;
    State(int n,int b,double cost):n(n),b(b),cost(cost){}
    bool operator<(State s)const{
      return s.cost-cost<-eps;
    }
};

Graph e;
vector<Point> vp;
Point a,b;

double getAngle(Vector v1,Vector v2){
  double r=dot(v1,v2)/(abs(v1)*abs(v2));
  if(r<-1.0)r=-1.0;
  if(1.0<r)r=1.0;
  return (acos(r)*180.0/pi);
}

double dijkstra(){
  int s=0,g=0;
  double d[MAX][MAX];
  priority_queue<State> pq;
  for(int i=0;i<vp.size();i++){
    if(vp[i]==a)s=i;
    if(vp[i]==b)g=i;
  }
  for(int i=0;i<MAX;i++)for(int j=0;j<MAX;j++)d[i][j]=inf;
  for(int i=0;i<e[s].size();i++){
    d[e[s][i]][s]=0;
    pq.push(State(e[s][i],s,0));
  }

  while(pq.size()){
    State u=pq.top();
    pq.pop();

    if(u.n==g)return u.cost;
    if(d[u.n][u.b]-u.cost<-eps)continue;

    for(int i=0;i<e[u.n].size();i++){
      int next=e[u.n][i];
      if(next==u.b)continue;
      double cost=getAngle(vp[u.n]-vp[u.b],vp[next]-vp[u.n]);
      if(u.cost+cost-d[next][u.n]<-eps){
        d[next][u.n]=u.cost+cost;
        pq.push(State(next,u.n,d[next][u.n]));
      }
    }
  }
  return -1;
}

int main()
{
  int n;

  while(1){
    cin>>n;
    if(n==0)break;
    vector<Segment> vs;
    for(int i=0;i<n;i++){
      int x1,y1,x2,y2;
      cin>>x1>>y1>>x2>>y2;
      vs.push_back(Segment(Point(x1,y1),Point(x2,y2)));
    }
    cin>>a.x>>a.y>>b.x>>b.y;
    vp.clear();
    vp.push_back(a);
    vp.push_back(b);
    merge(vs);
    e=SegmentArrangement(vs,vp);
    double ans=dijkstra();
    if(ans==-1)cout<<-1<<endl;
    else printf("%.10f\n",dijkstra());
  }
  return 0;
}