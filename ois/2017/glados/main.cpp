#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int righe, colonne, x, y, dire(0), ix, iy;
    in>>righe>>colonne>>x>>y;
    ix=x;
    iy=y;
    char labirinto[righe][colonne];
    for(int i=0; i<righe; i++)
        for(int j=0; j<colonne; j++)
            in>>labirinto[i][j];

    int direx[]={-1,0,1,0}, direy[]={0,1,0,-1};
    do{
        if(labirinto[x+direx[(dire+1)%4]][y+direy[(dire+1)%4]]!='#'){
            dire=(dire+1)%4;
            x+=direx[dire];
            y+=direy[dire];
        }
        else if(labirinto[x+direx[dire]][y+direy[dire]]!='#'){
            x+=direx[dire];
            y+=direy[dire];
        }
        else{
            dire=(dire-1+4)%4;
        }
    }
    while(labirinto[x][y]!='@'&&labirinto[x][y]!='O'&&!((x==ix&&y==iy&&dire==0)));
    if(x==ix&&y==iy&&dire==0)
        out<<"cycling";
    else if(labirinto[x][y]=='@')
        out<<"stuck";
    else if(labirinto[x][y]=='O')
        out<<"free";
}
