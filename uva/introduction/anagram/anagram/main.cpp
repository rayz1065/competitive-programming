#include <bits/stdc++.h>

using namespace std;

char lower (char letter) {
    if ('A' <= letter && letter <= 'Z') {
        letter += 'a' - 'A';
    }
    return letter;
}

char upper (char letter) {
    if ('a' <= letter && letter <= 'z') {
        letter += 'A' - 'a';
    }
    return letter;
}

int letter_to_key (char letter) {
    int key = lower(letter) * 2;
    if (letter == lower(letter)) {
        key += 1;
    }
    return key;
}

char key_to_letter (int key) {
    bool is_lower = key % 2 == 1;
    char letter = key / 2;
    if (!is_lower) {
        letter = upper(letter);
    }
    return letter;
}

int main () {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        
        vector<int> word_keys;
        for (auto c: word) {
            word_keys.push_back(letter_to_key(c));
        }

        sort(word_keys.begin(), word_keys.end());

        do {
            for (auto i: word_keys) {
                cout << key_to_letter(i);
            }
            cout << "\n";
        } while(next_permutation(word_keys.begin(), word_keys.end()));
    }
}
