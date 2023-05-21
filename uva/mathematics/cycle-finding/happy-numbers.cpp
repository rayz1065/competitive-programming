#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> found;

int getSquareDigits(int N){
    int S = 0;
    while(N > 0){
        S+= (N%10)*(N%10);
        N/= 10;
    }
    return S;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin>>N;
    for(int c = 1; c <= N; c++){
        int num;
        cin>>num;
        found.clear();

        int n = num;
        do{
            found[n] = true;
            n = getSquareDigits(n);
        }while(n != 1 && n != num && !found[n]);

        cout<<"Case #"<<c<<": "<<num<<" is a"<<((n == 1)?" H":"n Unh")<<"appy number.\n";
    }
}
