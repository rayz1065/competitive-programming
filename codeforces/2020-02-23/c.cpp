#include <bits/stdc++.h>
#define MAXN 205

using namespace std;

bool used[MAXN];
int permut[MAXN];
int n;

bool assign_num(int c){
    for(int j = 1; j < 2*n; j+= 2){
        if(c > permut[j - 1] && permut[j] == 0){
            permut[j] = c;
            return true;
        }
    }
    return false;
}

bool find_sol(){
    for(int i = 0; i < 2*n; i+= 2)
        used[permut[i]] = true;

    for(int i = 1; i <= 2*n; i++){
        if(!used[i]){
            used[i] = true;
            if(!assign_num(i))
                return false;
        }
    }
    return true;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        memset(used, 0, sizeof(used));
        memset(permut, 0, sizeof(permut));

        cin >> n;
        for(int i = 0; i < 2*n; i+= 2)
            cin >> permut[i];


        if(find_sol()){
            for(int i = 0; i < 2*n; i++)
                cout<<permut[i]<<" ";
            cout<<"\n";
        }
        else{
            cout<<-1<<"\n";
        }
    }
}
