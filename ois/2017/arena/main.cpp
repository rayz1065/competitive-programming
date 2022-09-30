#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, E, L;
    in>>N>>E>>L;
    int death=0, player[N];
    for(int i=0; i<N; i++)
        player[i]=L;
    int a,b;
    char ev;
    for(int i=0; i<E; i++){
        in>>a>>ev;
        if(ev=='e'){
            death++;
            player[a]++;
        }
        else{
            in>>b;
            player[b]--;
        }
    }
    int alive(0);
    for(int i=0; i<N; i++){
        if(player[i]>death)
            alive++;
    }
    cout<<alive;
}
