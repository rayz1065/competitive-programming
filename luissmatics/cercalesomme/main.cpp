#include <bits/stdc++.h>
#define MAXN 10
using namespace std;

fstream in, out;
int N;
int numeri[MAXN];
int somma;

void trovaSomma(int i, int S, int c, vector<int> piu){
    if(i == N){
        S+= c;
        if(S == somma){
            for(int j = 0; j < piu.size(); j++)
                out<<piu[j]<<" ";
            out<<endl;
        }
        return ;
    }

    piu.push_back(i);
    trovaSomma(i + 1, S + c, numeri[i], piu);

    piu.pop_back();
    trovaSomma(i + 1, S, c*10 + numeri[i], piu);

}

int main(){
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> N;
    for(int i = 0; i < N; i++)
        in >> numeri[i];
    in >> somma;

    trovaSomma(1, 0, numeri[0], {});
}
