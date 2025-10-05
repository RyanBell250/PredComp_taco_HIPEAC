#include <stdio.h>
#include <algorithm>
 
using namespace std;
 
typedef long long ll;
 
const int B = 1<<17;
 
struct SegmentTree{
	struct vd{
		int v;
		int delay;
		vd():v(0),delay(0){}
	} data[B*2];
	int s;
	void Initialize(int size){
		s=1;
		while(s<size) s<<=1;
	}
	inline void PassDelay(int idx){
		data[idx*2].delay += data[idx].delay;
		data[idx*2+1].delay += data[idx].delay;
		data[idx].delay = 0;
	}
	int b;
	int e;
	int val;
	inline void Update(int idx){
		data[idx].v = max(data[idx*2].v+data[idx*2].delay,data[idx*2+1].v+data[idx*2+1].delay);
	}
	inline void _add(int l,int r,int idx){
		if(e<=l||r<=b)
			return;
		if(b<=l&&r<=e){
			data[idx].delay += val;
			return;
		}
		PassDelay(idx);
		_add(l,(l+r)/2,idx*2);
		_add((l+r)/2,r,idx*2+1);
		Update(idx);
	}
	inline void Add(int _b,int _e,int _val){
		if(_e<=_b)
			return;
		b=_b;
		e=_e;
		val=_val;
		_add(0,s,1);
	}
	inline int GetMax(){
		return data[1].v+data[1].delay;
	}
} seg;
 
struct BinaryIndexedTree{
	int s;
	int data[B];
	void Initialize(int size){
		s=size;
	}
	inline void Add(int idx,int val){
		while(idx<s){
			data[idx]+=val;
			idx += (idx+1)&(-idx-1);
		}
	}
	inline int Get(int idx){
		int ret=0;
		while(idx>=0){
			ret += data[idx];
			idx -= (idx+1)&(-idx-1);
		}
		return ret;
	}
} bit;
 
int as[B];
int bra[B];
int bri[B];
int lbs[B][3];
 
struct ai{
	int a;
	int idx;
	bool operator<(const ai& rhs)const{
		return (a<rhs.a||(a==rhs.a&&idx<rhs.idx));
	}
} srt[B];
 
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&as[i]);
	
	bool sorted=true;
	bool twice=false;
	for(int i=1;i<n;i++){
		if(as[i-1]>as[i])
			sorted=false;
		if(as[i-1]==as[i])
			twice=true;
	}
	if(sorted){
		if(twice)
			printf("0\n");
		else
			printf("1\n");
		return 0;
	}
		
	int brc=0;
	int last=1145141919;
	for(int i=n-1;i>=0;i--)
		if(as[i] < last){
			brc++;
			last = as[i];
		}
	int brn=brc;
		
	seg.Initialize(brn);
	
	last = 1145141919;
	for(int i=n-1;i>=0;i--)
		if(as[i] < last){
			bra[--brc] = as[i];
			bri[brc] = i;
			last = as[i];
		}
		
	for(int i=0;i<n;i++){
		lbs[i][0] = lower_bound(bri,bri+brn,i+1)-bri;
		lbs[i][1] = lower_bound(bra,bra+brn,as[i])-bra;
		lbs[i][2] = lower_bound(bra,bra+brn,as[i]+1)-bra;
	}
	
	for(int i=0;i<n;i++)
		srt[i] = ai{as[i],i};
	sort(srt,srt+n);
	
	bit.Initialize(n);
	ll sum=0;
	for(int i=n-1;i>=0;i--){
		sum += bit.Get(srt[i].idx);
		bit.Add(srt[i].idx,1);
	}
	
	int v=0;
	int h=0;
	int g=0;
	int ans=0;
	for(int i=0;i<n;i++){
		if(i==0||as[v]<as[i]){
			while(v<i){
				seg.Add(lbs[v][0],lbs[v][1],-1);
				seg.Add(lbs[v][0],lbs[v][2],-1);
				v++;
			}
			while(h<n&&srt[h].a<=as[i]){
				seg.Add(lbs[srt[h].idx][0],lbs[srt[h].idx][1],1);
				h++;
			}
			while(g<n&&srt[g].a<as[i]){
				seg.Add(lbs[srt[g].idx][0],lbs[srt[g].idx][2],1);
				g++;
			}
			ans = max(ans,seg.GetMax());
		}
	}
	
	printf("%lld\n",sum-ans);	
}