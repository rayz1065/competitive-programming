#include <bits/stdc++.h>
#define MAXN 200005
#define ROW_SIZE 450

using namespace std;

int n, row_count;
bool used[MAXN];
int free_by_row[MAXN / ROW_SIZE + 5];

void josephus_advance(int &row, int &col, int amount) {
    int curr_row_size = min(n - row * ROW_SIZE, ROW_SIZE);

    while (amount && col < curr_row_size) {
        amount -= !used[row * ROW_SIZE + col];
        if (amount) {
            col += 1;
        }
    }

    if (!amount) {
        return;
    }

    for (row = (row + 1) % row_count, col = 0; amount > free_by_row[row];
         row = (row + 1) % row_count) {
        amount -= free_by_row[row];
    }

    josephus_advance(row, col, amount);
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int k;
    cin >> n >> k;
    row_count = (n / ROW_SIZE) + (n % ROW_SIZE > 0);

    for (int row = 0; row < row_count; row++) {
        int curr_row_size = min(n - row * ROW_SIZE, ROW_SIZE);
        free_by_row[row] = curr_row_size;
    }

    int row = 0, col = 0;
    for (int i = 0; i < n; i++) {
        josephus_advance(row, col, 1);  // move to the first available spot
        josephus_advance(row, col, k % (n - i) + 1);  // skip k, stop at k + 1

        used[row * ROW_SIZE + col] = true;
        free_by_row[row] -= 1;
        cout << row * ROW_SIZE + col + 1 << " \n"[i + 1 == n];
    }
}
