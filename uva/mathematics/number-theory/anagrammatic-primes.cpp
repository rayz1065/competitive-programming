#include <bits/stdc++.h>

using namespace std;

int main(){
    int an[]={2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, 97, 113, 131, 199, 311, 337, 373, 733, 919, 991};
    int N;
    cin>>N;
    while(N!=0){
        bool found=false;
        for(int i=0; i<22&&!found; i++)
            if(N<an[i]){
                found=true;
                if((int)log10(N)==(int)log10(an[i]))
                    cout<<an[i]<<endl;
                else
                    cout<<'0'<<endl;
            }
        if(!found)
            cout<<'0'<<endl;
        cin>>N;
    }
}
