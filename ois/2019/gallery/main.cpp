#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

typedef pair<int, int> pii;

int N;
set<pii> nodi;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> N;
    int xMin = 1000005, xMax = 0;

    for(int i = 0; i < N; i++){
        int x, y;
        in >> x >> y;
        nodi.insert({x, y});
        xMin = min(xMin, x);
        xMax = max(xMax, x);
    }

    for(auto i:nodi){
        if(nodi.count({xMax + xMin - i.first, i.second}) == 0){
            cout<<"NO\n";
            return 0;
        }
    }
    cout<<"YES\n";
    return 0;
}
