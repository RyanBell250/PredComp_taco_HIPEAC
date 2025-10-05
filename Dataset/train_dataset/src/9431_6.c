#include<iostream>
#include<cassert>
using namespace std;
#define DMAX 370
#define SMAX 4096
#define SIZE 16

static const int nextP[9+2][5] = {{0, 1, 2, 4, 8},
                                 {0, 1, 2, 5, 9},
                                 {0, 1, 2, 6, 10},
                                 {-1, -1, -1, -1 -1},
                                 {0, 4, 5, 6, 8},
                                 {1, 4, 5, 6, 9},
                                 {2, 4, 5, 6, 10},
                                 {-1, -1, -1, -1 -1},
                                 {0, 4, 8, 9, 10},
                                 {1, 5, 8, 9, 10},
                                 {2, 6, 8, 9, 10}};

int nday;
int schedule[DMAX][SIZE];
int no_rainy[SIZE];
bool visited[DMAX][11][SMAX];

bool checkFestival(int pos, int day ){
    if ( schedule[day][pos + 0] == 1 ||
        schedule[day][pos + 1] == 1 ||
        schedule[day][pos + 4] == 1 ||
        schedule[day][pos + 5] == 1 ) return true;
    return false;
}

bool check7NoRainy(){
    for ( int i = 0; i < SIZE; i++ ){
        if ( no_rainy[i] >= 7 ) return true;
    }
    return false;
}

int getState(){
    return no_rainy[0] + no_rainy[3]*8 + no_rainy[12]*64 + no_rainy[15]*512;
}

bool recursive( int pos, int day ){
    if ( day == nday ) return true;
    visited[day][pos][getState()] = true;

    int tmp[SIZE];
    for ( int i = 0; i < SIZE; i++ ) tmp[i] = no_rainy[i];

    for ( int n = 0; n < 5; n++ ){
        if ( checkFestival( nextP[pos][n], day+1 ) ) continue;
    
        for ( int i = 0; i < SIZE; i++ ) no_rainy[i] = tmp[i];
    
        for ( int i = 0; i < SIZE; i++ ){
            if ( i == pos || i == pos + 1 || i == pos + 4 || i == pos + 5 ) {
                no_rainy[i] = 0;
            } else no_rainy[i]++;
        }

        if ( check7NoRainy() ) continue;
        if ( visited[day+1][nextP[pos][n]][getState()] ) continue;
    
        if ( recursive( nextP[pos][n], day+1 ) ) return true;
    }

    return false;
}

void compute(){
    for ( int i = 0; i < SIZE; i++ ) no_rainy[i] = 0;
    for ( int i = 0; i < DMAX; i++ ){
        for (int  j = 0; j < 11; j++ ){
            for ( int k = 0; k < SMAX; k++ ) visited[i][j][k] = false;
       }
    }

    if ( !checkFestival( 5, 0 ) && recursive( 5, 0 ) ) cout << 1 << endl;
    else cout << 0 << endl;
}

bool input(){
    cin >> nday;
    if ( nday == 0 ) return false;
    for ( int i = 0; i < nday; i++ ){
        for ( int j = 0; j < SIZE; j++ ) cin >> schedule[i][j];
    }
    for ( int j = 0; j < SIZE; j++ ) schedule[nday][j] = 0;

    return true;
}

int main(){
    while ( input() ) compute();
}