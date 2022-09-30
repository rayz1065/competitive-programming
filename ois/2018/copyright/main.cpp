#include <bits/stdc++.h>

using namespace std;

int strToInt(string anno){
    int S = 0;
    for(int i = 0; i < 4; i++){
        S = S*10 + anno[i] - '0';
    }
    return S;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    int N;
    in>>N;
    string S;
    S.resize(N + 2);
    for(int i = 0; i < N; i++)
        in.get(S[i]);
    in.close();

    int pos = S.find("All rights reserved.");

    int anno = strToInt(S.substr(pos - 6, 4));
    if(anno == 2017){
        if(S[pos - 7] == '-'){
            S[pos - 3] = '8';
        }
        else{
            S.insert(pos - 2, "-2018");
            N+=5;
        }
    }
    else{
        S.insert(pos - 2, ", 2018");
        N+= 6;
    }
    out.open("output.txt", ios::out);
    out<<N;
    for(int i = 0; i < N; i++)
        out<<S[i];
}
