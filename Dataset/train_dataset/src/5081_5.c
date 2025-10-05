#include<bits/stdc++.h>
typedef long long int ll;
typedef unsigned long long int ull;
#define BIG_NUM 2000000000
#define HUGE_NUM 1000000000000000000
#define MOD 1000000007
using namespace std;
#define EPS 0.00001
#define EPS2 0.0000000001
#define EPS3 0.000001
struct Point{
	Point(long double arg_x,long double arg_y){
		x = arg_x;
		y = arg_y;
	}
	Point(){
		x = y = 0.0;
	}
	Point operator + (Point p){ return Point(x+p.x,y+p.y); }
	Point operator - (Point p){ return Point(x-p.x,y-p.y);}
	Point operator * (long double a){ return Point(a*x,a*y); }
	Point operator / (long double a){ return Point(x/a,y/a); }
	long double abs(){ return sqrt(norm()); }
	long double norm(){ return x*x + y*y; }
	bool operator<(const Point &p) const{
		return x != p.x? x < p.x: y < p.y;
	}
	bool operator == (const Point &p) const{
		return fabs(x-p.x) < EPS2 && fabs(y-p.y) < EPS2;
	}
	long double x,y;
};
struct Info{
	bool operator<(const struct Info &arg) const{
		return dist < arg.dist;
	}
	long double dist;
	Point point;
};
typedef Point Vector;
typedef vector<Point> Polygon;
struct Line{
	Line(){
	}
	Line(Point a,Point b){
		p[0] = a;
		p[1] = b;
	}
	Point p[2];
};
int N;
long double NUM = BIG_NUM;
long double calc_dist(Point A,Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
int func(long double x1,long double y1,long double x2, long double y2, long double xp, long double yp){
	long double naiseki,norm1,norm2,gaiseki;
	norm1 = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	norm2 = sqrt((xp-x1)*(xp-x1)+(yp-y1)*(yp-y1));
	naiseki = (xp-x1)*(x2-x1)+(yp-y1)*(y2-y1);
	gaiseki = (x2-x1)*(yp-y1)-(xp-x1)*(y2-y1);
	if(gaiseki > EPS2){
		return 1;
	}else if(gaiseki < -EPS2){
		return -1;
	}
	if(naiseki < -EPS2){
		return 2;
	}
	if(norm1 < norm2){
		return -2;
	}
	return 0;
}
bool is_Cross(Line a,Line b){
	if(func(a.p[0].x,a.p[0].y,a.p[1].x,a.p[1].y,b.p[0].x,b.p[0].y)*
			func(a.p[0].x,a.p[0].y,a.p[1].x,a.p[1].y,b.p[1].x,b.p[1].y) <= 0 &&
			func(b.p[0].x,b.p[0].y,b.p[1].x,b.p[1].y,a.p[0].x,a.p[0].y)*
			func(b.p[0].x,b.p[0].y,b.p[1].x,b.p[1].y,a.p[1].x,a.p[1].y) <= 0){
		return true;
	}
	return false;
}
long double calc_slope(Line A){
	if(fabs(A.p[0].x-A.p[1].x) < EPS2){
		return DBL_MAX;
	}else if(fabs(A.p[0].y-A.p[1].y) < EPS2){
		return 0;
	}else{
		return (A.p[1].y-A.p[0].y)/(A.p[1].x-A.p[0].x);
	}
}
Point calc_Cross_Point(long double x1,long double x2,long double x3,long double x4,long double y1,long double y2,long double y3,long double y4){
	Point ret;
	ret.x = ((x2-x1)*(y3*(x4-x3)+x3*(y3-y4))-(x4-x3)*(y1*(x2-x1)+x1*(y1-y2)))/((y2-y1)*(x4-x3)-(y4-y3)*(x2-x1));
	if(x1 != x2){
		ret.y = ((y2-y1)*ret.x+y1*(x2-x1)+x1*(y1-y2))/(x2-x1);
	}else{
		ret.y = ((y4-y3)*ret.x+y3*(x4-x3)+x3*(y3-y4))/(x4-x3);
	}
	return ret;
}
Point calc_Cross_Point(Point a,Point b,Point c,Point d){
	return calc_Cross_Point(a.x,b.x,c.x,d.x,a.y,b.y,c.y,d.y);
}
Point calc_minus(Point a,Point b){
    Point ret;
    ret.x = a.x-b.x;
    ret.y = a.y-b.y;
    return ret;
}
long double norm(Vector a){
	return a.x*a.x+a.y*a.y;
}
long double abs(Vector a){
	return sqrt(norm(a));
}
long double cross(Vector a,Vector b){
    return a.x*b.y-a.y*b.x;
}
long double dot(Vector a,Vector b){
    return a.x*b.x + a.y*b.y;
}
long double calc_len(Vector a){
    return sqrt(a.x*a.x+a.y*a.y);
}
long double getDistanceLP(Line l,Point p){
    return fabs(cross(calc_minus(l.p[1],l.p[0]),calc_minus(p,l.p[0]))/calc_len(calc_minus(l.p[1],l.p[0])));
}
long double getDistanceSP(Line l,Point p){
	if(dot(calc_minus(l.p[1],l.p[0]),calc_minus(p,l.p[0])) < 0.0)return calc_len(calc_minus(p,l.p[0]));
	if(dot(calc_minus(l.p[0],l.p[1]),calc_minus(p,l.p[1])) < 0.0)return calc_len(calc_minus(p,l.p[1]));
	return getDistanceLP(l,p);
}
long double getDistance(Line A,Line B){
	if(is_Cross(A,B))return 0.0;
	return min(min(getDistanceSP(A,B.p[0]),getDistanceSP(A,B.p[1])),
			min(getDistanceSP(B,A.p[0]),getDistanceSP(B,A.p[1])));
}
Point calc_Cross_Point(Line A,Line B){
	if(getDistanceSP(B,A.p[0]) < EPS2){
		return A.p[0];
	}else if(getDistanceSP(B,A.p[1]) < EPS2){
		return A.p[1];
	}else if(getDistanceSP(A,B.p[0]) < EPS2){
		return B.p[0];
	}else if(getDistanceSP(A,B.p[1]) < EPS2){
		return B.p[1];
	}
	return calc_Cross_Point(A.p[0],A.p[1],B.p[0],B.p[1]);
}
Point calc_Reflection_Point(long double x1,long double y1,long double x2,long double y2,long double xp,long double yp){
	Point ret;
	bool X_FLG = false,Y_FLG = false;
	long double slope;
	if(y1 == y2){
		X_FLG = true;
	}else if(x1 == x2){
		Y_FLG = true;
	}else{
		slope = (y2-y1)/(x2-x1);
	}
	if(X_FLG){
		ret.x = xp,ret.y=y1;
	}else if(Y_FLG){
		ret.x = x1,ret.y = yp;
	}else{
		ret.x = (yp*(x2-x1)*(y2-y1)+xp*(x2-x1)*(x2-x1)-y1*(y2-y1)*(x2-x1)+x1*(y2-y1)*(y2-y1))/((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
		ret.y = ((x1-x2)*ret.x+yp*(y2-y1)+xp*(x2-x1))/(y2-y1);
	}
	ret.x = 2*ret.x-xp;
	ret.y = 2*ret.y-yp;
	return ret;
}
Point calc_Reflection_Point(Line line,Point point){
	return calc_Reflection_Point(line.p[0].x,line.p[0].y,line.p[1].x,line.p[1].y,point.x,point.y);
}
bool isSame(Point a, Point b){
	return abs(a-b) < EPS;
}
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -1;
static const int ON_SEGMENT = 0;
int ccw(Point p0,Point p1,Point p2){
	Vector a = p1 - p0;
	Vector b = p2 - p0;
	if(cross(a,b) > EPS2)return COUNTER_CLOCKWISE;
	if(cross(a,b) < -EPS2)return CLOCKWISE;
	if(dot(a,b) < -EPS2)return ONLINE_BACK;
	if(a.norm() < b.norm())return ONLINE_FRONT;
	return ON_SEGMENT;
}
void  func(){
	Polygon P;
	long double x,y;
	for(int i = 0; i < N; i++){
		scanf("%Lf %Lf",&x,&y);
		P.push_back(Point(x,y));
	}
	int num_max = 0;
	long double ans = 0;
	long double slope,slope2;
	Line base_line; 
	int num_cross;
	Point cross_point[2],tmp_cross;
	int near_from[2],far_from[2];
	Polygon A,B;
	Polygon final_A,final_B;
	vector<Info> info;
	Vector pre_A,pre_B,now_A,now_B;
	vector<int> match_A,match_B;
	for(int from = 0; from < N; from++){
		for(int to = 0; to < N; to++){
			if(to == from)continue;
			slope = calc_slope(Line(P[from],P[to]));
			if(fabs(slope-DBL_MAX) < EPS2){ 
				long double tmp_y = (P[from].y+P[to].y)/2.0;
				base_line.p[0] = Point(-NUM,tmp_y); 
				base_line.p[1] = Point(NUM,tmp_y); 
			}else if(fabs(slope) < EPS2){ 
				long double tmp_x = (P[from].x+P[to].x)/2.0;
				base_line.p[0] = Point(tmp_x,-NUM); 
				base_line.p[1] = Point(tmp_x,NUM); 
			}else{
				slope2 = -1.0/slope;
				Point tmp_mid = Point((P[from].x+P[to].x)/2.0,(P[from].y+P[to].y)/2.0);
				base_line.p[0] = Point(tmp_mid.x-NUM,tmp_mid.y-NUM*slope2);
				base_line.p[1] = Point(tmp_mid.x+NUM,tmp_mid.y+NUM*slope2);
			}
			num_cross = 0;
			for(int i = 0; i < N; i++){
				Line tmp_line = Line(P[(from+i)%N],P[(from+(i+1))%N]);
				if(!is_Cross(base_line,tmp_line))continue;
				cross_point[num_cross] = calc_Cross_Point(base_line,tmp_line);
				if(num_cross == 0){ 
					near_from[num_cross] = (from+i)%N;
					far_from[num_cross] = (from+(i+1))%N;
				}else{ 
					near_from[num_cross] = (from+(i+1))%N;
					far_from[num_cross] = (from+i)%N;
				}
				num_cross++;
			}
			bool FLG = true;
			if(near_from[0] != near_from[1]){
				for(int i = 0; i < N; i++){
					if((near_from[0]+i)%N == near_from[1]){
						break;
					}else if((near_from[0]+i)%N == far_from[0] || (near_from[0]+i)%N == far_from[1]){
						FLG = false;
						break;
					}
				}
			}else{
				for(int i = 0; i < N; i++){
					if((far_from[1]+i)%N == far_from[0]){
						break;
					}else if((far_from[1]+i)%N == near_from[0] || (far_from[1]+i)%N == near_from[1]){
						FLG = false;
						break;
					}
				}
			}
			if(!FLG){
				swap(cross_point[0],cross_point[1]);
				swap(near_from[0],near_from[1]);
				swap(far_from[0],far_from[1]);
			}
			A.clear();
			B.clear();
			A.push_back(cross_point[1]);
			for(int i = 0; i < N; i++){
				if(isSame(P[(far_from[1]+i)%N],cross_point[0])||isSame(P[(far_from[1]+i)%N],cross_point[1]))continue;
				A.push_back(P[(far_from[1]+i)%N]);
				if((far_from[1]+i)%N == far_from[0])break;
			}
			A.push_back(cross_point[0]);
			reverse(A.begin(),A.end()); 
			B.push_back(cross_point[0]);
			for(int i = 0; i < N; i++){
				if(isSame(P[(near_from[0]+i)%N],cross_point[0])||isSame(P[(near_from[0]+i)%N],cross_point[1]))continue;
				Point ref_p = calc_Reflection_Point(base_line,P[(near_from[0]+i)%N]);
				B.push_back(ref_p);
				if((near_from[0]+i)%N == near_from[1])break;
			}
			B.push_back(cross_point[1]);
			final_A.clear();
			final_B.clear();
			final_A.push_back(A[0]);
			for(int a = 1; a < A.size(); a++){
				Line work_A = Line(A[a-1],A[a]);
				info.clear();
				for(int b = 0; b < B.size(); b++){
					Line work_B = Line(B[b],B[(b+1)%B.size()]);
					if(!is_Cross(work_A,work_B))continue;
					Point tmp_cross = calc_Cross_Point(work_A,work_B);
					if(!isSame(tmp_cross,work_A.p[0]) && !isSame(tmp_cross,work_A.p[1]) &&
							!isSame(tmp_cross,work_B.p[0]) && !isSame(tmp_cross,work_B.p[1])){
						Info tmp_info;
						tmp_info.point = tmp_cross;
						tmp_info.dist = calc_dist(A[a-1],tmp_cross);
						info.push_back(tmp_info);
					}
				}
				if(info.size() == 0){
					final_A.push_back(A[a]);
					continue;
				}
				sort(info.begin(),info.end());
				for(int i = 0; i < info.size(); i++){ 
					final_A.push_back(info[i].point);
				}
				final_A.push_back(A[a]);
			}
			final_B.push_back(B[0]);
			for(int b = 1; b < B.size(); b++){
				Line work_B = Line(B[b-1],B[b]);
				info.clear();
				for(int a = 0; a < A.size(); a++){
					Line work_A = Line(A[a],A[(a+1)%A.size()]);
					if(!is_Cross(work_A,work_B))continue;
					Point tmp_cross = calc_Cross_Point(work_A,work_B);
					if(!isSame(tmp_cross,work_B.p[0]) && !isSame(tmp_cross,work_B.p[1]) &&
							!isSame(tmp_cross,work_A.p[0]) && !isSame(tmp_cross,work_A.p[1])){
						Info tmp_info;
						tmp_info.point = tmp_cross;
						tmp_info.dist = calc_dist(B[b-1],tmp_cross);
						info.push_back(tmp_info);
					}
				}
				if(info.size() == 0){
					final_B.push_back(B[b]);
					continue;
				}
				for(int i = 0; i < info.size(); i++){ 
					final_B.push_back(info[i].point);
				}
				final_B.push_back(B[b]);
			}
			match_A.clear();
			match_B.clear();
			for(int a = 1; a < final_A.size()-1; a++){
				for(int b = 1; b < final_B.size()-1; b++){
					if(isSame(final_A[a],final_B[b])){
						match_A.push_back(a);
						break;
					}
				}
			}
			for(int b = 1; b < final_B.size()-1; b++){
				for(int a = 1; a < final_A.size()-1; a++){
					if(isSame(final_B[b],final_A[a])){
						match_B.push_back(b);
						break;
					}
				}
			}
			match_A.push_back(final_A.size()-1);
			match_B.push_back(final_B.size()-1);
			pre_A = cross_point[1]-cross_point[0];
			pre_B = pre_A;
			long double tmp_dist = calc_dist(cross_point[0],cross_point[1]);
			int index_A = 0,index_B = 0;
			int tmp_num = 1;
			Point pre_P = cross_point[1];
			long double deg_A,deg_B;
			for(int i = 0; i < match_A.size(); i++){
				if(i > 0){
					pre_A = pre_P-final_A[index_A];
					pre_B = pre_P-final_B[index_B];
				}
				now_A = final_A[(index_A+1)]-final_A[index_A];
				now_B = final_B[(index_B+1)]-final_B[index_B];
				long double cos_A = dot(pre_A,now_A)/(abs(now_A)*abs(pre_A));
				long double cos_B = dot(pre_B,now_B)/(abs(now_B)*abs(pre_B));
				if(fabs(cos_A+1.0) < EPS2){ 
					deg_A = 180.0;
				}else{
					deg_A = acos(cos_A)*(180/M_PI);
				}
				if(fabs(cos_B+1.0) < EPS2){ 
					deg_B = 180.0;
				}else{
					deg_B = acos(cos_B)*(180/M_PI);
				}
				if(ccw(final_A[index_A],pre_P,final_A[(index_A+1)]) == CLOCKWISE){
					deg_A = 360.0-deg_A;
				}
				if(ccw(final_B[index_B],pre_P,final_B[(index_B+1)]) == CLOCKWISE){
					deg_B = 360.0-deg_B;
				}
				if(deg_A > deg_B){
					if(fabs(deg_A-180.0) < EPS3){ 
						tmp_num--;
					}
					for(int k = index_A+1; k <= match_A[i]; k++){
						tmp_dist += calc_dist(final_A[k],final_A[k-1]);
						pre_P = final_A[k-1];
						tmp_num++;
					}
				}else{
					if(fabs(deg_B-180.0) < EPS3){ 
						tmp_num--;
					}
					for(int k = index_B+1; k <= match_B[i]; k++){
						tmp_dist += calc_dist(final_B[k],final_B[k-1]);
						pre_P = final_B[k-1];
						tmp_num++;
					}
				}
				index_A = match_A[i];
				index_B = match_B[i];
			}
			if(isSame(cross_point[0],cross_point[1]))tmp_num--; 
			if(tmp_num < num_max)continue;
			if(tmp_num > num_max){
				num_max = tmp_num;
				ans = tmp_dist;
			}else{ 
				ans = max(ans,tmp_dist);
			}
		}
	}
	printf("%.15Lf\n",ans);
}
int main(){
	while(true){
		scanf("%d",&N);
		if(N == 0)break;
		func();
	}
	return 0;
}
