#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
typedef long double ld;
struct po{
	ld x;
	ld y;
	po(ld a){ x=a; y=0; }
	po(ld a,ld b){ x=a; y=b; }
	po(){}
	inline ld operator()(const po& rhs) const {
		return x*rhs.x+y*rhs.y;
	}
	inline po& operator +=(const po& rhs){
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	inline po& operator -=(const po& rhs){
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	inline po& operator *=(const po& rhs){
		ld x_ = x*rhs.x-y*rhs.y;
		y = x*rhs.y+y*rhs.x;
		x = x_;
		return *this;
	}
	inline po& operator /=(const po& rhs){
		ld x_ = x*rhs.x+y*rhs.y;
		y = -x*rhs.y+y*rhs.x;
		x = x_;
		ld nor = rhs(rhs);
		x /= nor;
		y /= nor;
		return *this;
	}
	bool operator < ( const po& rhs )const {
		return false;
	}
};
inline po operator+(const po& a, const po& b){return po(a) += b;}
inline po operator-(const po& a, const po& b){return po(a) -= b;}
inline po operator*(const po& a, const po& b){return po(a) *= b;}
inline po operator/(const po& a, const po& b){return po(a) /= b;}
inline po similar(const po& a, const po& b, const po& c,const po &p, const po& q){
	return p+(q-p)*(c-a)/(b-a);
}
typedef pair<po,po> se;
#define fr first
#define sc second
struct li{
	ld a;
	ld b;
	ld c;
	li(po p,po q){
		a = q.y-p.y;
		b = p.x-q.x;
		c = p.y*q.x-p.x*q.y;
	}
	li(){}
	inline ld operator()(const po& p) const {
		return a*p.x+b*p.y+c;
	}
};
void intersect(const li &l, const li &m, po* &ret){
	if(abs(l.a*m.b-m.a*l.b) <= 1e-18){
		ret = nullptr;
		return;
	}
	ret = new po;
	ret->x = -(l.c*m.b-m.c*l.b)/(l.a*m.b-m.a*l.b);
	ret->y = -(l.a*m.c-m.a*l.c)/(l.a*m.b-m.a*l.b);
}
inline bool on(const po &p, const se &s){
	return (s.fr-p)(s.sc-p) <= 1e-9;
}
void intersect(const se &s, const li &l, po* &ret){
	li m = li(s.fr,s.sc);
	po *p;
	intersect(l,m,p);
	if(p == nullptr || on(*p,s))ret = p;
	else {
		delete p;
		ret = nullptr;
	}
}
void intersect(const se &s, const se & t, po* &ret){
	li l = li(s.fr,s.sc);
	li m = li(t.fr,t.sc);
	po *p;
	intersect(l,m,p);
	if(p == nullptr || (on(*p,s)&&on(*p,t)))ret = p;
	else {
		delete p;
		ret = nullptr;
	}
}
inline ld dist(const po &p, const po &q){
	return sqrt((p-q)(p-q));
}
inline li perpen(const po &p, const li &l){
	li ret;
	ret.a = l.b;
	ret.b = -l.a;
	ret.c = l.a*p.y-l.b*p.x;
	return ret;
}
inline po perpen_leg(const po &p, const li &l){
	po ret;
	li m = perpen(p,l);
	ret.x = -(l.c*m.b-m.c*l.b)/(l.a*m.b-m.a*l.b);
	ret.y = -(l.a*m.c-m.a*l.c)/(l.a*m.b-m.a*l.b);
	return ret;
}
inline ld dist(const po &p, const se &s){
	po h = perpen_leg(p,li(s.fr,s.sc));
	if(on(h,s))return dist(p,h);
	else return min( dist(p,s.fr) , dist(p,s.sc) );
}
int n,r;
po p[102];
inline ld dist_1(const po &p, const po &q){
	return abs(p.x-q.x)+abs(p.y-q.y);
}
inline ld dist_1(const po &p, const se &s){
	ld ret = min(dist_1(p,s.fr),dist_1(p,s.sc));
	po* q;
	intersect(s,li(p,p+1),q);
	if(q != nullptr){
		ret = min( ret , dist_1(p,*q) );
		delete q;
	}
	intersect(s,li(p,p+po(0,1)),q);
	if(q != nullptr){
		ret = min( ret , dist_1(p,*q) );
		delete q;
	}
	return ret;
}
bool inside(po q){
	cout.precision(20);
	int cnt = 0;
	for(int i = 0 ; i < n ; i ++){
		po* s;
		intersect(se(p[i],p[i+1]),se(q,q-1000000.0),s);
		if(s != nullptr){
			delete s;
			cnt ++;
		}
	}
	if(cnt%2 == 0)return false;
	for(int i = 0 ; i < n ; i ++){
		if(dist_1(q,se(p[i],p[i+1])) <= r)return false;
	}
	return true;
}
int main_solve(){
	cin >> n >> r;
	if(n == 0)return 1;
	for(int i = 0 ; i < n ; i ++){
		cin >> p[i].x >> p[i].y;
	}
	p[n] = p[0];
	vector<se> L;
	po d[4];
	d[0].x = r; d[0].y = 0;
	d[1].x = 0; d[1].y = r;
	d[2].x = -r; d[2].y = 0;
	d[3].x = 0; d[3].y = -r;
	for(int i = 0 ; i < n ; i ++){
		for(int j = 0 ; j < 4 ; j ++){
			L.push_back(se(p[i]+d[j],p[i]+d[(j+1)&3]));
		}
	}
	for(int i = 0 ; i < n ; i ++){
		for(int j = 0 ; j < 4 ; j ++){
			L.push_back(se(p[i]+d[j],p[i+1]+d[j]));
		}
	}
	vector<se> L_;
	for(int i = 0 ; i < L.size() ; i ++){
		for(int j = i+1 ; j <= L.size() ; j ++){
			if(j == L.size()){
				L_.push_back(L[i]);
				break;
			}
			li l = li(L[i].fr,L[i].sc);
			li m = li(L[j].fr,L[j].sc);
			if(abs(l.a*m.b-m.a*l.b) <= 1e-18){
				po X_ = similar(L[j].fr,L[j].sc,L[i].fr,po(0.0),po(1.0));
				po Y_ = similar(L[j].fr,L[j].sc,L[i].sc,po(0.0),po(1.0));
				if(abs(X_.y) > 1e-10 || abs(Y_.y) > 1e-10){
					continue;
				}
				ld X = X_.x;
				ld Y = Y_.x;
				if(max(X,Y) <= 1e-10)continue;
				if(min(X,Y) >= 1.0+1e-10)continue;
				po FR = similar(0.0,1.0,min(min(X,Y),(ld)0.0),L[j].fr,L[j].sc);
				po SC = similar(0.0,1.0,max(max(X,Y),(ld)1.0),L[j].fr,L[j].sc);
				L[j].fr = FR;
				L[j].sc = SC;
				break;
			}
		}
	}
	L = L_;
	ld ret = 0.0;
	for(int xxx = 0 ; xxx < L.size() ; xxx ++){
		se l = L[xxx];
		vector<pair<ld,po>> vec;
		vec.push_back(pair<ld,po>(0.0,l.fr));
		vec.push_back(pair<ld,po>(1.0,l.sc));
		for(int yyy = 0 ; yyy < L.size() ; yyy ++){
			if(xxx == yyy)continue;
			se m = L[yyy];
			po* p;
			intersect(l,m,p);
			if(p == nullptr)continue;
			else {
				vec.push_back(pair<ld,po>(similar(l.fr,l.sc,*p,0.0,1.0).x,*p));
				delete p;
			}
		}
		sort(vec.begin(),vec.end());
		po D = po(l.fr.y-l.sc.y,l.sc.x-l.fr.x);
		D /= sqrt(D(D));
		D *= 1e-6;
		ld dx = D.x;
		ld dy = D.y;
		for(int i = 0 ; i+1 < vec.size() ; i ++){
			bool b1 = inside((vec[i].sc+vec[i+1].sc)/2.0+po(dx,dy));
			bool b2 = inside((vec[i].sc+vec[i+1].sc)/2.0-po(dx,dy));
			if(b1 != b2){
				ret += dist(vec[i].sc,vec[i+1].sc);
			}
		}
	}
	cout.precision(20);
	cout << ret << endl;
	return 0;
}
int main(){
	while(!main_solve()){};
}
