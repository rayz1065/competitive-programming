#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    map<string, int> freq;
    cin >> n;

    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        freq[s]+= 1;
    }
    int k = 0;

    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        if(freq[s] > 0){
            freq[s]-= 1;
            k+= 1;
        }
    }
    cout<<k<<"\n";
}
