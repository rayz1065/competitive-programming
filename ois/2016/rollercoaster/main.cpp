#include <iostream>
#include <fstream>

using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int H[N];
    for(int i=0; i<N; i++)
        in>>H[i];

    int Caduta, i;
    for(i=0; i+1<N;){
        Caduta=H[i];
        while(i+1<N&&H[i+1]<H[i])
            i++;
        if(i+2<N&&H[i+1]-H[i]>0&&H[i+1]-H[i]==H[i+2]-H[i+1]){
            //cout<<"inizia una risalita motorizzata al punto "<<i<<endl;
            int K=H[i+1]-H[i];
            while(i+1<N&&H[i+1]-H[i]==K)
                i++;
            //cout<<"finisce la risalita al punto "<<i<<endl;
            if(i+1<N&&H[i+1]>=H[i]){
                //cout<<"#INCIDENTE# dopo la risalita non e' possibile raggiungere il pilone\n";
                out<<i;
                return 0;
            }
        }
        else{
            //cout<<"inizia una risalita inerziale al punto "<<i<<". Altezza massima "<<Caduta<<endl;
            while(i+1<N&&H[i]<=H[i+1]&&H[i+1]<Caduta&&!(i+2<N&&H[i]<H[i+1]&&H[i+1]-H[i]==H[i+2]-H[i+1]))
                i++;
            //cout<<"finisce la risalita al punto "<<i<<endl;
            if(i+1<N&&H[i]<=H[i+1]&&H[i+1]>=Caduta){
                //cout<<"#INCIDENTE# durante la salita inerziale l'energia non era sufficiente\n";
                out<<i;
                return 0;
            }
        }
    }
    out<<i;
}
