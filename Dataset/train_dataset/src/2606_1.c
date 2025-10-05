
#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <set>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <iostream>
using namespace std;
#define eps 1e-7
#define pw(x) ((x)*(x))
typedef long long LL;
struct P
{
    double x,y;
    P () {}
    P (double x,double y) : x(x),y(y) {}
    P operator - (const P & b)
    {
        return P (x-b.x,y-b.y);
    }
    double operator * (const P & b)
    {
        return x*b.y-y*b.x;
    }
    double operator & (const P & b)
    {
        return x*b.x+y*b.y;
    }
    double dorm()
    {
        return sqrt(pw(x)+pw(y));
    }
}p[300],s[300],tp[300];
int sgn(double x)
{
    return x<-eps?-1:x>eps;
}
double cal(P a,P b,P c) 
{
    int t1=sgn((c-a)&(b-a));
    int t2=sgn((c-b)&(a-b));
    if(t1>=0&&t2>=0) return fabs((a-c)*(a-b))/(a-b).dorm();
    return min((c-a).dorm(),(c-b).dorm());
}
double maybe[10000]; 
int cnt,flag;
double L;
int n,m;
void run(P a,P b,P c) 
{
    double l=-20000,h=20000,mid1,mid2;
    for(int i=0;i<50;i++){
        mid1=(2*l+h)/3;
        mid2=(2*h+l)/3;
        double t1=cal(a,b,P(mid1,c.y));
        double t2=cal(a,b,P(mid2,c.y));
        if(sgn(t1-t2)>=0) l=mid1;
        else h=mid2;
    }
    double mid;
    l=-20000;h=mid1;
    for(int i=0;i<50;i++){
        mid=(l+h)/2;
        double t1=cal(a,b,P(mid,c.y));
        if(sgn(t1-L)>=0) l=mid;
        else h=mid;
    }
    double delta=mid-c.x;
    if(flag) delta=-delta;
    maybe[cnt++]=delta;
    l=mid1,h=20000;
    for(int i=0;i<50;i++){
        mid=(l+h)/2;
        double t1=cal(a,b,P(mid,c.y));
        if(sgn(t1-L)>=0) h=mid;
        else l=mid;
    }
    delta=mid-c.x;
    if(flag) delta=-delta;
    maybe[cnt++]=delta;
}
void creat()
{
    cnt=0;
    s[m]=s[0],p[n]=p[0];
    flag=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            run(s[j],s[j+1],p[i]);
        }
    }
    flag=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            run(p[j],p[j+1],s[i]);
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++) {
            maybe[cnt++]=p[j].x-s[i].x;
        }
    }
}
int in(P a,P pt[],int n)
{
    int cnt=0;
    pt[n]=pt[0];
    for(int i=0;i<n;i++){
        P x=pt[i],y=pt[i+1];
        if(sgn(x.y-y.y)>0) swap(x,y);
        if(sgn(x.y-a.y)>=0||sgn(y.y-a.y)<0) continue;
        double t=(x-a)*(y-a);
        if(sgn(t)>0) cnt++;
    }
    return cnt&1;
}
double solve()
{
    double ans=1e10;
    for(int i=0;i<cnt;i++){
        double x=maybe[i];
        for(int j=0;j<m;j++){
            tp[j].x=s[j].x+x;
            tp[j].y=s[j].y;
        }
        tp[m]=tp[0];
        int flag=0;
        for(int j=0;j<n;j++){
            for(int k=0;k<m;k++){
                int t1=sgn((p[j]-tp[k])*(tp[k+1]-tp[k]))*sgn((p[j+1]-tp[k])*(tp[k+1]-tp[k]));
                int t2=sgn((tp[k]-p[j])*(p[j+1]-p[j]))*sgn((tp[k+1]-p[j])*(p[j+1]-p[j]));
                if(t1<0&&t2<0) {
                    flag=1;
                    break;
                }
                double dis=min(min(cal(p[j],p[j+1],tp[k]),cal(p[j],p[j+1],tp[k+1])),min(cal(tp[k],tp[k+1],p[j]),cal(tp[k],tp[k+1],p[j+1])));
                if(dis-L<-1e-6) {
                    flag=1;
                    break;
                }
            }
        }
        if(flag) continue;
        flag=in(tp[0],p,n)||in(p[0],tp,m);
        if(flag) continue;
        double minx=1e10,maxx=-1e10;
        for(int j=0;j<m;j++){
            minx=min(minx,tp[j].x);
            maxx=max(maxx,tp[j].x);
        }
        for(int j=0;j<n;j++){
            minx=min(minx,p[j].x);
            maxx=max(maxx,p[j].x);
        }
        ans=min(ans,maxx-minx);
    }
    return ans;
}
int main()
{   
    P a,b,c;
    while(scanf("%lf",&L)&&sgn(L)){
        scanf("%d",&n);
        for(int i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        scanf("%d",&m);
        for(int i=0;i<m;i++) scanf("%lf%lf",&s[i].x,&s[i].y);
        creat();
        printf("%f\n",solve());
    }
    return 0;
}