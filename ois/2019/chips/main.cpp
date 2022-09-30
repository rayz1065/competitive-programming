#include <bits/stdc++.h>
using namespace std;

int A, C;

int valore(int r, int g, int b){
    return A * (r*r + g*g + b*b) + C * min(r, min(g, b));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for(int i = 0; i < T; i++){
        int r, g, b;
        cin >> A >> C >> r >> g >> b;

        int valR = valore(r + 1, g, b), valG = valore(r, g + 1, b), valB = valore(r, g, b + 1);
        if(valR > valG){
            if(valR > valB)
                cout<<"RED\n";
            else
                cout<<"BLUE\n";
        }
        else if(valG > valB)
            cout<<"GREEN\n";
        else
            cout<<"BLUE\n";
    }
}
