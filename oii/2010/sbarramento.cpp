#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;


int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N,R,C=0;
    in >> N >> R;
    vector<int> riga(N+1,0);
    int colonna, rig;
    for(int i=0; i<N; i++){
        in >> rig >> colonna;
        riga[colonna]++;
        C+=fabs(R-rig);}

    for(int i=1; i<N; i++)
        if(riga[i]<=0){
            riga[i+1]+=riga[i]-1;
            C+=1-riga[i];
            riga[i]=1;
        }
        else if(riga[i]>1){
            riga[i+1]=riga[i+1]+(riga[i]-1);
            C+=riga[i]-1;
            riga[i]=1;
        }
        out << C;
        return 0;
}
