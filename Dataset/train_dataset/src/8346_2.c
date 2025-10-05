#include <iostream>
#include <utility>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#define llint long long
#define eps 1e-8
using namespace std;
struct vec2d{
	double x, y;
	vec2d(){}
	vec2d(double x, double y){
		this->x = x, this->y = y;
	}
	double add(double a, double b){
		if(fabs(a+b) < eps * (fabs(a) + fabs(b))) return 0.0;
		return a+b;
	}
	vec2d operator+(vec2d ope){
		return vec2d(add(x, ope.x), add(y, ope.y));
	}
	vec2d operator-(vec2d ope){
		return vec2d(add(x, -ope.x), add(y, -ope.y));
	}
	vec2d operator*(double t){
		return vec2d(x*t, y*t);
	}
	vec2d operator/(double t){
		return vec2d(x/t, y/t);
	}
	double dot(vec2d ope){
		return add(x*ope.x, y*ope.y);
	}
	double cross(vec2d ope){
		return add(x*ope.y, -y*ope.x);
	}
	double norm(){
		double d2 = dot(*this);
		if(d2 > 0) return sqrt(d2);
		return 0.0;
	}
};
llint n;
vec2d p[10];
int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i = 0; i < 10; i++) p[i].x = p[i].y = 0;
	for(int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;
	int perm[10];
	for(int i = 0; i < 10; i++) perm[i] = 0;
	for(int i = 1; i <= n; i++) perm[i] = i;
	double ans = 1e9;
	do{
		vec2d a = p[perm[1]], b = vec2d(1, 0);
		double tmp = fabs(acos(a.dot(b) / (a.norm()*b.norm())));;
		for(int i = 1; i <= n; i++){
			vec2d a = p[perm[i]]-p[perm[i-1]], b = p[perm[i+1]]-p[perm[i]];
			tmp += fabs(acos(a.dot(b) / (a.norm()*b.norm())));
		}
		ans = min(ans, tmp);
	}while(next_permutation(perm+1, perm+n+1));
	printf("%.11f\n", ans * 180 / 3.14159265358979);
	return 0;
}
