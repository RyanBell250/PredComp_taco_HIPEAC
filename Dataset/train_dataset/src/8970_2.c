#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=a;i<b;i++)
#define REP(i,b) FOR(i,0,b)
#define PB push_back
#define MP make_pair
	
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,int> pli;

const int Nmax=200000;

int read(){
	int i;
	scanf("%d",&i);
	return i;
}

struct LCNode{
	typedef LCNode *NP;
	NP l,r,p;
	ll v,vsm,w,wsm,lz;
	ll Get(){
		return wsm+vsm*lz;
	}
	int Pos(){
		if(p&&p->l==this)return -1;
		if(p&&p->r==this)return 1;
		return 0;
	}
	void Update(){
		vsm=v;
		wsm=v*w;
		if(l){
			vsm+=l->vsm;
			wsm+=l->Get();
		}
		if(r){
			vsm+=r->vsm;
			wsm+=r->Get();
		}
	}
	void Propagate(){
		w+=lz;
		wsm+=vsm*lz;
		if(l)
			l->lz+=lz;
		if(r)
			r->lz+=lz;
		lz=0;
	}
	void Push(){
		if(Pos())
			p->Push();
		Propagate();
	}
	void Rotate(){
		NP q=p,c;
		if(Pos()==-1){
			c=r;
			r=p;
			p->l=c;
		}else{
			c=l;
			l=p;
			p->r=c;
		}
		if(c)c->p=p;
		p=p->p;
		q->p=this;
		q->Update();
		if(p&&p->l==q)p->l=this;
		if(p&&p->r==q)p->r=this;
	}
	void Splay(){
		Push();
		while(Pos()){
			int a=Pos(),b=p->Pos();
			if(b&&a==b)p->Rotate();
			if(b&&a!=b)Rotate();
			Rotate();
		}
		Update();
	}
	void Expose(){
		for(NP x=this;x;x=x->p)
			x->Splay();
		for(NP x=this;x->p;x=x->p){
			x->p->r=x;
			x->p->Update();
		}
		Splay();
	}
	void Prepare(){
		Expose();
		r=NULL;
		Update();
	}
	NP Find(NP x,ll k,ll d){
		d+=lz;
		ll a=v*(k-(w+d)*2);
		if(a<=0){
			if(r)
				return r->Find(this,k,d);
			else
				return this;
		}else{
			if(l)
				return l->Find(x,k,d);
			else
				return x;
		}
	}
} lc1[Nmax],lc2[Nmax];

vector<pii> tree[Nmax];
ll dep[Nmax];
void dfs(int i,ll d){
	dep[i]=d;
	for(auto c:tree[i])
		dfs(c.first,d+c.second);
}

ll sum0;

pli Calc(int i,int k){
	lc2[i].Prepare();
	int x=lc2[i].Find(NULL,k,0)-lc2;
	lc1[x].Prepare();
	return MP(sum0+dep[x]*k-lc1[x].Get()*2,x);
}

void Solve(){
	int n=read();
	lc1[0]=LCNode{NULL,NULL,NULL,0,0,0,0,0};
	lc2[0]=LCNode{NULL,NULL,NULL,0,0,0,0,0};
	FOR(i,1,n){
		int p=read()-1,d=read();
		tree[p].PB(MP(i,d));
		lc1[i]=LCNode{NULL,NULL,lc1+p,d,0,0,0,0};
		lc2[i]=LCNode{NULL,NULL,lc2+p,1,0,0,0,0};
	}
	dfs(0,0);
	pli mn(0,0);
	REP(i,n){
		sum0+=dep[i];
		lc1[i].Prepare();
		lc1[i].lz++;
		lc2[i].Prepare();
		lc2[i].lz++;
		pli a=Calc(i,i+1);
		pli b=Calc(mn.second,i+1);
		mn=min(a,b);
		printf("%lld\n",mn.first);
	}
}

#ifdef _WIN32
int main(){
	Solve();
}
#else
ll stackNew,stackOrigin;
int main(){
	const int stackSize=(128)*(1<<20);
	void *stackSpace=malloc(stackSize);
	stackNew=ll(stackSpace)+stackSize-1024;
	asm("mov %rsp, stackOrigin");
	asm("mov stackNew, %rsp");
	Solve();
	asm("mov stackOrigin, %rsp");
}
#endif