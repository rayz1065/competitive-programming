#include <bits/stdc++.h>

using namespace std;

char inputTxt[105*105];
int numeri[105];

bool readInt(char str[], int &i, int &S){
    S = 0;
    while(i < 105*105 && str[i] != '\0' && str[i] < '0' || str[i] > '9')
        i++;
    if(i >= 105*105 || str[i] < '0' || str[i] > '9')
        return false;
    while(i < 105*105 && str[i] >= '0' && str[i] <= '9')
        S = S*10 + str[i] - '0', i++;
    return true;
}

int getGcd(int a, int b){
    if(b == 0) return a;
    return getGcd(b, a%b);
}

int main(){
    int T;
    cin >> T;
    cin.ignore();

    for(int t = 0; t < T; t++){
        cin.getline(inputTxt, 105*105);
        int i = 0, N = 0;

        while(readInt(inputTxt, i, numeri[N]))
            N++;

        int maxGcd = 0;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                if(i != j)
                    maxGcd = max(maxGcd, getGcd(numeri[i], numeri[j]));

        cout<<maxGcd<<"\n";
    }
}
