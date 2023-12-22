#include <bits/stdc++.h>
#define MAXN 10005

using namespace std;

int n;
int sol[MAXN];
int currGreatest = 0;

int makeQuery(int x, int y){
    cout<<"? "<<x + 1<<" "<<y + 1<<"\n";
    cout.flush();

    int k;
    cin >> k;
    return k;
}

void printSolution(){
    cout<<"! ";
    for(int i = 0; i < n; i++)
        cout<<sol[i]<<" ";
    cout<<"\n";
    cout.flush();
}

void testPair(int x, int y){
    int a = makeQuery(x, y);
    int b = makeQuery(y, x);

    if(a > b){
        swap(a, b);
        swap(x, y);
    }
    currGreatest = x;
    sol[y] = b;
}

int main(){
    cin >> n;
    if(n != 1){
        testPair(0, 1);
        for(int i = 2; i < n; i++){
            testPair(currGreatest, i);
        }
    }
    sol[currGreatest] = n;

    printSolution();
}
