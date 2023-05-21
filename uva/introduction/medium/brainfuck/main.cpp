#include <bits/stdc++.h>
#define MEMORY_SIZE 100
#define MAX_VALUE 256

using namespace std;

int memory[MEMORY_SIZE + 5];

void solve () {
    fill(memory, memory + MEMORY_SIZE, 0);
    int pointer = 0;
    string instructions;
    cin >> instructions;

    for (int i = 0; i < (int) instructions.size(); i++) {
        char c = instructions[i];
        switch (c)
        {
        case '>':
            pointer = (pointer + 1) % MEMORY_SIZE;
            break;
        case '<':
            pointer = (pointer - 1 + MEMORY_SIZE) % MEMORY_SIZE;
            break;
        case '-':
            memory[pointer] = (memory[pointer] - 1 + MAX_VALUE) % MAX_VALUE;
            break;
        case '+':
            memory[pointer] = (memory[pointer] + 1) % MAX_VALUE;
            break;
        default:
            break;
        }
    }
}

string to_hex (int i) {
    string s = "";
    string hex_digits = "0123456789ABCDEF";
    while (i > 0) {
        s += hex_digits[i % 16];
        i /= 16;
    }
    while (s.size() < 2) {
        s += '0';
    }
    reverse(s.begin(), s.end());
    return s;
}

int main () {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve();
        cout << "Case " << i << ": ";
        for (int j = 0; j < MEMORY_SIZE; j++) {
            cout << to_hex(memory[j]) << " \n"[j + 1 == MEMORY_SIZE];
        }
    }
}
