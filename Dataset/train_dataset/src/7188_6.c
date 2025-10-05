#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
#define INF 1000000000.0;
typedef pair<double, double> P;
bool compare_y(P a, P b){
    return a.second < b.second;
}
double closest_pair(vector<P> &a, int pos, int n){
    if(n==1) return INF;
    int m = n/2;
    double x = a[m+pos].first;
    double d = min(closest_pair(a,pos,m), closest_pair(a,pos+m,n-m));
    inplace_merge(a.begin()+pos,a.begin()+pos+m,a.begin()+pos+n, compare_y);
    vector<P> b;
    for(int i=0;i<n;i++){
        if(fabs(a[i+pos].first - x) >= d) continue;
        for(int j=0;j < b.size(); j++){
            double dx = a[i+pos].first - b[b.size()-1-j].first;
            double dy = a[i+pos].second - b[b.size()-j-1].second;
            if(dy >= d) break;
            d = min(d, sqrt(dx *dx + dy * dy));
        }
        b.push_back(a[i+pos]);
    }
    return d;
}
int main(){
    int n; cin >> n;
    vector<P> points(n);
    for(int i=0;i<n;i++){
        cin >> points[i].first >> points[i].second;
    }
    sort(points.begin(), points.end());
    printf("%.16lf\n", closest_pair(points, 0, n));
}
