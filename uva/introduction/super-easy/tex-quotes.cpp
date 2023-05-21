#include <bits/stdc++.h>
#define MAXL 100000

using namespace std;

int main(){
    char c;
    bool inQuotes = false;
    while(c = getchar()){
        if(c == EOF)
            return 0;
        if(c == '"'){
            cout<<((inQuotes)?"''":"``");
            inQuotes = !inQuotes;
        }
        else
            cout<<c;
    }
}
