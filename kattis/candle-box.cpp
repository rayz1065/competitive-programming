#include <bits/stdc++.h>

using namespace std;

int D, R, T;

bool init(){
    cin >> D >> R >> T;
    return true;
}

int getR(int y){
    return y*(y + 1)/2 - 6;
}

int getT(int y){
    return y*(y + 1)/2 - 3;
}

int solve(){
    int yR = 3 + D;
    while(getR(yR) + getT(yR - D) < R + T)
        yR++;
    return R - getR(yR);
}

int main(){
    init();
    printf("%d\n", solve());
}
