#include <bits/stdc++.h>
#define MAXN 125
#define MOD 1000000007

using namespace std;

int N;
long long x;
int carte[MAXN][MAXN];
int memo[MAXN][MAXN][MAXN][MAXN];

int stored_sums_row[MAXN][MAXN][MAXN];
int stored_sums_col[MAXN][MAXN][MAXN];

int get_sum_row(int r, int i, int j){
    if(i == j) return carte[r][i];
    if(stored_sums_row[r][i][j] != INT_MIN) return stored_sums_row[r][i][j];
    return stored_sums_row[r][i][j] = get_sum_row(r, i, j - 1) + carte[r][j];
}

int get_sum_col(int c, int i, int j){
    if(i == j) return carte[i][c];
    if(stored_sums_col[c][i][j] != INT_MIN) return stored_sums_col[c][i][j];
    return stored_sums_col[c][i][j] = get_sum_col(c, i, j - 1) + carte[j][c];
}

int solve(int up, int down, int left, int right){
    if(down < up) return 1;
    if(left > right) return 1;

    if(memo[up][down][left][right] != 0) return memo[up][down][left][right];

    long long games = 1;
    if(get_sum_row(up, left, right)   >= x) games+= solve(up + 1, down, left, right);
    if(get_sum_row(down, left, right) >= x) games+= solve(up, down - 1, left, right);
    if(get_sum_col(left, up, down)    >= x) games+= solve(up, down, left + 1, right);
    if(get_sum_col(right, up, down)   >= x) games+= solve(up, down, left, right - 1);

    return memo[up][down][left][right] = games%MOD;
}

int solve_sub4(int up, int down, int left, int right){
    if(down < up) return 1;
    if(left > right) return 1;
    down-= up, up = 0, right-= left, left = 0;

    if(memo[up][down][left][right] != 0) return memo[up][down][left][right];

    long long games = 1;
    games+= solve_sub4(up + 1, down, left, right);
    games+= solve_sub4(up, down - 1, left, right);
    games+= solve_sub4(up, down, left + 1, right);
    games+= solve_sub4(up, down, left, right - 1);

    return memo[up][down][left][right] = games%MOD;
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> x;
    bool sub4 = (x == 0);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> carte[i][j];
            if(carte[i][j] < 0) sub4 = false;
        }
    }

    for(int i = 0; i <= N; i++)
        for(int j = 0; j <= N; j++)
            fill(stored_sums_col[i][j], stored_sums_col[i][j] + N + 1, INT_MIN),
            fill(stored_sums_row[i][j], stored_sums_row[i][j] + N + 1, INT_MIN);

    if(sub4)
        cout<<solve_sub4(0, N - 1, 0, N - 1)<<"\n";
    else
        cout<<solve(0, N - 1, 0, N - 1)<<"\n";
}
