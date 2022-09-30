#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int partite=(N*(N-1))/2;
    pair<int, int> teams[N+1];
    for(int i=1; i<=N; i++)
        teams[i]={0,i};
    for(int i=0; i<partite; i++){
        int a, b, scoreA, scoreB;
        in>>a>>b>>scoreA>>scoreB;
        if(scoreA>scoreB)
            teams[a].first+=3;
        else if(scoreB>scoreA)
            teams[b].first+=3;
        else{
            teams[a].first+=1;
            teams[b].first+=1;
        }
    }
    for(int i=0; i<N; i++)
    sort(teams+1, teams+N+1);
    for(int i=N; i>0; i--)
        if(teams[i].first>teams[i-1].first){
            out<<teams[i].second<<" "<<teams[i].first;
            return 0;
        }
    out<<teams[0].second<<" "<<teams[0].first;
}
