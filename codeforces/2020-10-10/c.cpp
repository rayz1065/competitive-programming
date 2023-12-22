#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int streets, n;

int t[MAXN];
int row[MAXN];
int col[MAXN];

vector<int> solByPhotos[MAXN];
int maxPhotos;

void init(){
    cin >> streets >> n;
    for(int i = 1; i <= n; i++)
        cin >> t[i] >> row[i] >> col[i];
    row[0] = 1, col[0] = 1, t[0] = 0;
    for(int i = 0; i < MAXN; i++)
        solByPhotos[i].clear();
    solByPhotos[0].push_back(0);
    maxPhotos = 0;
}

int calcTime(int i, int j){
    return abs(row[i] - row[j]) + abs(col[i] - col[j]);
}

int solve(){
    for(int i = 1; i <= n; i++){
        for(int j = maxPhotos; j >= 0; j--){
            bool found = false;

            for(auto a:solByPhotos[j]){
                if(calcTime(a, i) <= t[i] - t[a]){
                    found = true;
                    break;
                }
            }

            if(found){
                solByPhotos[j + 1].push_back(i);
                maxPhotos = max(maxPhotos, j + 1);
                break;
            }
        }
    }

    return maxPhotos;
}

int main(){
    init();
    cout<<solve()<<"\n";
}
