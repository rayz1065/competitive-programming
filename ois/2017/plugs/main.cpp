#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int n, m;
    cin>>n>>m;
    vector <int> presepic;
    vector <int> presebig;
    int memo[n];
    for(int i=0; i<n; i++)
        cin>>memo[i];
    for(int i=0; i<n; i++){
        int tipo;
        cin.ignore(1,'L');
        cin>>tipo;
        if(tipo==10)
            presepic.push_back(memo[i]);
        else
            presebig.push_back(memo[i]);
    }
    int piccole=0, grandi=0, bipasso=0;
    cin.ignore(100,'\n');
    for(int i=0; i<m; i++){
        string tipo;
        cin>>tipo;
        if(tipo=="bipasso")
            bipasso++;
        else if(tipo=="L10")
            piccole++;
        else            //L16
            grandi++;
    }
    int flopsMax=0;
    sort(presepic.begin(), presepic.end(), greater<int>());
    sort(presebig.begin(), presebig.end(), greater<int>());
    int arrp=0, arrb=0;
    for(; piccole>0&&arrp<presepic.size(); piccole--){
        flopsMax+=presepic[arrp];
        arrp++;
    }
    for(; grandi>0&&arrb<presebig.size(); grandi--){
        flopsMax+=presebig[arrb];
        arrb++;
    }
    for(; bipasso>0&&(arrb<presebig.size()||arrp<presepic.size()); bipasso--){
        if(arrb>=presebig.size()){
            flopsMax+=presepic[arrp];
            arrp++;
        }
        else if(arrp>=presepic.size()){
            flopsMax+=presebig[arrb];
            arrb++;
        }
        else if(presepic[arrp]>=presebig[arrb]){
            flopsMax+=presepic[arrp];
            arrp++;
        }
        else{
            flopsMax+=presebig[arrb];
            arrb++;
        }
    }
    cout<<flopsMax;
}
