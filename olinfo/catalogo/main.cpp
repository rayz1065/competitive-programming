#include <bits/stdc++.h>

using namespace std;

unordered_map<long long int, int> freq;

void aggiungi(long long int id) {
    freq[id]++;
}

void togli(long long int id) {
    freq[id]--;
}

int conta(long long int id) {
    return freq[id];
}
