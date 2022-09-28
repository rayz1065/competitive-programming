#include <bits/stdc++.h>
#define MAXN 2005
#define MAXQ 200005
using namespace std;

struct Car {
    int a;
    int b;
    int c;
};
struct Query {
    int pos;
    int time;
};
int n_cars, q_queries;
Car cars[MAXN];
int cars_order[MAXN];
Query queries[MAXQ];
int queries_order[MAXQ];
int sol[MAXQ];
int curr_time;

bool queries_cmp (int i, int j) {
    return queries[i].time < queries[j].time;
}

long long get_dist (int i, int t) {
    return (long long) cars[i].a * t * t + (long long) cars[i].b * t + cars[i].c;
}

bool cars_cmp (int i, int j) {
    long long di = get_dist(i, curr_time), dj = get_dist(j, curr_time);
    return di > dj || (di == dj && i < j);
}

int swaps = 0;

void bubble_sort () {
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i < n_cars - 1; i++) {
            if (!cars_cmp(cars_order[i], cars_order[i + 1])) {
                swap(cars_order[i], cars_order[i + 1]);
                flag = true;
            }
        }
    }
}

void insertion_sort () {
    for (int i = 1; i < n_cars; i++) {
        int memo = cars_order[i];
        int j = i - 1;

        while (j >= 0 && !cars_cmp(cars_order[j], memo)) {
            cars_order[j + 1] = cars_order[j];
            j--;
        }
        cars_order[j + 1] = memo;
    }
}

void find_sols () {
    sort(cars_order, cars_order + n_cars, cars_cmp);
    for (int i = 0; i < q_queries; i++) {
        curr_time = queries[queries_order[i]].time;
        // cout << "Curr time is " << curr_time << "\n";
        int pos = queries[queries_order[i]].pos;
        insertion_sort();
        // sort(cars_order, cars_order + n_cars, cars_cmp);
        sol[queries_order[i]] = cars_order[queries[queries_order[i]].pos];
    }
}

int main () {
#ifndef DEBUG
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
#endif
    cin >> n_cars;
    for (int i = 0; i < n_cars; i++) {
        cin >> cars[i].a >> cars[i].b >> cars[i].c;
        cars_order[i] = i;
    }
    cin >> q_queries;
    for (int i = 0; i < q_queries; i++) {
        cin >> queries[i].pos >> queries[i].time;
        queries_order[i] = i;
        queries[i].pos--;
    }
    sort(queries_order, queries_order + q_queries, queries_cmp);

    find_sols();

    for (int i = 0; i < q_queries; i++) {
        cout << sol[i] + 1 << "\n";
    }
}