#include <bits/stdc++.h>
#define MAXN 30000000
#define MAXL 10
#define DEBUGMODE false
using namespace std;

int ricette[MAXN] = {3, 7};
int digits[MAXL];
int a = 0, b = 1;
int N = 2, L;

bool checkDigits(int firstPos){
    for(int i = 0; i < L && i < MAXN; i++){
        if(ricette[i + firstPos] != digits[i])
            return false;
    }
    return true;
}

int main(){
    fstream in, out;
    in.open("input14.txt", ios::in);
    out.open("output14.txt", ios::out);

    char inputTxt[10];
    in.getline(inputTxt, 10);

    L = strlen(inputTxt);

    int S = 0;
    for(int i = 0; i < L; i++){
        S = (S*10 + inputTxt[i] - '0'); ///   prima parte
        digits[i] = inputTxt[i] - '0';  /// seconda parte
    }

    while(N + 2 < MAXN){
        int newRec = ricette[a] + ricette[b];
        if(newRec < 10)
            ricette[N++] = newRec%10;
        else{
            ricette[N++] = (newRec/10)%10;
            ricette[N++] = newRec%10;
        }
        a = (a + ricette[a] + 1)%N;
        b = (b + ricette[b] + 1)%N;
        if(DEBUGMODE){
            for(int i = 0; i < N; i++){
                if(i != a && i != b)
                    cout<<" ";
                if(i == a)
                    cout<<"(";
                if(i == b)
                    cout<<"[";
                cout<<ricette[i];
                if(i == b)
                    cout<<"]";
                if(i == a)
                    cout<<")";
                if(i != a && i != b)
                    cout<<" ";
            }
            cout<<endl;
        }
    }

    for(int i = S; i < S + 10; i++)
        out<<ricette[i];
    out<<endl;
    int sol = 0;
    while(sol + L < N && checkDigits(sol) == false){
        sol++;
    }
    if(checkDigits(sol) == false){
        cout<<"Soluzione non trovata\n";
        return 0;
    }
    cout<<sol<<endl;
    out<<sol<<endl;
}
