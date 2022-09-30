#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

std::queue<std::pair<int, int> > FF;
std::vector<std::vector<std::pair<char, int> > > torino;
using namespace std;

int teletrasporto(int righe, int colonne,pair <int,int> arrivo){
    int x,y,mx[]={0,0,-1,1},my[]={-1,1,0,0};
    bool teletr=0;
    while(!FF.empty()){
        x=FF.front().first;
        y=FF.front().second;
        FF.pop();
        if(x==arrivo.first&&y==arrivo.second)
            return torino[x][y].second;
        if(!teletr&&torino[x][y].first=='@')
            for(int i=0; i<righe; i++)
                for(int j=0; j<colonne; j++)
                    if((i!=x||j!=y)&&torino[i][j].first=='@'){
                        FF.push({i,j});
                        teletr=1;
                        torino[i][j].second=torino[x][y].second+1;
                    }
        for(int i=0; i<4; i++){
            if(x+mx[i]>=0&&x+mx[i]<righe&&y+my[i]>=0&&y+my[i]<colonne&&torino[x+mx[i]][y+my[i]].first!='#'&&torino[x][y].second+1<torino[x+mx[i]][y+my[i]].second){
                torino[x+mx[i]][y+my[i]].second=torino[x][y].second+1;
                FF.push({x+mx[i], y+my[i]});
            }
        }
    }
    return -1;
}

int main(){
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int righe, colonne;
    pair <int, int> arrivo;
    cin>>righe>>colonne;
    torino.resize(righe);
    for(int i=0; i<righe; i++){
        torino[i].resize(colonne);
        for(int j=0; j<colonne; j++){
            cin>>torino[i][j].first;
            torino[i][j].second=1000000;
            if(torino[i][j].first=='M')
                arrivo=(make_pair(i,j));
            else if(torino[i][j].first=='C'){
                FF.push({i,j});
                torino[i][j].second=0;
            }
        }
    }
    cout<<teletrasporto(righe, colonne,arrivo);
}
