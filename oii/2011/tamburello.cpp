#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;
int N;
int B[MAXN];

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in>>N;

    for(int i = 0; i < N; i++)
        in>>B[i];

    for(int periodo = 1; periodo < N; periodo++){
        if(N % periodo != 0)
            continue;
        bool funziona = true;
        for(int j = periodo; j < N; j++)
            if(B[j] != B[j%periodo])
                funziona = false;
        if(funziona){
            for(int i = 0; i < periodo; i++)
                out<<B[i]<<" ";
            return 0;
        }
    }
    out<<2;
}
