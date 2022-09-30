#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int righe, colonne;
    cin>>righe>>colonne;
    char papiro[righe][colonne];
    int seriemax=1, serieatt=0, vertmax[colonne]={0};
    for(int i=0; i<righe; i++){
        for(int j=0; j<colonne; j++){
            cin>>papiro[i][j];
            if(papiro[i][j]!=papiro[i][j-1]&&j>0)
                serieatt=0;
            serieatt++;
            if(serieatt>seriemax)
                seriemax=serieatt;
            if(i>0&&papiro[i][j]!=papiro[i-1][j])
                vertmax[j]=1;
            else if(i>0){
                if(vertmax[j]==0)
                    vertmax[j]=2;
                else
                    vertmax[j]++;
            }
            if(vertmax[j]>seriemax)
                seriemax=vertmax[j];
        }
        serieatt=0;
    }
    int i=0, j=0;
    serieatt=0;
    for(int memoj=colonne-1; memoj>=0; memoj--){
        j=memoj;
        for(i=0; i<righe&&j<colonne; i++, j++){
            if(papiro[i][j]!=papiro[i-1][j-1]&&i>0&&j>0)
                serieatt=0;
            serieatt++;
            if(serieatt>seriemax)
                seriemax=serieatt;
        }
        serieatt=0;
        j=memoj;
        for(i=0; i<righe&&j>=0; i++, j--){
            if(papiro[i][j]!=papiro[i-1][j+1]&&i!=0&&j!=colonne-1)
                serieatt=0;
            serieatt++;
            if(serieatt>seriemax)
                seriemax=serieatt;
        }
        serieatt=0;
    }
    for(int memoi=1; memoi<righe; memoi++){
        i=memoi;
        for(j=0; i<righe&&j<colonne; i++, j++){
            if(papiro[i][j]!=papiro[i-1][j-1])
                serieatt=0;
            serieatt++;
            if(serieatt>seriemax)
                seriemax=serieatt;
        }
        serieatt=0;
    }
    for(int memoi=1; memoi<righe; memoi++){
        i=memoi;
        for(j=colonne-1; i<righe&&j>=0; i++, j--){
            if(papiro[i][j]!=papiro[i-1][j+1])
                serieatt=0;
            serieatt++;
            if(serieatt>seriemax)
                seriemax=serieatt;
        }
        serieatt=0;
    }
    cout<<seriemax;
}
