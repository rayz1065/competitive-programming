#include <bits/stdc++.h>
#define MAXL 100000
using namespace std;

int segmenti[3][MAXL];


int main(){
    ios::sync_with_stdio(false);

    int N = 3;

    string S, comp;
    cin >> S;
    comp+= S[0];
    int c = 0;

    for(int i = 0; i < S.length(); i++){
        if(S[i] != comp.back()){
            c++;
            comp+= S[i];
        }
        segmenti[0][c]++;
    }

    int numeroComponenti = comp.length();

    for(int a = 1; a < 3; a++){
        cin >> S;
        c = 0;
        for(int i = 0; i < S.length(); i++){
            if(S[i] != comp[c]){
                c++;
                if(c == numeroComponenti || S[i] != comp[c]){
                    cout<<"IMPOSSIBLE\n";
                    return 0;
                }
            }
            segmenti[a][c]++;
        }
    }
    int dimSegmenti[3];

    for(int c = 0; c < comp.length(); c++){
        for(int a = 0; a < 3; a++)
            dimSegmenti[a] = segmenti[a][c];
        sort(dimSegmenti, dimSegmenti + 3);

        for(int i = 0; i < dimSegmenti[1]; i++)
            cout<<comp[c];
    }
    cout<<endl;
}
