#include <bits/stdc++.h>

using namespace std;

bool visita(int n, int a[]) {
    int i = 0, j = n - 1;
    int time_i = 0, time_j = 0;
    while (i < j) {
        if (time_i < time_j) time_i += a[i], i++;
        else time_j += a[j], j--;
    }
    return time_i == time_j;
}
