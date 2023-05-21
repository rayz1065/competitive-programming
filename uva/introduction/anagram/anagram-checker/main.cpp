#include <bits/stdc++.h>
#define ALF 26

using namespace std;

int dictionary_size = 0;
string dictionary[2005];
int dictionary_freqs[2005][ALF];
unordered_map<string, int> dictionary_index;
bool marked[2005];
int freqs[ALF];

vector<vector<int>> anagrams;

bool can_use (int i) {
    if (marked[i]) {
        return false;
    }
    for (int j = 0; j < ALF; j++) {
        if (dictionary_freqs[i][j] > freqs[j]) {
            return false;
        }
    }
    return true;
}

void update_freqs (int i, int multiplier) {
    for (int j = 0; j < ALF; j++) {
        freqs[j] += dictionary_freqs[i][j] * multiplier;
    }
}

bool all_found () {
    for (int j = 0; j < ALF; j++) {
        if (freqs[j]) {
            return false;
        }
    }
    return true;
}

// recursively finds anagrams
void find_anagrams (int i, vector<int> &curr) {
    if (all_found()) {
        anagrams.push_back(curr);
        return ;
    }

    for (; i < dictionary_size; i++) {
        if (can_use(i)) {
            update_freqs(i, -1);
            curr.push_back(i);
            find_anagrams(i + 1, curr);
            curr.pop_back();
            update_freqs(i, +1);
        }
    }
}

bool tc () {
    fill(freqs, freqs + ALF, 0);
    fill(marked, marked + dictionary_size, false);
    anagrams.clear();

    string sentence;
    getline(cin, sentence);
    if (sentence == "#") {
        return false;
    }

    // words within the sentence are marked, so they're not used in anagrams
    string curr_word = "";
    for (auto letter: sentence) {
        if (letter != ' ') {
            curr_word += letter;
            freqs[letter - 'A'] += 1;
        } else {
            if (dictionary_index.find(curr_word) != dictionary_index.end()) {
                marked[dictionary_index[curr_word]] = true;
            }
            curr_word = "";
        }
    }
    if (dictionary_index.find(curr_word) != dictionary_index.end()) {
        marked[dictionary_index[curr_word]] = true;
    }

    vector<int> curr;
    find_anagrams(0, curr);

    for (auto &anagram: anagrams) {
        cout << sentence << " =";
        for (auto i: anagram) {
            assert(!marked[i]);
            cout << " " << dictionary[i];
        }
        cout << "\n";
    }

    return true;
}

int main () {
    while (true) {
        string word;
        cin >> word;
        if (word == "#") {
            break ;
        }
        for (auto letter: word) {
            dictionary_freqs[dictionary_size][letter - 'A'] += 1;
        }
        dictionary_index[word] = dictionary_size;
        dictionary[dictionary_size++] = word;
    }
    getchar(); // clear nl

    while (tc());
}
