#include <bits/stdc++.h>
#define MAXN 505
using namespace std;

char nomi[MAXN][25];
pair<double, int> tempiA[MAXN];
pair<double, int> tempiB[MAXN];

int main(){
    int N;
    cin >> N;

    double tempoA, tempoB;
    for(int i = 0; i < N; i++){
        cin >> nomi[i] >> tempoA >> tempoB;
        tempiA[i] = {tempoA, i};
        tempiB[i] = {tempoB, i};
    }

    sort(tempiA, tempiA + N);
    sort(tempiB, tempiB + N);

    double bestTime = 10000;
    int bestFirst = -1;
    for(int i = 0; i < N; i++){
        double time = tempiA[i].first;
        int x = 3;
        for(int j = 0; j < x; j++){
            if(tempiB[j].second == tempiA[i].second)
                x++;
            else
                time+= tempiB[j].first;
        }
        if(time < bestTime){
            bestTime = time;
            bestFirst = i;
        }
    }
    int i = bestFirst;
    cout<<bestTime<<endl<<nomi[tempiA[bestFirst].second]<<endl;
    int x = 3;
    for(int j = 0; j < x; j++){
        if(tempiB[j].second == tempiA[i].second)
            x++;
        else
            cout<<nomi[tempiB[j].second]<<endl;
    }
}
