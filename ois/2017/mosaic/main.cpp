#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
int A, B, N, finale[5][5], usato[50], tessere[50][10][10];
bool trovato=false, vert[51][50];
std::vector<std::vector<int> > dex;
std::vector<std::vector<int> > down;
using namespace std;

void aggiungi(int riga, int colonna){
    if(colonna==B){
        colonna=0;
        riga++;
        if(riga==B){
            for(int i=0; i<B; i++){
                for(int j=0; j<B; j++)
                    cout<<finale[i][j]<<" ";
                cout<<endl;
            }
            trovato=true;
            return;
        }
        int up=finale[riga-1][colonna];
        for(int a=0; a<down[up].size()&&!trovato; a++){
            if(!usato[down[up][a]]){
                usato[down[up][a]]=true;
                finale[riga][colonna]=down[up][a];
                aggiungi(riga, colonna+1);
                usato[down[up][a]]=false;
            }
        }
        return;
    }
    if(!trovato){
        int sx=finale[riga][colonna-1], up=50;
        if(riga!=0)
            up=finale[riga-1][colonna];
        for(int a=0; a<dex[sx].size(); a++){
            if(!usato[dex[sx][a]]&&vert[up][dex[sx][a]]){
                usato[dex[sx][a]]=true;
                finale[riga][colonna]=dex[sx][a];
                aggiungi(riga, colonna+1);
                usato[dex[sx][a]]=false;
            }
        }
    }
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    in>>A>>B>>N;
    for(int c=0; c<N; c++){
        int input;
        for(int i=0; i<A; i++){
            in>>input;
            for(int j=0; j<A; j++){
                tessere[c][i][A-j-1]=input%10;
                input/=10;
            }
        }
    }

    dex.resize(N+1);
    for(int a=0; a<N; a++){
        for(int b=0; b<N; b++){
            bool maybe=(a!=b);
            for(int i=0; i<A&&maybe; i++)
                if(tessere[a][i][A-1]!=tessere[b][i][0])
                    maybe=false;
            if(maybe)
                dex[a].push_back(b);
        }
    }
    for(int b=0; b<N; b++)
        dex[N].push_back(b);

    down.resize(N);
    for(int a=0; a<N; a++){
        for(int b=0; b<N; b++){
            bool maybe=(a!=b);
            for(int j=0; j<A&&maybe; j++)
                if(tessere[a][A-1][j]!=tessere[b][0][j])
                    maybe=false;
            if(maybe){
                vert[a][b]=true;
                down[a].push_back(b);
            }
            else
                vert[a][b]=false;
        }
    }

    for(int i=0; i<N; i++)
        vert[50][i]=true;

    for(int b=0; b<N; b++)
        dex[N].push_back(b);

    for(int i=0; i<N; i++)
        usato[i]=false;

    for(int i=0; i<N&&!trovato; i++){
        finale[0][0]=i;
        usato[i]=true;
        aggiungi(0,1);
        usato[i]=false;
    }
}
