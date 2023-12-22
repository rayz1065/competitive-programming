#include <bits/stdc++.h>

using namespace std;

void printBits(int x){
    for(int i = 31; i >= 0; i--)
        cout<<((x&(1<<i))?"1":"0");
    cout<<"\n";
}

bool isLongCat(int x){
    bool foundOne = false;
    int i;
    for(i = 31; !foundOne && i >= 0; i--)
        foundOne = (x&(1<<i));
    while(i >= 0 && (x&(1<<i)))
        i--;
    return (i < 0);
}

int findN(int x){
    bool foundOne = false;
    int i;
    for(i = 31; !foundOne && i >= 0; i--)
        foundOne = (x&(1<<i));
    while(i >= 0 && (x&(1<<i)))
        i--;
    return i + 1;
}

int main(){
    int x;
    cin >> x;

    int opCount = 0;
    vector<int> operations;
    while(!isLongCat(x)){
        int N = findN(x);
        operations.push_back(N);
        opCount++;

        x = x^((1<<N) - 1);

        if(isLongCat(x))
            continue ;
        x++;
        opCount++;
    }

    cout<<opCount<<"\n";
    for(auto i:operations)
        cout<<i<<" ";
    cout<<"\n";
}
