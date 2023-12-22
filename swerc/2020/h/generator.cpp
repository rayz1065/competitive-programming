#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n = 10000;

int currentFigurines[MAXN];

int main(){
    srand(time(NULL));
    fstream out;
    out.open("input.txt", ios::out);
    out<<n<<"\n";
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n; j++){
            if(currentFigurines[j] == 0 && rand()%10000 == 0){
                currentFigurines[j]++;
                out<<"+"<<j<<" ";
            }
            else if(currentFigurines[j] == 1 && rand()%100 == 0){
                currentFigurines[j]++;
                out<<"-"<<j<<" ";
            }
        }
        out<<"\n";
    }
    for(int j = 0; j < n; j++)
        if(currentFigurines[j] == 1){
            currentFigurines[j]++;
            out<<"-"<<j<<" ";
        }

    for(int i = 0; i < n; i++){
        out<<rand()%(n + 1)<<"\n";
    }
}
