#include <iostream>
#include <vector>
using namespace std;

long long trova(int N);

static int N, query = 0, max_length = 0;
static vector<int> v;

long long somma(int a, int b) {
    max_length = max(max_length, b - a + 1);
    query++;
    long long tot = 0;
    for (int i = a; i <= b; i++) tot += v[i];
    return tot;
}

long long subarray_massimo(int a, int b) {
    max_length = max(max_length, b - a + 1);
    query++;
    long long ma = 0;
    for (int i = a; i <= b; i++) {
        for (int j = i; j <= b; j++) {
            long long tot = 0;
            for (int h = i; h <= j; h++) tot += v[h];
            if (tot > ma) ma = tot;
        }
    }
    return ma;
}

long long subarray_minimo(int a, int b) {
    max_length = max(max_length, b - a + 1);
    query++;
    long long mi = 0;
    for (int i = a; i <= b; i++) {
        for (int j = i; j <= b; j++) {
            long long tot = 0;
            for (int h = i; h <= j; h++) tot += v[h];
            if (tot < mi) mi = tot;
        }
    }
    return mi;
}

int main() {
    cin >> N;
    v.resize(N);
    for (int i = 0; i < N; i++) cin >> v[i];
    long long ans = trova(N);
    cout << "Your answer is " << ans << endl;
    cout << "You made " << query << " queries" << endl;
    cout << "The maximum length is " << max_length << endl;
    return 0;
}
