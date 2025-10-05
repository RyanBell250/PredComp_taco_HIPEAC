#include<iostream>
#include<vector>
struct ans{
  int y0,x0,y1,x1;
  ans(int a,int b,int c,int d){
    y0=a+1;
    x0=b+1;
    y1=c+1;
    x1=d+1;
  }
};
using namespace std;
int main(){
  int h,w;
  vector<ans> an;
  cin >> h >> w;
  int a[h][w];
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      cin >> a[i][j];
    }
  }
  for(int y=0;y<h;y++){
    for(int x=0;x<w-1;x++){
      if(a[y][x]%2!=0){
        an.push_back(ans(y,x,y,x+1));
        a[y][x]--;
        a[y][x+1]++;
      }
    }
  }
  for(int y=0;y<h-1;y++){
    if(a[y][w-1]%2!=0){
      an.push_back(ans(y,w-1,y+1,w-1));
      a[y][w-1]--;
      a[y+1][w-1]++;
    }
  }
  cout << an.size()<<endl;
  for(auto i=an.begin();i!=an.end();i++){
    cout << i->y0<<" "<<i->x0<<" "<<i->y1<<" "<<i->x1<<endl;
  }
}
