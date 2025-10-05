#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
  
  vector<int> close((1<<(5*5))/32, 0);
  vector<int> cls(1000000);
  for (int n; scanf("%d", &n), !(n==0); ){
    vector<vector<int> > pats(33);
    vector<vector<int> > tmp(n, vector<int>(n, 0));
    for (int i=0; i<n; i++){
      for (int j=0; j<n; j++){
	for (int k=i; k<n; k++){
	  for (int l=j; l<n; l++){
	    for (int a=i; a<=k; a++)
	      for (int b=j; b<=l; b++)
		tmp[a][b]=1;
	    int bd=0;
	    for (int a=0; a<n; a++){
	      for (int b=0; b<n; b++){
		bd=(bd<<1)|tmp[a][b];
	      }
	    }
	    pats[__builtin_clz(bd)].push_back(bd);
	    for (int a=i; a<=k; a++)
	      for (int b=j; b<=l; b++)
		tmp[a][b]=0;
	  }
	}
      }
    }
    int bd=0;
    for (int i=0; i<n; i++){
      for (int j=0; j<n; j++){
	int t; scanf("%d", &t);
	bd=(bd<<1)|t;
      }
    }
    int cls_cnt=0, cls_cur=0;
    close[bd>>5]|=(1<<(bd&31));
    cls[cls_cnt++]=bd;
    for (;;){
      int dep=cls[cls_cur]>>25;
      int cbd=cls[cls_cur]&0x1ffffff;
      cls_cur++;
      const vector<int> &ps=pats[__builtin_clz(cbd)];
      int sz=ps.size();
      for (int i=0; i<sz; i++){
	int nbd=cbd^ps[i];
	if (close[nbd>>5]&(1<<(nbd&31)))
	  continue;
	close[nbd>>5]|=(1<<(nbd&31));
	cls[cls_cnt++]=((dep+1)<<25)|nbd;
	if (nbd==0){
	  for (int i=0; i<=dep; i++)
	    printf("myon");
	  puts("");
	  goto _exit;
	}
      }
    }
  _exit:;
    {
      int i=0;
      for (; i+3<cls_cnt; i+=4){
	close[(cls[i+0]&0x1ffffff)>>5]=0;
	close[(cls[i+1]&0x1ffffff)>>5]=0;
	close[(cls[i+2]&0x1ffffff)>>5]=0;
	close[(cls[i+3]&0x1ffffff)>>5]=0;
      }
      for (; i<cls_cnt; i++)
	close[(cls[i]&0x1ffffff)>>5]=0;
    }
  }
  return 0;
}
