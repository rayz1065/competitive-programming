#include <bits/stdc++.h>

using namespace std;

int max_right (int n, vector<int> &a, vector<int> &b) {
    int s = 0;
    int i = 0, j = 0;
    while (i < n && j < n) {
        // first spot available on the right
        while (j < n && a[i] > b[j]) j++;
        if (j < n) s++, i++, j++;
    }
    return s;
}

int min_right (int n, vector<int> &a, vector<int> &b) {
    int s = 0;
    int i = n - 1, j = n - 1;
    while (i < n && j >= 0) {
        // first spot available on the left
        while (j >= 0 && a[i] < b[j]) j--, s++;
        if (j >= 0) i--, j--;
    }
    return s;
}

int direziona(int n, vector<int> a, vector<int> b) {
    int r = max_right(n, a, b);
    int l = min_right(n, a, b);
    return r - l + 1;
}
