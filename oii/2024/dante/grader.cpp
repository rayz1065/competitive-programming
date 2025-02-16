#include <iostream>
#include <vector>

using namespace std;

int rimembra(int N, int K, vector<int> V);

int main(){
    int N, K; cin >> N >> K;

    vector<int> V(N);
    for(int &x: V) cin >> x;

    cout << rimembra(N, K, V) << "\n";
}
