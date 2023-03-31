#define novefatt 362881
#include <iostream>
int ope[novefatt];
int p=0;

int fact(int N){
    if(N==1)
        return 1;
    return N*fact(N-1);
}

void prepara(int N){
    int F=fact(N);
    for(int i=1; i<F; i++){
        if(i%6==0){
            int a=2, K=2;
            while(i%K==0){
                a++;
                K*=a;
            }
            ope[i-1]=a;
        }
        else if(i%2==1)
            ope[i-1]=2;
        else
            ope[i-1]=3;
    }
    ope[fact(N)-1]=N;
}

int ribalta(){
    p++;
    return ope[p-1];
}
