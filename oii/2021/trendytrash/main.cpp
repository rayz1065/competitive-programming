#include <bits/stdc++.h>

#define MAXN 2005

using namespace std;

int n, m;
vector<string> room;
pair<int, int> sorted_rows[2][MAXN];
pair<int, int> sorted_cols[2][MAXN];
bool row_removed[MAXN];
bool col_removed[MAXN];
int rows_trash[2][MAXN];
int cols_trash[2][MAXN];

int solve() {
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      bool trash_before = room[r][c] == '1';
      bool trash_after = !trash_before;
      // to remove trash_after we must first remove trash_before
      rows_trash[trash_after][r]++;
      cols_trash[trash_after][c]++;
    }
  }

  for (int trash = 0; trash < 2; trash++) {
    for (int r = 0; r < n; r++) {
      // add all of the rows to sort them
      sorted_rows[trash][r] = { rows_trash[trash][r], r };
    }
    for (int c = 0; c < m; c++) {
      // add all of the cols to sort them
      sorted_cols[trash][c] = { cols_trash[trash][c], c };
    }
    sort(sorted_rows[trash], sorted_rows[trash] + n);
    sort(sorted_cols[trash], sorted_cols[trash] + m);
  }

  int removed_n[2] = { 0, 0 };
  int removed_m[2] = { 0, 0 };
  int next_rows[2] = { 0, 0 };
  int next_cols[2] = { 0, 0 };
  while (true) {
    bool any_change = 0;
    for (int trash = 0; trash < 2; trash++) {
      if (next_rows[trash] < n) {
        int r = sorted_rows[trash][next_rows[trash]].second;

        if (row_removed[r]) {
          next_rows[trash]++;
          any_change = 1;
        }
        // if we removed enough cols with !trash to expose row r with trash
        else if (removed_m[!trash] >= rows_trash[trash][r]) {
          removed_n[trash]++;
          next_rows[trash]++;
          row_removed[r] = true;
          any_change = 1;
        }
      }
      if (next_cols[trash] < m) {
        int c = sorted_cols[trash][next_cols[trash]].second;

        if (col_removed[c]) {
          next_cols[trash]++;
          any_change = 1;
        }
        // if we removed enough rows with !trash to expose column c with trash
        else if (removed_n[!trash] >= cols_trash[trash][c]) {
          removed_m[trash]++;
          next_cols[trash]++;
          col_removed[c] = true;
          any_change = 1;
        }
      }
    }
    if (!any_change) {
      break ;
    }
  }

  return (n - removed_n[0] - removed_n[1]) * (m - removed_m[0] - removed_m[1]);
}

int pulisci(int n, int m, vector<string> room) {
  ::n = n;
  ::m = m;
  ::room = room;

  return solve();
}
