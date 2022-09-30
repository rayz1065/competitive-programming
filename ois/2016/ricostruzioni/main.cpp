#include <cstdio>
#include <iostream>
#include <set>
#include <queue>
#include <fstream>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n, k, alte;
    in>>n>>k;
    queue<pair<int,int> > monte;
    set<pair<int,int> > ordine;
    for(int i=0; i<k; i++){
        in>>alte;
        monte.push({alte,i});
        ordine.insert({alte,i});
    }
    int altmin=ordine.rbegin()->first-ordine.begin()->first;
    for(int i=k; i<n; i++){
        in>>alte;
        ordine.erase(monte.front());
        monte.pop();
        monte.push({alte,i});
        ordine.insert({alte,i});
        if(ordine.rbegin()->first-ordine.begin()->first<altmin)
            altmin=ordine.rbegin()->first-ordine.begin()->first;
    }
    cout<<altmin;
}
