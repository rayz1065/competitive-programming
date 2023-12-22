#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int pos[MAXN];

int main(){
    int T;
    cin >> T;

    for(int t = 0; t < T; t++){
        int N, R;
        cin >> N >> R;

        for(int i = 0; i < N; i++)
            cin >> pos[i];

        sort(pos, pos + N);
        int pushedToLeft = 0, rightDeath = INT_MAX;

        int shots = 0, ind = N - 1;

        while(ind >= 0 && rightDeath > pushedToLeft){
            // shoot rightmost monster
            if(pos[ind] <= pushedToLeft)
                break ;
            rightDeath = pos[ind];
            shots++;
            pushedToLeft+= R;
            while(ind >= 0 && pos[ind] >= rightDeath)
                ind--;
        }

        cout<<shots<<"\n";
    }
}
