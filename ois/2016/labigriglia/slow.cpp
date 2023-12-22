#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <set>
int righe, colonne;
int griglia[3000][3000];

using namespace std;

int cammina(){
    set<pair<int,pair<int,int> > > FF;
    int movr[]={1,0,-1,0,1,1,-1,-1}, movc[]={0,1,0,-1,1,-1,1,-1};
    int i, j;
    FF.insert({0, {0,0}});
    while(griglia[righe*3-1][colonne*3-1]==1000000&&!FF.empty()){
        i=FF.begin()->second.first;
        j=FF.begin()->second.second;
        FF.erase(FF.begin());
        for(int c=0; c<8; c++){
            if(i+movr[c]<righe*3&&i+movr[c]>=0&&j+movc[c]>=0&&j+movc[c]<colonne*3&&griglia[i+movr[c]][j+movc[c]]>griglia[i][j]){
                if((i+movr[c])/3!=i/3||(j+movc[c])/3!=j/3){
                    if(griglia[i][j]+1<griglia[i+movr[c]][j+movc[c]]){
                        griglia[i+movr[c]][j+movc[c]]=griglia[i][j]+1;
                        FF.insert({griglia[i][j]+1, {i+movr[c], j+movc[c]}});
                    }
                }
                else{
                    griglia[i+movr[c]][j+movc[c]]=griglia[i][j];
                    FF.insert({griglia[i][j], {i+movr[c], j+movc[c]}});
                }
            }
        }
    }
    if(griglia[righe*3-1][colonne*3-1]!=1000000)
        return griglia[righe*3-1][colonne*3-1];
    return -1;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    in>>righe>>colonne;
    bool veleno=false;
    for(int i=0; i<righe; i++){
        int input;
        for(int j=0; j<colonne; j++){
            in>>input;
            if(!veleno&&input>0)
                veleno=true;
            griglia[i*3][j*3]=1000000;
            griglia[i*3][j*3+2]=1000000;
            griglia[i*3+2][j*3]=1000000;
            griglia[i*3+2][j*3+2]=1000000;
            griglia[i*3+1][j*3+1]=0;
            if(input>=8){
                griglia[i*3+1][j*3]=0;
                input-=8;
            }
            else
                griglia[i*3+1][j*3]=1000000;

            if(input>=4){
                griglia[i*3+2][j*3+1]=0;
                input-=4;
            }
            else
                griglia[i*3+2][j*3+1]=1000000;

            if(input>=2){
                griglia[i*3+1][j*3+2]=0;
                input-=2;
            }
            else
                griglia[i*3+1][j*3+2]=1000000;

            if(input==1){
                griglia[i*3][j*3+1]=0;
                input-=8;
            }
            else
                griglia[i*3][j*3+1]=1000000;
        }
    }
    if(!veleno){
        if(righe>colonne)
            out<<righe;
        else
            out<<colonne;
        return 0;
    }
    griglia[0][0]=1;
    out<<cammina();
}
