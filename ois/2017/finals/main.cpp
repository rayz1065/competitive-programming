#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    vector<pair<int,int> > esami;
    for(int i=0; i<N; i++){
        int h, u;
        in>>h>>u;
        esami.push_back({h,u});
    }
    sort(esami.begin(), esami.begin()+N);
    int valenza[N], valmax=1;
    for(int i=N-1; i>=0; i--){
        valenza[i]=0;
        for(int j=i+1; j<N; j++){
            if(valenza[j]>valenza[i]&&(esami[i].first+esami[i].second<esami[j].first)&&(esami[j].first-esami[j].second>esami[i].first))
                valenza[i]=valenza[j];
        }
        valenza[i]++;
        if(valenza[i]>valmax)
            valmax=valenza[i];
    }
    out<<valmax;
}
