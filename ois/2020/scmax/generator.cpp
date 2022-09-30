#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int N;

int rand_int(int a, int b){
    return ((double)(rand()%RAND_MAX)/RAND_MAX)*(b - a + 1) + a;
}

int main(){
    srand(time(NULL));
    for(int i = 0; i < 100; i++) rand();
    fstream out;
    out.open("input.txt", ios::out);

    N = 1000;

    out<<N<<"\n";
    for(int i = 0; i < N; i++)
        out << rand_int(1, N)<<" ";
    out<<"\n";
    for(int i = 0; i < N; i++)
        out << rand_int(1, N)<<" ";
}
