#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int max_size = 200;
ll fibo_memo[105][105];

ll fibo(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    } else if (fibo_memo[n][k] != 0) {
        return fibo_memo[n][k];
    }

    return fibo_memo[n][k] = fibo(n - 1, k) + fibo(n - 1, k - 1);
}

int find_fibo(ll n) {
    int req_fibo = 0;
    while (fibo(2 * (req_fibo + 1), (req_fibo + 1)) <= n) {
        req_fibo += 1;
    }
    return req_fibo;
}

vector<int> fibo_decompose(ll n) {
    vector<int> res;
    while (n) {
        int req_fibo = find_fibo(n);
        ll found = fibo(2 * req_fibo, req_fibo);
        n -= found;
        res.push_back(req_fibo + 1);
    }
    return res;
}

void draw_rectangle(vector<vector<char>> &mat, int top, int left, int height,
                    int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            mat[top + i][left + j] = '.';
        }
    }
}

void draw_square(vector<vector<char>> &mat, int top, int left, int size) {
    draw_rectangle(mat, top, left, size, size);
}

vector<vector<char>> solve(ll n) {
    auto sizes = fibo_decompose(n);
    auto solution = vector<vector<char>>(max_size, vector<char>(max_size, '#'));
    draw_rectangle(solution, 0, 0, max_size, 1);             // general entrance
    draw_rectangle(solution, 0, max_size - 1, max_size, 1);  // general exit

    int row = 2, row_height = 0, col = 2;
    for (auto sz : sizes) {
        if (col + sz >= max_size - 2) {
            // entrances
            draw_rectangle(solution, row + row_height + 1, 2, 1, max_size - 2);
            // exits
            draw_rectangle(solution, row - 2, 0, 1, max_size - 2);
            row += row_height + 5;
            col = 2;
            row_height = 0;
        }
        draw_square(solution, row - 1, col, 1);  // entrance
        draw_square(solution, row, col, sz);     // fibo square
        row_height = max(row_height, sz);
        draw_rectangle(solution, row + sz, col + sz - 1, row_height - sz + 1,
                       1);  // exit
        col += sz + 1;
    }

    // entrances
    draw_rectangle(solution, row + row_height + 1, 2, 1, max_size - 2);
    // exits
    draw_rectangle(solution, row - 2, 0, 1, max_size - 2);

    return solution;
}
