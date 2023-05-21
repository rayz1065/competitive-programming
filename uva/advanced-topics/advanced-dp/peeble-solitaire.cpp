#include <bits/stdc++.h>
#define MAXDIM 12
using namespace std;

short memo[4100];

int sposta(short disp){
    if(memo[disp]==0){
        int minP=0;
        for(int c=0; c<MAXDIM; c++)
            if(disp==(disp|(1<<c)))
                minP++;
        for(int c=0; c<MAXDIM-2; c++)
            if(disp==(disp|(1<<c))&&disp==(disp|(1<<c+1))&&disp!=(disp|1<<c+2))
                minP=min(minP, sposta(disp&~((1<<c)+(1<<c+1))|(1<<c+2)));

        for(int c=MAXDIM-1; c>1; c--)
            if(disp==(disp|(1<<c))&&disp==(disp|(1<<c-1))&&disp!=(disp|1<<c-2))
                minP=min(minP, sposta(disp&~((1<<c)+(1<<c-1))|(1<<c-2)));

        memo[disp]=minP;
    }
    return memo[disp];
}

int main(){
    int N;
    cin>>N;

    for(int i=0; i<N; i++){
        short disp=0;
        for(int c=0; c<MAXDIM; c++){
            char elem;
            cin>>elem;
            if(elem=='o')
                disp=disp|(1<<c);
        }
        cout<<sposta(disp);
        cout<<endl;
    }
}
