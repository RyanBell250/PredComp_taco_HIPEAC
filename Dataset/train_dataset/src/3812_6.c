#include <bits/stdc++.h>
using namespace std;
#define x() real()
#define y() imag()
#define x1 jfwekljfwklj
#define x2 jfwekljwefkjklf
typedef complex<double> P;
const double g = 4.9;
const double EPS = 1e-8;
int N;
double V,X,Y;
struct Box{
    P p1,p2,p3,p4;
};
vector<Box> box;
P in(){
    double x,y;
    cin >> x >> y;
    return P(x,y);
}
bool inner(double a,double b,double c){
    return a + EPS < b and b < c - EPS;
}
void trying(double tanv){
    double a = - g / V / V * (1+tanv * tanv);
    double b = tanv;
    auto f = [a,b](double x){
        return a * x * x + b * x;
    };
    auto g = [a,b](double y){   
        vector<double> ps;
        double c = -y;
        double D = b*b-4*a*c;
        if( D < -EPS ){
            return ps;
        }
        if( D < EPS ) D = 0;
        D = sqrt(D);
        double x1 = (-b+D)/(2*a);
        double x2 = (-b-D)/(2*a);
        ps = {x1,x2};
        return ps;
    };
    double hx = 1e9;
    double hy = 1e9;
    vector<double> uxtmp;
    for( auto b : box ){
        if( inner(b.p1.x(),X,b.p2.x()) and b.p1.y() > Y ){
            hy = min(hy,b.p1.y());
        }
    }
    for( auto b : box ){
        double x = b.p1.x();
        uxtmp.push_back(x);
        double y = f(x);
        if( inner(b.p1.y(),y,b.p4.y()) ){
            hx = min(x,hx);
        }
    }
    for( auto b : box ){
        double x = b.p2.x();
        double y = f(x);
        uxtmp.push_back(x);
        if( inner(b.p2.y(),y,b.p3.y()) ){
            hx = min(x,hx);
        }
    }
    for( auto b : box ){
        double y = b.p1.y();
        for( double x : g(y) ){
            uxtmp.push_back(x);
            if( inner(b.p1.x(),x,b.p2.x()) ){
                hx = min(x,hx);
            }
        }
    }
    for( auto b : box ){
        double y = b.p3.y();
        for( double x : g(y) ){
            uxtmp.push_back(x);
            if( inner(b.p1.x(),x,b.p2.x()) ){
                hx = min(x,hx);
            }
        }
    }
    sort(uxtmp.begin(),uxtmp.end());
    vector<double> ux;
    for(int i = 0 ; i < uxtmp.size() ; i++)
        if( !i or uxtmp[i] - uxtmp[i-1] > EPS )
            ux.push_back(uxtmp[i]);
    for( auto b : box ){
        if( inner(b.p1.x(),X,b.p2.x()) ){
            if( inner(b.p1.y(),Y,b.p4.y()) ){
                hx = -1e9;
            }
        }
    }
    for(int i = 0 ; i+1 < ux.size() ; i++){
        double x = (ux[i] + ux[i+1] ) / 2;
        double y = f(x);
        for( auto b : box ){
            if( inner(b.p1.x(),x,b.p2.x()) ){
                if( inner(b.p1.y(),y,b.p4.y()) ){
                    hx = min(ux[i],hx);
                }
            }
        }
    }
    if( hx + EPS > X ){
        if( f(X) > Y - EPS and f(X) < hy - EPS ){
            cout << "Yes" << endl;
            exit(0);
        }
    }
}
int main(){
    cin >> N;
    cin >> V >> X >> Y;
    vector<P> ps;
    for(int i = 0 ; i < N ; i++){
        P a,b;
        a = in();
        b = in();
        ps.push_back(a);
        ps.push_back(P(b.x(),a.y()));
        ps.push_back(b);
        ps.push_back(P(a.x(),b.y()));
        box.push_back({P(a.x(),a.y()),P(b.x(),a.y()),P(b.x(),b.y()),P(a.x(),b.y())});       
    }
    for(int i = 0 ; i < 3000 ; i++){
        trying(0.001*i);
    }
    if(true){
        double x = X;
        double y = Y;
        double a = -g/V/V*x*x;
        double b = x;
        double c = -y-g/V/V*x*x;
        double D = b*b-4*a*c;
        if( D < -EPS ){
        }else{
            D = max(0.0,D);
            D = sqrt(D);
            double t1 = (-b+D)/(2*a);
            double t2 = (-b-D)/(2*a);
            trying(t1);
            trying(t2);
        }
    }
    for(int i = 0 ; i < ps.size() ; i++){
        double x = ps[i].x();
        double y = ps[i].y();
        if( x == 0 ) continue;
        double a = -g/V/V*x*x;
        double b = x;
        double c = -y-g/V/V*x*x;
        double D = b*b-4*a*c;
        if( D < -EPS ){
            continue;
        }
        if( D < EPS ) D = 0;
        double t1 = (-b+D)/(2*a);
        double t2 = (-b-D)/(2*a);
        trying(t1);
        trying(t2);
    }
    cout << "No" << endl;
}