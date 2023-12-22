#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int numeri[MAXN];
int lisOfSize[MAXN];
int lastElementIdx[MAXN];
int goesTo[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while(cin >> N){
        for(int i = 0; i < N; i++)
            cin >> numeri[i];

        fill(lisOfSize, lisOfSize + N, INT_MAX/2);
        int maxLisSize = -1;
        for(int i = 0; i < N; i++){
            auto ite = lower_bound(lisOfSize, lisOfSize + N, numeri[i]);
            if(*ite > numeri[i]){
                *ite = numeri[i];
                int currLisSize = ite - lisOfSize;
                maxLisSize = max(maxLisSize, currLisSize);
                if(currLisSize == 0)
                    goesTo[i] = -1;
                else
                    goesTo[i] = lastElementIdx[currLisSize - 1];
                lastElementIdx[currLisSize] = i;
            }
        }

        cout<<maxLisSize + 1<<endl;
        int p = lastElementIdx[maxLisSize];
        stack<int> sol;
        while(p >= 0){
            sol.push(p);
            p = goesTo[p];
        }
        while(!sol.empty()){
            cout<<sol.top()<<" ";
            sol.pop();
        }
        cout<<endl;
    }
}
