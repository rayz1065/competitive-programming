#include <bits/stdc++.h>

using namespace std;

int n;

long long somma(int l, int r);
long long subarray_massimo(int l, int r);
long long subarray_minimo(int l, int r);

long long better_sum (int l, int r) {
    int sqrtn = sqrt(n);
    long long total_sum = 0;
    for (int i = l; i <= r; i+= sqrtn) {
        total_sum += somma(i, min(r, i + sqrtn - 1));
    }
    return total_sum;
}

long long all_positive () {
    int sqrtn = sqrt(n);
    for (int i = 0; i < n; i+= sqrtn) {
        if (subarray_minimo(i, min(n - 1, i + sqrtn - 1)) < 0) {
            return -1;
        }
    }
    return better_sum(0, n - 1);
}

long long all_decreasing () {
    int l = 0, r = n - 1;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        int mid_val = somma(mid, mid);
        if (mid_val >= 0) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return better_sum(0, l);
}

long long find_bucket_right_sum (int bucket_l, int bucket_r) {
    // highest sum in the bucket ending at r
    int l = bucket_l, r = bucket_r;
    long long sum = somma(l, r);
    long long max_sum = subarray_massimo(l, r);
    while (l < r) {
        // let's say that the highest subarray starts at mid
        int mid = (l + r + 1) / 2;
        long long curr_sum = somma(mid, r);
        if (curr_sum > )
    }
}

long long generic_sol () {
    // divide into buckets
    int sqrtn = sqrt(n);
    long long total_sum = 0;
    for (int l = 0; l < n; l+= sqrtn) {
        int r = min(n - 1, l + sqrtn - 1);
    }
    return total_sum;
}

long long trova(int N) {
    n = N;
    long long sol = all_positive();
    if (sol >= 0) {
        return sol;
    }

    return all_decreasing();
}
