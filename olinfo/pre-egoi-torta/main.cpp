#include <bits/stdc++.h>
#pragma GCC optimize("O3")

#define MAXB 1000000000
#define MAXN 10000000
using namespace std;

int n;
long long int total_sum;
vector<int> cake;
int divisors_count = 0;
long long int divisors[50];

void add_divisor (int div) {
    divisors[divisors_count++] = div;
}

void find_divisors () {
    long long int sum = llabs(total_sum);
    if (sum % 2 == 0) {
        add_divisor(2);
        if (sum == 0) {
            return ;
        }
        while (sum % 2 == 0) {
            sum /= 2;
        }
    }
    for (int i = 3; (long long int) i * i <= sum; i+= 2) {
        if (sum % i == 0) {
            while (sum % i == 0) {
                sum /= i;
            }
            add_divisor(i);
        }
    }
    if (sum > 1) {
        add_divisor(sum);
    }
}

int slice_cake () {
    for (int j = 0; j < divisors_count; j++) {
        long long int slice_size = total_sum / divisors[j];
        long long int current_sum = 0;
        int slices_count = 0;
        for (int i = 0; i < n; i++) {
            current_sum += cake[i];
            if (current_sum == slice_size) {
                // cout << "found slice of size " << slice_size << " for division into " << divisors[j] << " slices\n";
                current_sum = 0;
                slices_count++;

                if (slices_count == divisors[j]) {
                    // found the solution
                    return slices_count;
                }
            }
        }
    }
    return -1;
}

int taglia (int n, vector<int> cake) {
    ::n = n;
    ::cake = cake;
    for (int i = 0; i < n; i++) {
        total_sum += cake[i];
    }

    // find the prime divisors of sum
    find_divisors();
    // find the correct slicing
    return slice_cake();
}
