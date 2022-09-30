#include <bits/stdc++.h>

using namespace std;

int main(){
    int N;
    cin >> N;

    long long most_val = -1, s = 0;
    for(int i = 0; i < N; i++){
        int c;
        cin >> c;

        if(most_val < c)
            most_val = c, s+= c;
    }

    cout<<s<<"\n";
}
