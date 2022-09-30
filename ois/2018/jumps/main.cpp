#include <bits/stdc++.h>

using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;

    map<string, i> parole[N];
    vector<int> albero[N];
    for(int i=0; i<N; i++){
        string word;
        in>>word;
        parole[word] = i;
    }

    for(int i=0; i<N; i++){
        for(int c=0; c<parole[i])
    }
}
