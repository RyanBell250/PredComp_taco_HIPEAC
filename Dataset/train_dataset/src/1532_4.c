#include <iostream>
#include <string>
using namespace std;
int myhas(string s, int ptr, int a, int b, int c, int d){
  if(s[ptr] == 'a'){ return a; }
  else if(s[ptr] == 'b'){ return b; }
  else if(s[ptr] == 'c'){ return c; }
  else if(s[ptr] == 'd'){ return d; }
  else if(s[ptr] == '['){
    int p = 0;
    if(s[ptr+2] == '['){
      int cnt = 1;
      while(cnt != 0){
	p++;
	if(s[ptr+2+p] == ']'){cnt--;}
	else if(s[ptr+2+p] == '['){cnt++;}
      }
    }
    
    
    int X = myhas(s, ptr+2, a, b, c, d);
    
    int Y = myhas(s, ptr+2+p+1, a, b, c, d);
    if(s[ptr+1] == '+'){
      return (X | Y) & 15;
    }else if(s[ptr+1] == '*'){
      return (X & Y) & 15;
    }else if(s[ptr+1] == '^'){
      return (X ^ Y) & 15;
    }
  }
  
  return 0;
}
int main(void){
  for(;;){
    string S;
    cin >> S;
    if(S == "."){return 0;}
    string P;
    cin >> P;
    int mypassword = stoi(P);
    int md = mypassword % 10;
    int mc = (mypassword / 10) % 10;
    int mb = (mypassword / 100) % 10;
    int ma = (mypassword / 1000);
    int ans = myhas(S,0,ma,mb,mc,md);
    int cnt = 0;
    for(int a = 0 ; a <= 9 ; a++){
      for(int b = 0 ; b <= 9 ; b++){
	for(int c = 0 ; c <= 9 ; c++){
	  for(int d = 0 ; d <= 9 ; d++){
	    if(ans == myhas(S,0,a,b,c,d)){
	      cnt++;
	    }
	  }
	}	
      }
      }
    cout << ans << " " << cnt << endl;
  }
}
