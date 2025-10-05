#include<iostream>
#include<string>
#include<queue>
#include<map>
#define MAX 4
#define LIMIT 6
#define FORWARD 0
#define BACK 1
#define WEST 0
#define EAST 1
#define BUFFER 40

using namespace std;

class Load{
 public:
  char buffer[BUFFER];
  int head, tail, size;
  Load(){}
  Load( string str ){
    head = tail = BUFFER/2;
    size = 0;
    for ( int i = 0; i < str.size(); i++ ){
      buffer[tail++] = str[i];
      size++;
    }
  }
  
  void intoW( char ch ){ buffer[--head] = ch; size++; }
  void intoE( char ch ){ buffer[tail++] = ch; size++; }
  char fromW(){ char ch = buffer[head]; head++; size--; return ch; }
  char fromE(){ char ch = buffer[tail-1]; tail--; size--; return ch; }
  
  bool operator < ( const Load &l ) const {
    if ( size != l.size ) return size < l.size;
    for ( int i = head, j = l.head; i < tail; i++, j++ ){
      if ( buffer[i] == l.buffer[j] ) continue;
      return buffer[i] < l.buffer[j];
    }
    return false;
  }
  
  bool operator == ( const Load &l ) const {
    if ( size != l.size ) return false;
    for ( int i = head, j = l.head; i < tail; i++, j++ ){
      if ( buffer[i] != l.buffer[j] ) return false;
    }
    return true;
  }
  
  bool operator != ( const Load &l ) const {
    if ( size != l.size ) return true;
    for ( int i = head, j = l.head; i < tail; i++, j++ ){
      if ( buffer[i] != l.buffer[j] ) return true;
    }
    return false;
  }
};

class Station{
 public:
  int nload;
  Load loads[MAX];
  int id;
  
  Station(){}
  Station( int nload): nload(nload){}
  
  bool operator < ( const Station &s ) const {
    for ( int i = 0; i < nload; i++ ){
      if ( loads[i] == s.loads[i] ) continue;
      return loads[i] < s.loads[i];
    }
    return false;
  }
  
  bool operator == ( const Station &s ) const {
    for ( int i = 0; i < nload; i++ ){
      if ( loads[i] != s.loads[i] ) return false;
    }
    return true;
  }
};


Station initial, goal;
int nload;
bool M[MAX][2][MAX][2]; 

map<Station, int> BS; 
map<Station, int> FS; 

Station getNext(Station v, int d, int s, int sd, int t, int td){
  int nd;
  
  if ( sd == WEST ){
    if ( td == WEST ){
      for ( int i = 0; i < d; i++  ){
	v.loads[t].intoW(v.loads[s].fromW());
      }
    } else {
      for ( int i = 0; i < d; i++  ){
	v.loads[t].intoE(v.loads[s].fromW());
      }
    }
  } else {
    if ( td == WEST ){
      nd = v.loads[s].size - d;
      for ( int i = 0; i < nd; i++ ){
	v.loads[t].intoW(v.loads[s].fromE());
      }
    } else {
      nd = v.loads[s].size - d;
      for ( int i = 0; i < nd; i++ ){
	v.loads[t].intoE(v.loads[s].fromE());
      }
    }
  }
  
  return v;
}

int bfs( Station source, map<Station, int> &D, int mode ){
  queue<Station> Q;
  Q.push(source);
  D[source] = 0;
  
  Station u, v;
  
  if ( mode == FORWARD && BS.find(source) != BS.end() ) return BS[source];
  
  while(!Q.empty()){
    u = Q.front(); Q.pop();
    int dist = D[u];
    
    if ( mode == BACK && dist >= 3 ) return 0;
    
    for ( int s = 0; s < nload; s++ ){
      for ( int d = 0; d < u.loads[s].size; d++ ){
	for ( int t = 0; t < nload; t++ ){
	  for ( int sd = 0; sd < 2; sd++ ){
	    for ( int td = 0; td < 2; td++ ){
	      if ( M[s][sd][t][td] ){
		v = getNext(u, d, s, sd, t, td );
		if ( D.find(v) == D.end() ){
		  D[v] = dist + 1;
		  if ( mode == FORWARD ){
		    if ( BS.find(v) != BS.end() ) {
		      return BS[v] + dist + 1;
		    }
		  } 
		  Q.push(v);
		}
	      }
	    }
	  }
	}
      }
    }
  }
  return -1;
}

void compute(){
  BS = map<Station, int>();
  FS = map<Station, int>();
  bfs(goal, BS, BACK);
  cout << bfs(initial, FS, FORWARD) << endl;
}

bool input(){
  int y;
  cin >> nload >> y;
  if ( nload == 0 && y == 0 ) return false;
  
  for ( int i = 0; i < nload; i++ ){
    for ( int j = 0; j < nload; j++ ){
      M[i][WEST][j][WEST] = false;
      M[i][WEST][j][EAST] = false;
      M[i][EAST][j][WEST] = false;
      M[i][EAST][j][EAST] = false;
    }
  }
  int sl, tl; 
  char sd, td; 
  for ( int i = 0; i < y; i++ ){
    cin >> sl >> sd >> tl >> td;
    M[sl][(sd == 'W' ? WEST : EAST)][tl][(td == 'W' ? WEST : EAST)] = true;
    M[tl][(td == 'W' ? WEST : EAST)][sl][(sd == 'W' ? WEST : EAST)] = true;
  }
  
  initial = Station(nload);
  goal = Station(nload);
  
  string train;
  for ( int i = 0; i < nload; i++ ) {
    cin >> train; if ( train == "-" ) train = "";
    initial.loads[i] = Load(train);
  }
  for ( int i = 0; i < nload; i++ ) {
    cin >> train; if ( train == "-" ) train = "";
    goal.loads[i] = Load(train);
  }
  
  return true;
}

int main(){
  while( input() ) compute();
}