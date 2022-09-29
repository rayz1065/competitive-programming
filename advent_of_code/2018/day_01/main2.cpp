#include <bits/stdc++.h>
#define MAXN 2000
using namespace std;

int changes[MAXN];
map<int, bool> found;

int main(){
    fstream in, out;
    in.open("input1.txt", ios::in);

    int f = 0, a, N = 0;

    while(in >> a)
        changes[N++] = a;

    found[f] = true;

    while(true){
        for(int i = 0; i < N; i++){
            f+= changes[i];
            if(found[f]){
                cout<<f<<endl;
                return 0;
            }
            found[f] = true;
        }
    }
}
