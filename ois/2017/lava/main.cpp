#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<std::pair<char, int> > > pavimento;
std::queue<std::pair<int, int> > FF;
using namespace std;

void salvati(int righe, int colonne){
    int x=0, y=0, mx[]={-1,-1,-1,0,0,1,1,1,0,0,-2,2}, my[]={-1,0,1,-1,1,-1,0,1,-2,2,0,0};
    while(!FF.empty()&&pavimento[righe-1][colonne-1].second==1000000){
        x=FF.front().first;
        y=FF.front().second;
        FF.pop();
        for(int i=0; i<12; i++){
            if(x+mx[i]>=0&&x+mx[i]<=righe-1&&y+my[i]>=0&&y+my[i]<=colonne-1&&pavimento[x+mx[i]][y+my[i]].first=='.'&&pavimento[x+mx[i]][y+my[i]].second>pavimento[x][y].second+1){
                FF.push({x+mx[i], y+my[i]});
                pavimento[x+mx[i]][y+my[i]].second=pavimento[x][y].second+1;
            }
        }
    }
}

int main(){
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int righe, colonne;
    cin>>righe>>colonne;
    pavimento.resize(righe);
    for(int i=0; i<righe; i++){
        pavimento[i].resize(colonne);
        for(int j=0; j<colonne; j++){
            cin>>pavimento[i][j].first;
            pavimento[i][j].second=1000000;
        }
    }
    FF.push({0,0});
    pavimento[0][0].second=0;
    salvati(righe, colonne);
    cout<<pavimento[righe-1][colonne-1].second;
}
