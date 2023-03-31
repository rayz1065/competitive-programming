#include <bits/stdc++.h>

using namespace std;

int n;
int solution[1005];
struct SweepRequest {
    bool waiting;
    int left;
    int right;
} sweep_requests[1005];
int missing_requests;
int available_sweeps;
int pos;
bool moving_right;
bool chiedi(int K);
void stato();
void sposta();

/**
 * It's not quite pivot but it's similar enough...
 */
void pivot (int i, int j) {
    while (i != j) {
        bool is_left = chiedi(solution[i]);
        if (is_left) {
            i++;
        } else {
            swap(solution[i], solution[j]);
            j--;
        }
    }
}

void move_to (int new_pos) {
    if (pos == new_pos) {
        return ;
    }
    bool need_right = new_pos > pos;
    if (moving_right != need_right) {
        stato();
        moving_right = need_right;
    }
    while (pos != new_pos) {
        sposta();
        if (moving_right) {
            pos++;
        } else {
            pos--;
        }
    }
}

/**
 * divides into buckets half the size each time
 */
void solve (int left, int right) {
    int bucket_size = right - left + 1;
    if (bucket_size == 1) {
        return ;
    }

    // sort the numbers to the left or right of the middle
    int mid = (left + right) / 2;
    // move to the middle
    move_to(mid);
    pivot(left, right);

    // solve the subcases
    solve(left, mid);
    solve(mid + 1, right);
}

void add_sweep_request (int left, int right) {
    if (left < right) {
        missing_requests += 1;
        int mid = (left + right) / 2;
#ifdef DEBUG
        printf("Sweep request added in %d, from %d to %d\n", mid, left, right);
#endif
        assert(!sweep_requests[mid].waiting);
        sweep_requests[mid] = { true, left, right };
    }
}

void check_request () {
    // if there's a requst waiting at this position, run it and divide
    while (sweep_requests[pos].waiting) {
        missing_requests -= 1;
        int left = sweep_requests[pos].left;
        int right = sweep_requests[pos].right;
#ifdef DEBUG
        printf("Found sweep request at %d from %d to %d\n", pos, left, right);
#endif
        sweep_requests[pos].waiting = false;
        pivot(left, right);

        // add the new requests
        add_sweep_request(left, pos);
        add_sweep_request(pos + 1, right);
    }
}

/**
 * Implements a sweeping algorithm, somewhat like disk access queries
 */
void solve_sweep () {
    add_sweep_request(0, n - 1);
    for (int sweep = 0; sweep < available_sweeps && missing_requests; sweep++) {
        bool sweep_right = (sweep % 2 == 0);
        int sweep_limit = sweep_right ? n - 1 : 0;
        int sweep_direction = sweep_right ? +1 : -1;
#ifdef DEBUG
        printf("Moving up to the sweep limit of %d\n", sweep_limit);
#endif
        while (pos != sweep_limit && missing_requests) {
            check_request();
            move_to(pos + sweep_direction);
        }
        check_request();
        // turn around and continue
    }
}

/**
 * divides into sqrt(n) buckets, only requires turning around once
 */
void solve_sqrt_buckets () {
    int bucket_size = sqrt(n);
#ifdef DEBUG
    printf("Bucket size is %d\n", bucket_size);
#endif
    // create sqrt(n) buckets 
    while (true) {
        // try to sort all of the next numbers
        int bucket_start = pos;
        int next_bucket_start = min(pos + bucket_size, n);
        move_to(next_bucket_start - 1);

        int i = pos, j = n - 1;
#ifdef DEBUG
        printf("Moving to before next bucket: %d - 1\n", next_bucket_start);
#endif
        pivot(bucket_start, j);

        if (next_bucket_start == n) {
            break ;
        }
    }

    // move back to the start, sorting on the way
    move_to(n - 1); // should already be here...

    while (pos > 0) {
        move_to(pos - 1); // pos = pos - 1
        // guess number in pos + 1
        for (int i = pos + 1; i >= 0; i--) {
            bool is_left = chiedi(solution[i]);
            if (!is_left) {
                // found it!
                swap(solution[i], solution[pos + 1]);
                break ;
            }
        }
    }
}

void indovina(int N, int A, int B, int C, int H[]) {
    ::n = N;
    pos = 0;
    moving_right = true;
    for (int i = 0; i < n; i++) {
        solution[i] = i;
    }
    available_sweeps = B + 1;
    if (B == 1) {
        // use a solution which turns only once
        solve_sqrt_buckets();
    } else {
        // solution that optimizes the number of sweeps
        solve_sweep();
    }
    // else {
    //     // generic solution
    //     solve(0, n - 1);
    // }
    for (int i = 0; i < N; i++) {
        H[i] = solution[i];
    }
}
