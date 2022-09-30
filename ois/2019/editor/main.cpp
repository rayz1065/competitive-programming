#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

bool isBold(char c){
    return (c >= 'A' && c <= 'Z');
}

bool isItalic(char c){
    return (c == 'i' || c == 'I');
}

int main(){
    fstream in;
    in.open("input.txt", ios::in);

    int N;
    in >> N;

    bool bold = false, italic = false;
    int S = 0;
    char c;
    for(int i = 0; i < N; i++){
        in >> c;
        if(bold != isBold(c))
            bold = !bold, S+= bold;
        if(italic != isItalic(c))
            italic = !italic, S+= italic;
    }

    cout << S << endl;
}
