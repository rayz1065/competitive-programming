#include <bits/stdc++.h>
using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    int a, b, S = 0;
    in>>a;
    for(int i = 1; i < N; i++){
        in>>b;
        S = max(S, abs(b - a));
        a = b;
    }
    out<<S;
}
