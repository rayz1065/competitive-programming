#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

std::queue<std::pair<int, int> > coda;
std::vector<std::vector<std::pair<char, int> > > mappa;
using namespace std;

void percorso(int n){
    int r, c;
    int direr[]={-1,-1,-1,0,0,1,1,1}, direc[]={-1,0,1,-1,1,-1,0,1};
    while(!coda.empty()&&mappa[n-1][n-1].second==1000000){
        r=coda.front().first;
        c=coda.front().second;
        coda.pop();
        for(int i=0; i<8; i++){
            if(r+direr[i]>=0&&r+direr[i]<=n-1&&c+direc[i]>=0&&c+direc[i]<=n-1&&mappa[r+direr[i]][c+direc[i]].second>mappa[r][c].second+1&&mappa[r+direr[i]][c+direc[i]].first=='*'){
                coda.push({r+direr[i], c+direc[i]});
                mappa[r+direr[i]][c+direc[i]].second=mappa[r][c].second+1;
            }
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n;
    cin>>n;
    mappa.resize(n);
    for(int i=0; i<n; i++){
        mappa[i].resize(n);
        for(int j=0; j<n; j++){
            cin>>mappa[i][j].first;
            mappa[i][j].second=1000000;
        }
    }
    mappa[0][0].second=1;
    coda.push({0,0});
    percorso(n);
    cout<<mappa[n-1][n-1].second;
}
