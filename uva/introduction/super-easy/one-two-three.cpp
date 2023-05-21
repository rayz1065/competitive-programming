#include <bits/stdc++.h>

using namespace std;

int main(){
    int N;
    cin>>N;
    string word;
    for(int i=0; i<N; i++){
        cin>>word;
        if(word.size()==5)
            cout<<3<<endl;
        else{
            string one="one";
            int err=0;
            for(int i=0; i<3; i++){
                if(word[i]!=one[i])
                    err++;
            }
            if(err<=1)
                cout<<1<<endl;
            else
                cout<<2<<endl;
        }
    }
}
