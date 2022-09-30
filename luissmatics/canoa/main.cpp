#include <bits/stdc++.h>

using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    set <pair<double, int> > best;
    int N, K;
    in >> N >> K;

    for(int i = 0; i < N; i++){
        int peso, forza;
        in >> forza >> peso;
        best.insert({-(forza - (peso*3)/2), i + 1});
    }

    for(int i = 0; i < K; i++){
        out<<best.begin()->second<<endl;
        best.erase(best.begin());
    }
}
