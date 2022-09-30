#include <bits/stdc++.h>

using namespace std;

class maxQueue{
    vector<pair<int, int> > elements;
private:
    pair<int, int> getMax(){
        int max1 = 0, max2 = 0;
        for(int i = 0; i < elements.size(); i++){
            if(elements[i].second > max2){
                if(elements[i].second >= max1){
                    max2 = max1;
                    max1 = elements[i].second;
                }
                else{
                    max2 = elements[i].second;
                }
            }
        }
        return {max1, max2};
    }
public:
    int k;
    void insertVal(int a, int val){
        elements.push_back({a, val});
        int max1 = val, max2 = 0;
        for(int i = elements.size() - 2; i >= 0; i--){
            if(elements[i].first <= a - k){
                elements.erase(elements.begin() + i);
                continue;
            }
            else if(elements[i].second > max2){
                if(elements[i].second >= max1){
                    max2 = max1;
                    max1 = elements[i].second;
                }
                else{
                    max2 = elements[i].second;
                }
            }
            else if(elements[i].second <= max2)
                elements.erase(elements.begin() + i);
        }
        //cout<<max1<<" "<<max2<<endl;
        //show();
    }
    void show(){
        for(int i = 0; i < elements.size(); i++)
            cout<<elements[i].second<<"("<<elements[i].first<<")"<<((i + 1 < elements.size())?", ":"\n");
    }
    void stampaMassimi(){
        pair<int, int> massimi = getMax();
        cout<<"massimi: "<<massimi.first<<" "<<massimi.second<<endl;
    }
    int dislivello(){
        pair<int, int> massimi = getMax();
        return massimi.first - massimi.second;
    }
} coda;

int main(){
    ios::sync_with_stdio(false);
    int N, K;
    cin>>N>>K;
    coda.k = K;
    for(int i = 0; i < K; i++){
        int val;
        cin>>val;
        coda.insertVal(i, val);
    }
    int S = coda.dislivello();
    for(int i = K; i < N; i++){
        int val;
        cin>>val;
        coda.insertVal(i, val);
        S = min(coda.dislivello(), S);
        //coda.stampaMassimi();
    }
    cout<<S/2;
}
