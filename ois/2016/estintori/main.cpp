#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

std::vector<std::vector<char> > mappa;
std::queue<std::pair<int,int> > muri;
std::queue<std::pair<int,int> > stanza;
int mancanti(0);
using namespace std;

void cercaesti(){
    int movx[]={0,1,1}, movy[]={1,0,1}, x=stanza.front().first, y=stanza.front().second;
    bool estintore=false;
    if(mappa[x][y]=='@')
        estintore=true;
    mappa[x][y]='V';
    while(!stanza.empty()){
        x=stanza.front().first;
        y=stanza.front().second;
        stanza.pop();
        for(int c=0; c<3; c++){
            if(mappa[x+movx[c]][y+movy[c]]=='@'){
                estintore=true;
                stanza.push({x+movx[c],y+movy[c]});
                mappa[x+movx[c]][y+movy[c]]='V';
            }
            else if(mappa[x+movx[c]][y+movy[c]]=='.'){
                stanza.push({x+movx[c],y+movy[c]});
                mappa[x+movx[c]][y+movy[c]]='V';
            }
        }
    }
    if(!estintore)
        mancanti++;
}

int ricerca(int righe, int colonne){
    muri.push({0,0});
    int movx[]={0,1,1}, movy[]={1,0,1}, x, y;
    while(!muri.empty()){
        x=muri.front().first;
        y=muri.front().second;
        muri.pop();
        for(int c=0; c<3; c++){
            if(x+movx[c]<righe&&y+movy[c]<colonne){
                if(mappa[x+movx[c]][y+movy[c]]=='#'){
                    muri.push({x+movx[c], y+movy[c]});
                    mappa[x+movx[c]][y+movy[c]]='V';
                }
                else if(mappa[x+movx[c]][y+movy[c]]=='.'||mappa[x+movx[c]][y+movy[c]]=='@'){
                    stanza.push({x+movx[c],y+movy[c]});
                    cercaesti();
                }
            }
        }
    }
}


int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int righe, colonne;
    in>>righe>>colonne;
    mappa.resize(righe);
    for(int i=0; i<righe; i++){
        mappa[i].resize(colonne);
        for(int j=0; j<colonne; j++)
            in>>mappa[i][j];
    }
    ricerca(righe, colonne);
    out<<mancanti;
}
