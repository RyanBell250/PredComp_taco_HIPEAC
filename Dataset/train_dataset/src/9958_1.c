#include<bits/stdc++.h>
typedef long long int ll;
typedef unsigned long long int ull;
#define BIG_NUM 2000000000
#define HUGE_NUM 99999999999999999
#define MOD 1000000007
#define EPS 0.000000001
using namespace std;


#define NUM 40005

struct Info{
	Info(){
		row = col = 0;
	}

	Info(int arg_row,int arg_col){
		row = arg_row;
		col = arg_col;
	}
	bool operator<(const struct Info &arg) const{
		if(row != arg.row){
			return row < arg.row;
		}else{
			return col < arg.col;
		}
	}
	int row,col;
};

ll N,num_query,A,B,C,D,E,F,G;
int clock_table[8] = {1,2,3,0,7,4,5,6};
int rev_clock_table[8] = {3,0,1,2,5,6,7,4};
int LR[8] = {4,5,6,7,0,1,2,3};
int UD[8] = {6,7,4,5,2,3,0,1};
map<Info,ll> MAP;

int STATE;
int row_table[NUM],col_table[NUM];

ll get_value(ll row,ll col){

	auto at = MAP.find(Info(row,col));

	if(at == MAP.end()){
		MAP[Info(row,col)] = (row*A+col*B)%C;
	}
	return MAP[Info(row,col)];
}

Info get_pos(ll row,ll col){

	Info ret;

	switch(STATE){
	case 0:
		ret.row = row;
		ret.col = col;
		break;
	case 1:
		ret.row = N+1-col;
		ret.col = row;
		break;
	case 2:
		ret.row = N+1-row;
		ret.col = N+1-col;
		break;
	case 3:
		ret.row = col;
		ret.col = N+1-row;
		break;
	case 4:
		ret.row = row;
		ret.col = N+1-col;
		break;
	case 5:
		ret.row = col;
		ret.col = row;
		break;
	case 6:
		ret.row = N+1-row;
		ret.col = col;
		break;
	case 7:
		ret.row = N+1-col;
		ret.col = N+1-row;
		break;
	}

	return ret;
}

Info get_loc(ll row,ll col){

	Info ret = get_pos(row,col);

	ret.row = row_table[ret.row];
	ret.col = col_table[ret.col];

	return ret;
}

Info get_loc2(ll row,ll col){

	return get_pos(row,col);
}


int main(){

	scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld",&N,&num_query,&A,&B,&C,&D,&E,&F,&G);

	STATE = 0;

	for(int i = 1; i <= N; i++){
		row_table[i] = i;
		col_table[i] = i;
	}

	char buf[3];

	ll tmp_row1,tmp_col1,tmp_row2,tmp_col2,tmp_value;
	Info info,info2;

	for(int loop = 0; loop < num_query; loop++){

		scanf("%s",buf);

		switch(buf[0]){
		case 'W': //書き込み命令

			scanf("%lld %lld %lld",&tmp_row1,&tmp_col1,&tmp_value);
			info = get_loc(tmp_row1,tmp_col1);
			MAP[Info(info.row,info.col)] = tmp_value;

			break;

		case 'C': //コピー命令

			scanf("%lld %lld %lld %lld",&tmp_row1,&tmp_col1,&tmp_row2,&tmp_col2);
			info = get_loc(tmp_row1,tmp_col1);
			info2 = get_loc(tmp_row2,tmp_col2);
			MAP[Info(info2.row,info2.col)] = get_value(info.row,info.col);

			break;
		case 'S':

			if(buf[1] == 'R'){ //行スワップ

				scanf("%lld %lld",&tmp_row1,&tmp_row2);
				info = get_loc2(tmp_row1,0);
				info2 = get_loc2(tmp_row2,0);

				if(STATE%2){
					swap(col_table[info.col],col_table[info2.col]);
				}else{
					swap(row_table[info.row],row_table[info2.row]);
				}

			}else{ //列スワップ

				scanf("%lld %lld",&tmp_col1,&tmp_col2);
				info = get_loc2(0,tmp_col1);
				info2 = get_loc2(0,tmp_col2);

				if(STATE%2){
					swap(row_table[info.row],row_table[info2.row]);
				}else{
					swap(col_table[info.col],col_table[info2.col]);
				}
			}

			break;
		case 'R':

			switch(buf[1]){
			case 'L': //反時計90

				STATE = rev_clock_table[STATE];

				break;
			case 'R': //時計90

				STATE = clock_table[STATE];

				break;
			case 'H': //上下反転

				STATE = UD[STATE];

				break;
			case 'V': //左右反転

				STATE = LR[STATE];
				break;
			}
			break;
		}
	}


	ll ans = 314159265;

	for(int row = D; row <= E;row++){
		for(int col = F; col <=G; col++){

			info = get_loc(row,col);

			ans = ans*31 + get_value(info.row,info.col);
			ans %=MOD;
	    }
	}

	printf("%lld\n",ans);

	return 0;
}

