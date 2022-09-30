#include <bits/stdc++.h>

using namespace std;

int solve(int first_neg, int last_pos){
    return (first_neg == -1 || last_pos == -1 || first_neg >= last_pos) ? -1 : last_pos - first_neg + 1;
}

int main(){
    int N;
    cin >> N;

    int first_neg = -1, last_pos = -1;
    for(int i = 0; i < N; i++){
        int c;
        cin >> c;
        if(c <= 5 && first_neg == -1)
            first_neg = i;
        if(c > 5)
            last_pos = i;
    }

    cout<<solve(first_neg, last_pos)<<"\n";
}
