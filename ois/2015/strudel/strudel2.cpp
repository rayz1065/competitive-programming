#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int mando[N], diff[N+1];
    for(int i=0; i<N; i++)
        in>>mando[i];
    diff[0]=0;
    int fettamax(1);
    set<pair<int, int> > minori;
    set<pair<int, int> >::iterator it;
    for(int i=1; i<=N; i++){
        int cannella;
        in>>cannella;
        diff[i]=diff[i-1]-mando[i-1]+cannella;
        minori.insert({diff[i], i});
        it=minori.begin();
        while(it->second!=i){
            if(i-it->second>fettamax)
                fettamax=i-it->second;
            it++;
        }
    }
    out<<fettamax;
}
