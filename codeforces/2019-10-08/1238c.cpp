#include <bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin >> T;

    for(int t = 0; t < T; t++){
        int h, n;
        cin >> h >> n;

        int currH;
        cin >> currH;

        int S = 0;
        bool falling = false;

        for(int i = 0; i < n - 1; i++){
            cin >> h;

            int diff = currH - h;

            if(!falling){
                falling = true, currH = h;
            }
            else{
                if(diff == 1){
                    falling = false, currH = h;
                }
                else{
                    S++, falling = true, currH = h;
                }
            }
        }
        if(falling && currH > 1)
            S++;

        cout<<S<<"\n";
    }
}
