#include<iostream>
using namespace std;
string t[2][2][2];
string u[192];
bool used[8];
int n,flg;
int checkch='A'-'a';
bool input();
string ra(string,int);
string rb(string,int);
string rc(string,int);
void dfs(int,int,int);
inline bool check_ch(char x,char y){
  return (x+checkch==y||x-checkch==y);
}
int main(){
  while(input()){
    for(int i=0;i<8;i++)used[i]=false;
    flg=0;
    dfs(0,0,0);
    if(flg)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
  }
  return 0;
}
void dfs(int x,int y,int z){
  
  if(x==2){x=0;y++;}
  if(y==2){y=0;z++;}
  if(x==0&&y==0&&z==2)flg=1;
  for(int j=0;j<8;j++){
    if(used[j])continue;
    for(int i=j*24;i<j*24+24;i++){
      if(flg)return;
      if(x>0)if(check_ch(t[x-1][y][z][2],u[i][3])==false)continue;
      if(y>0)if(check_ch(t[x][y-1][z][4],u[i][1])==false)continue;
      if(z>0)if(check_ch(t[x][y][z-1][0],u[i][5])==false)continue;
      used[j]=true;
      t[x][y][z]=u[i];
      dfs(x+1,y,z);
      used[j]=false;
    }
  }
}
bool input(){
  string in,str,str2;
  n=0;
  for(int i=0;i<8;i++){
    cin>>in;if(in=="0")return false;
    for(int j=0;j<6;j++){
      if(j<4)str=ra(in,j);
      else if(j==4)str=rb(in,1);
      else str=rb(in,3);
      for(int k=0;k<4;k++){
	str2=rc(str,k);
	u[n++]=str2;
      }
    }
  }
  return true;
}
string ra(string str,int x){
  char tmp;
  for(int i=0;i<x;i++){
    tmp=str[3];
    str[3]=str[0];
    str[0]=str[2];
    str[2]=str[5];
    str[5]=tmp;
  }
  return str;
}
string rb(string str,int x){
  char tmp;
  for(int i=0;i<x;i++){
    tmp=str[5];
    str[5]=str[4];
    str[4]=str[0];
    str[0]=str[1];
    str[1]=tmp;
  }
  return str;
}
string rc(string str,int x){
  char tmp;
  for(int i=0;i<x;i++){
    tmp=str[1];
    str[1]=str[2];
    str[2]=str[4];
    str[4]=str[3];
    str[3]=tmp;
  }
  return str;
}
