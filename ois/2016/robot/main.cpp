#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int righe, colonne;
    int movx[]={-1,0,1,0}, movy[]={0,1,0,-1};
    in>>righe>>colonne;
    char mappa[righe][colonne];
    int passato[righe][colonne][4];
    for(int i=0; i<righe; i++)
        for(int j=0; j<colonne; j++){
            in>>mappa[i][j];
            passato[i][j][0]=INT_MAX;
            passato[i][j][1]=INT_MAX;
            passato[i][j][2]=INT_MAX;
            passato[i][j][3]=INT_MAX;
        }
    int x=0, y=0, dire=1,dist(0);
    while(passato[x][y][dire]>dist&&mappa[x][y]!='X'){
        passato[x][y][dire]=dist;
        //cout<<x<<" "<<y<<" "<<dire<<" "<<mappa[x][y]<<endl;
        if(mappa[x][y]=='+'){
            x+=movx[dire];
            y+=movy[dire];
        }
        else if(mappa[x][y]=='O'){
            x+=movx[dire]*2;
            y+=movy[dire]*2;
            dist++;
        }
        else if(mappa[x][y]=='L'){
            dire=(dire+3)%4;
            x+=movx[dire];
            y+=movy[dire];
        }
        else{
            dire=(dire+1)%4;
            x+=movx[dire];
            y+=movy[dire];
        }
        dist++;
        x=(x+righe)%righe;
        y=(y+colonne)%colonne;
    }
    //cout<<endl<<x<<" "<<y<<" "<<dire<<" "<<mappa[x][y]<<endl;
    if(mappa[x][y]=='X')
        out<<-1;
    else
        out<<dist-passato[x][y][dire];
}
