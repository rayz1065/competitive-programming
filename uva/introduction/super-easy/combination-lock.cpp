#include <bits/stdc++.h>

using namespace std;

int a, b, c, d;

bool init(){
    cin >> a >> b >> c >> d;
    if(a == 0 && b == 0 && c == 0 && d == 0)
        return false;
    return true;
}

int main(){
    while(init()){
        int curr = a, S = 0;
        S+= 360*2;
        while(curr != b){
            curr = (curr + 39)%40;
            S+= 9;
        }
        S+= 360;
        while(curr != c){
            curr = (curr + 1)%40;
            S+= 9;
        }
        while(curr != d){
            curr = (curr + 39)%40;
            S+= 9;
        }
        printf("%d\n", S);
    }
}
