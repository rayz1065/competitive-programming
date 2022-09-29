#include <bits/stdc++.h>

using namespace std;

int main(){
    fstream in, out;
    in.open("input2.txt", ios::in);
    out.open("output1.txt", ios::out);

    string S;
    int due = 0, tre = 0;

    while(in >> S){
        sort(S.begin(), S.end());
        bool d = false, t = false;

        int a = 0;
        for(int i = 1; i <= S.length(); i++){
            if(i == S.length() || S[i] != S[a]){
                if(i - a == 2)
                    d = true;
                if(i - a == 3)
                    t = true;
                a = i;
            }
        }
        due+= d, tre+= t;
    }
    cout<<due*tre<<endl;
}
