#include <vector>
using namespace std;

int trova_massimo(int N, vector<int> V) {
    int s = V[0];
    
    for (int i = 0; i < N; i++) {
        s = max(s, V[i]);
    }

    return s;
}
