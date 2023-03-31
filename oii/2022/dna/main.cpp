#include <bits/stdc++.h>

using namespace std;

bool test(string T);

int n;

int find_longest_zero_streak (string prefix, int l, int r) {
    string curr;
    int first_invalid = r - l + 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        curr = prefix + string(mid, '0');
        if (test(curr)) {
            // curr is a valid string
            l = mid + 1;
        } else {
            // curr is not a valid string
            r = mid - 1;
            first_invalid = mid;
        }
    }
    return first_invalid - 1;
}

string compose_solution () {
    int lzs = find_longest_zero_streak("", 0, n);
    int curr_zeros = lzs;
    string sol = string(lzs, '0');

    while (curr_zeros <= lzs && sol.size() < n) {
        // try appending a 1
        int next_bit = 1;
        sol += next_bit + '0';
        if(!test(sol)) {
            // got it wrong, let's hope next time it's fine
            curr_zeros++;
            sol.pop_back();
            sol += (!next_bit) + '0';
        } else {
            // back on track!
            curr_zeros = 0;
        }
    }
    // clean the end of the string
    sol = sol.substr(0, sol.size() - curr_zeros);
    // int ending_zeros = find_longest_zero_streak(sol, 0, lzs);
    // sol = sol + string(ending_zeros, '0');
    while (true) {
        sol += '0';
        if (!test(sol)) {
            sol.pop_back();
            break ;
        }
    }

    curr_zeros = lzs;
    while (sol.size() < n) {
        // find the prefix
        if (curr_zeros == lzs) {
            sol = "1" + sol;
            curr_zeros = 0;
        } else {
            sol = "0" + sol;
            if(!test(sol)) {
                // it wasn't a 0, therefore it was a 1
                sol[0] = '1';
                curr_zeros = 0;
            } else {
                curr_zeros++;
            }
        }
    }

    return sol;
}

string analizza(int N) {
    n = N;
    return compose_solution();
}
