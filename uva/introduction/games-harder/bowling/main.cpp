#include <bits/stdc++.h>

using namespace std;

char line[100];
char tosses[100];

int get_value (char x, char prv) {
    if ('0' <= x && x <= '9') {
        return x - '0';
    } else if (x == 'X') {
        return 10;
    } else {
        return 10 - (prv - '0');
    }
}

int main () {
    while (true) {
        cin.getline(line, 100);
        if (line[0] == 'G') {
            break ;
        }
        int tosses_count = 0;
        for (; tosses_count * 2 < strlen(line); tosses_count++) {
            tosses[tosses_count] = line[tosses_count * 2];
        }
        int round_idx = 1;
        int total_score = 0;
        bool already_tossed = false;

        for (int i = 0; i < tosses_count; i++) {
            if (round_idx > 10) {
                break ;
            }
            char prev = i == 0 ? '0' : tosses[i - 1];
            total_score += get_value(tosses[i], prev);

            if (tosses[i] == 'X') {
                total_score += get_value(tosses[i + 1], tosses[i])
                             + get_value(tosses[i + 2], tosses[i + 1]);
            } else if (tosses[i] == '/') {
                total_score += get_value(tosses[i + 1], tosses[i]);
            }

            if (tosses[i] == 'X' or already_tossed) {
                round_idx += 1;
                already_tossed = false;
            } else {
                already_tossed = true;
            }
        }
        cout << total_score << "\n";
    }
}
