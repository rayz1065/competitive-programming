#include <bits/stdc++.h>
#ifdef _WIN32
    #define getchar_unlocked getchar
#endif // _WIN32
using namespace std;

void readNum(int &N){
    char c = getchar_unlocked();
    N = 0;
    while(c > '/'){
        N = (N * 10) + c - '0';
        c = getchar_unlocked();
    }
}

int main(){
    int N;
    readNum(N);

    int lastStudent = 1, currStudent;
    int senzaPenna = 0;
    for(int i = 0; i < N; i++){
        readNum(currStudent);
        if(currStudent == 0){
            if(lastStudent > 1)
                currStudent++;
        }
        else if(currStudent > 1){
            if(lastStudent < 1){
                lastStudent++;
                currStudent--;
            }
        }
        if(lastStudent < 1)
            senzaPenna++;
        lastStudent = currStudent;
    }
    if(lastStudent < 1)
        senzaPenna++;

    cout<<senzaPenna<<endl;
}
