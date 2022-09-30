#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt", ios::out);
    int n, q;
    in>>n>>q;
    int ora, cont(0), plz(0), pers[n], treno[n];
    char az;
    set<int> liberi;
    for(int i=0; i<n; i++){
        liberi.insert(i);
        treno[i]=-1;
    }
    for(int i=0; i<q; i++){
        in>>az>>ora;
        if(az=='l'){
            liberi.insert(pers[ora]);
            treno[pers[ora]]=-1;
        }
        else{
            if(liberi.size()>0&&*liberi.begin()<ora){
                int posto=*liberi.begin();
                liberi.erase(liberi.begin());
                treno[posto]=ora;
                pers[ora]=posto;
            }
            else{
                int oora;
                while(treno[ora]!=-1){
                    oora=ora;
                    ora=treno[ora];
                    pers[oora]=oora;
                    treno[oora]=oora;
                    plz++;
                }
                pers[ora]=ora;
                treno[ora]=ora;
                liberi.erase(ora);
            }
        }
    }
    out<<plz;
}
