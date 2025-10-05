#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cfloat>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <time.h>
typedef long long int ll;
typedef unsigned long long int ull;
#define BIG_NUM 2000000000
#define MOD 1000000007
#define EPS 0.000000001
using namespace std;
enum Type{
	Stone,
	Mobile,
};
struct Info{
	Type type;
	int index_left,index_right;
	double weight,left,right,most_left_loc,most_right_loc;
};
Info info[12];
int num_stone,eq_index;
int table[7][720][6],table_index[7],eq_num[7];
double room_width;
char equation[7][100000][12];
priority_queue<double> Q;
void strcpy(char* to,char* str){
	for(int i=0;str[i] != '\0';i++){
		to[i] = str[i];
		to[i+1] = '\0';
	}
}
void makeEquation(int array[6],int array_index,char buf[12],int buf_index,int value,int rest_mult,int length){
	if(rest_mult == 0){
		buf[buf_index] = '\0';
		strcpy(equation[length][eq_num[length]++],buf);
		return;
	}
	if(array_index < length){
		char next_buf[12];
		for(int i = 0; i < buf_index; i++)next_buf[i] = buf[i];
		next_buf[buf_index] = array[array_index]+'0';
		makeEquation(array,array_index+1,next_buf,buf_index+1,value+1,rest_mult,length);
	}
	if(value >= 2){
		char next_buf[12];
		for(int i = 0; i < buf_index; i++)next_buf[i] = buf[i];
		next_buf[buf_index] = '*';
		makeEquation(array,array_index,next_buf,buf_index+1,value-1,rest_mult-1,length);
	}
}
void calc_mobile(int tmp_index,int buf_index,Info tmp_info[12],int info_index,stack<int> S){
	if(equation[num_stone][tmp_index][buf_index] == '\0'){
		Q.push(tmp_info[info_index-1].most_left_loc+tmp_info[info_index-1].most_right_loc);
		return;
	}
	int left,right;
	double left_weight,right_weight;
	char tmp_ch;
	stack<int> WORK,NEXT;
	while(!S.empty()){
		WORK.push(S.top());
		S.pop();
	}
	while(!WORK.empty()){
		NEXT.push(WORK.top());
		WORK.pop();
	}
	tmp_ch = equation[num_stone][tmp_index][buf_index];
	if(tmp_ch >= '0' && tmp_ch <= '5'){
		NEXT.push(tmp_ch-'0');
		calc_mobile(tmp_index,buf_index+1,tmp_info,info_index,NEXT);
	}else{ 
		left = NEXT.top();
		NEXT.pop();
		right = NEXT.top();
		NEXT.pop();
		left_weight = tmp_info[left].weight;
		right_weight = tmp_info[right].weight;
		tmp_info[info_index].left = (right_weight)/(left_weight+right_weight);
		tmp_info[info_index].right = 1.0-tmp_info[info_index].left;
		tmp_info[info_index].type = Mobile;
		tmp_info[info_index].index_left = left;
		tmp_info[info_index].index_right = right;
		tmp_info[info_index].weight = left_weight+right_weight;
		tmp_info[info_index].most_left_loc = max(tmp_info[info_index].left+tmp_info[left].most_left_loc,tmp_info[right].most_left_loc-tmp_info[info_index].right);
		tmp_info[info_index].most_right_loc = max(tmp_info[info_index].right+tmp_info[right].most_right_loc,tmp_info[left].most_right_loc-tmp_info[info_index].left);
		NEXT.push(info_index);
		calc_mobile(tmp_index,buf_index+1,tmp_info,info_index+1,NEXT);
	}
}
void calc(int tmp_index){
	Info tmp_info[12];
	for(int i = 0; i < num_stone; i++)tmp_info[i] = info[i];
	for(int i = num_stone; i < 12; i++){
		tmp_info[i].index_left = -1;
		tmp_info[i].index_right = -1;
		tmp_info[i].most_left_loc = 0.0;
		tmp_info[i].most_right_loc = 0.0;
	}
	stack<int> S;
	calc_mobile(tmp_index,0,tmp_info,num_stone,S);
}
void func(){
	while(!Q.empty())Q.pop();
	scanf("%lf",&room_width);
	scanf("%d",&num_stone);
	for(int i = 0; i < num_stone; i++){
		scanf("%lf",&info[i].weight);
		info[i].type = Stone;
		info[i].index_left = -1;
		info[i].index_right = -1;
	}
	if(num_stone == 1){
		printf("0.00000000\n");
		return;
	}
	eq_index = eq_num[num_stone];
	for(int i = 0; i < eq_index; i++){
		calc(i);
	}
	while(!Q.empty()){
		if(Q.top() < room_width){
			printf("%.16lf\n",Q.top());
			return;
		}
		Q.pop();
	}
	printf("-1\n");
}
void recursive(int array[6],int array_index,int length){
	if(array_index == length){
		for(int i = 0; i < length; i++){
			table[length][table_index[length]][i] = array[i];
		}
		table_index[length]++;
		return;
	}
	bool check[length];
	for(int i = 0; i < length; i++)check[i] = false;
	for(int i = 0; i < array_index; i++){
		check[array[i]] = true;
	}
	for(int i = 0; i < length; i++){
		if(check[i] == false){
			int next_array[6];
			for(int k = 0; k < array_index; k++)next_array[k] = array[k];
			next_array[array_index] = i;
			recursive(next_array,array_index+1,length);
		}
	}
}
void makeTable(){
	for(int length = 2; length <= 6; length++){
		table_index[length] = 0;
		int first_array[6];
		recursive(first_array,0,length);
	}
}
int main(){
	makeTable();
	for(int length = 2; length <= 6; length++){
		char first_buf[12];
		eq_num[length] = 0;
		for(int i = 0; i < table_index[length]; i++){
			makeEquation(table[length][i],0,first_buf,0,0,length-1,length);
		}
	}
	int case_num;
	scanf("%d",&case_num);
	for(int i = 0; i < case_num; i++)func();
	return 0;
}