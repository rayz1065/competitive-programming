#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin>>N;

    vector<int> torri;
    for(int i = 0; i < N; i++){
        int h;
        cin>>h;
        if(torri.size() == 0)
            torri.push_back(h);
        else{
            auto hMin = lower_bound(torri.begin(), torri.end(), h + 1);
            if(hMin == torri.end())
                torri.push_back(h);
            else{
                int pos = hMin - torri.begin();
                torri[pos] = h;
            }
        }
    }
    cout<<torri.size();
}
