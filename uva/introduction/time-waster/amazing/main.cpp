#include <bits/stdc++.h>
#define MOV 4

using namespace std;

int n, m;
vector<vector<bool>> grid;
int mov_r[] = {0, 1, 0, -1};
int mov_c[] = {1, 0, -1, 0};

inline bool is_wall(int r, int c) {
    return r < 0 || r >= n || c < 0 || c >= m || grid[r][c];
}

string right_justify(int n, int l) {
    string res = "";
    do {
        res.push_back((n % 10) + '0');
        n /= 10;
    } while (n);

    while (res.size() < l) {
        res.push_back(' ');
    }
    reverse(res.begin(), res.end());

    return res;
}

vector<vector<int>> visit() {
    vector<vector<int>> visited(n, vector<int>(m, 0));

    int start_r = n - 1, start_c = 0;
    int last_r = start_r, last_c = start_c;
    int r = start_r, c = start_c, dire = 0;
    while (true) {
        if (last_r != r || last_c != c) {
            visited[last_r][last_c] += 1;
            last_r = r, last_c = c;
            if (r == start_r && c == start_c) {
                break;
            }
        }
        if (visited[r][c] > 4) {
            exit(1);
        }
        int right_dire = (dire + 1) % 4;
        int right_r = r + mov_r[right_dire], right_c = c + mov_c[right_dire];
        if (!is_wall(right_r, right_c)) {
            dire = right_dire, r = right_r, c = right_c;
            continue;
        }
        int new_r = r + mov_r[dire], new_c = c + mov_c[dire];
        if (is_wall(new_r, new_c)) {
            dire = (dire + 3) % 4;
            continue;
        }
        r = new_r, c = new_c;
    }

    return visited;
}

bool tc() {
    cin >> n >> m;
    if (n == 0) {
        return false;
    }

    grid.resize(n);
    for (int i = 0; i < n; i++) {
        grid[i].resize(m);

        string line;
        cin >> line;
        for (int j = 0; j < m; j++) {
            grid[i][j] = line[j] == '1';
        }
    }

    auto visited = visit();

    vector<int> results(5, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            results[visited[i][j]] += !is_wall(i, j);
        }
    }

    for (int i = 0; i < 5; i++) {
        cout << right_justify(results[i], 3);
    }
    cout << "\n";

    return true;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (tc());
}
