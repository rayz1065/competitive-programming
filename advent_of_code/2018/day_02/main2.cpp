#include <bits/stdc++.h>
#define MAXN 300

using namespace std;
string ids[MAXN];

int calcolaDifferenze(string a, string b){
    int l = min(a.length(), b.length());
    int S = 0;
    for(int i = 0; i < l; i++)
        S+= (a[i] != b[i]);
    return S;
}

int main(){
    fstream in, out;
    in.open("input2.txt", ios::in);
    out.open("output2.txt", ios::out);

    string S;
    int N = 0;

    while(in >> ids[N++]);

    for(int i = 0; i < N; i++){
        for(int j = i + 1; j < N; j++){
            if(calcolaDifferenze(ids[i], ids[j]) == 1){
                for(int c = 0; c < ids[i].length(); c++){
                    if(ids[i][c] == ids[j][c])
                        out<<ids[i][c];
                }
                return 0;
            }
        }
    }
}
