#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> h(14),a(13);
vector<bool> hf(14);
bool ten(int x, int y);
int main(){
  string s;
  while(cin >>s){
    bool f = false;
    for(int i=0; i<13; i++) a[i] = s[i]-'0';
    for(int i=1; i<=9; i++){
      int lot[10]={0};
      bool ax = true;
      for(int j=0; j<13; j++) h[j] = a[j];
      h[13] = i;
      for(int j=0; j<14; j++){hf[j] = true;lot[h[j]]++;}
      for(int j=1; j<10; j++) if(lot[j]>4) ax = false;
      if(ax){
	sort(h.begin(),h.end());
	if(ten(4,1)){
	  if(f) cout <<" ";
	  cout <<i;
	  f = true;
	}
      }
    }
    if(!f) cout <<"0";
    cout <<endl;
  }
  return 0;
}
bool ten(int x, int y){
  bool f=false;
  if(x == 0 && y == 0) return true;
  for(int i=0; i<14; i++){
    if(hf[i]){
      if(y!=0){
	for(int j=i+1; j<14; j++){
	  if(hf[j] && h[i] == h[j]){
	    hf[i] = hf[j] = false;
	    f|=ten(x,0);
	    if(f) return f;
	    hf[i] = hf[j] = true;
	    break;
	  }
	  else if(h[i]!=h[j]) break;
	}
      }
      if(x!=0){
	for(int j=i+1; j<14; j++){
	  if(hf[j] && h[i] == h[j]){
	    for(int k=j+1; k<14; k++){
	      if(hf[k] && h[i] == h[k]){
		hf[i] =	hf[j] = hf[k] = false;
		f|=ten(x-1,y);
		if(f) return f;
		hf[i] = hf[j] = hf[k] = true;
		break;
	      }
	      else if(h[i]!=h[k]) break;
	    }
	  }
	  else if(h[i]!=h[j]) break;
	}
	for(int j=i+1; j<14; j++){
	  if(hf[j] && h[i]+1 == h[j]){
	    for(int k=j+1; k<14; k++){
	      if(hf[k] && h[i]+2 == h[k]){
		hf[i] =	hf[j] = hf[k] = false;
		f|=ten(x-1,y);
		if(f) return f;
		hf[i] = hf[j] = hf[k] = true;
		break;
	      }
	      else if(h[i]+2<h[k]) break;
	    }
	  }
	  else if(h[i]+1<h[j]) break;
	}
      }
    }
  }
  return f;
}