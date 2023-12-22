#include <bits/stdc++.h>
#define MAXN 300005
using namespace std;

int main(){
    fstream out;
    out.open("output.txt", ios::out);

    int t = 1;
    out<<t<<"\n";
    while(t--){
        int n = 300000;
        out<<n<<"\n";
        for(int i = 0; i < n; i++)
            out<<rand()%100<<" "<<rand()%100<<"\n";
    }
}
