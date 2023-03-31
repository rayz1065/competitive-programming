#include <cstring>
#include <iostream>
#include <string>

using namespace std;

string analizza(int N);

static string secret;
static size_t cnt;

bool test(string qry) {
    cnt += 1;
    return secret.find(qry) != string::npos;
}

int main() {
    cin.exceptions(ios::failbit | ios::badbit);

    // se preferisci leggere e scrivere da file ti basta decommentare le seguenti due righe:
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> secret;

    cnt = 0;
    auto ans = analizza(secret.size());

    if (ans == secret) {
        cout << "Risposta corretta!\n" << cnt << " chiamate a test." << endl;
    } else {
        cout << "Risposta sbagliata!" << endl;
    }

    return 0;
}
