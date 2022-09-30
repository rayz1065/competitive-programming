#include <bits/stdc++.h>
#define MAXN 1005
using namespace std;

unsigned long long int N, K;
unsigned long long int inizi[MAXN];
unsigned long long int fini[MAXN];

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> N >> K;
    for(int i = 0; i < N; i++){
        in >> inizi[i] >> fini[i];
        fini[i]++;
    }

    sort(inizi, inizi + N);
    sort(fini, fini + N);

    unsigned long long int limSx = 0, limDx = 0, curr = 0, tot = 0, idxInizi = 0, idxFini = 0;
    while(tot < K && idxFini < N){
        while(idxInizi < N && inizi[idxInizi] <= limDx)
            curr++, idxInizi++;
        while(idxFini < N && fini[idxFini] <= limDx)
            curr--, idxFini++;
        if(idxInizi < N){
            limSx = limDx;
            limDx = min(inizi[idxInizi], fini[idxFini]);
        }
        else if(idxFini < N){
            limSx = limDx;
            limDx = fini[idxFini];
        }
        else
            limDx = -1;
        tot+= (limDx - limSx)*curr;
        //cout<<"Intervallo ["<<limSx<<", "<<limDx<<"]: "<<curr<<" -> "<<tot<<endl;
    }
    tot-= (limDx - limSx)*curr;
    //cout<<"curr = "<<curr<<". tot = "<<tot<<endl;
    unsigned long long int a = limSx;
    while(a < limDx){
        unsigned long long int mid = (limDx - a)/2 + a;
        //cout<<a<<" "<<mid<<" "<<limDx<<endl<<"In "<<mid<<": "<<(mid - limSx)*curr<<" < "<<K - tot<<" <= "<<(mid - limSx + 1)*curr<<endl;
        if((mid - limSx)*curr < K - tot && K - tot <= (mid - limSx + 1)*curr){
            out<<mid<<endl;
            return 0;
        }
        else if((mid - limSx)*curr >= K - tot){
            //cout<<(mid - limSx)*curr<<" > "<<K - tot<<"!"<<endl;
            limDx = mid - 1;
        }
        else{
            //cout<<(mid - limSx)*curr<<" < "<<K - tot<<"! D:"<<endl;
            a = mid + 1;
        }
    }
    out<<limDx<<endl;
}
