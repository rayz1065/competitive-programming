from typing import List


class Solution:
    def add(self, r, c, value, amount):
        self.rows[r, value] += amount
        self.cols[c, value] += amount
        self.sqrs[r // 3, c // 3, value] += amount

    def can_set(self, r, c, value):
        return (
            self.rows[r, value]
            == self.cols[c, value]
            == self.sqrs[r // 3, c // 3, value]
            == 0
        )

    def solve(self, board, r, c):
        if c == len(board):
            r += 1
            c = 0
            if r == len(board):
                return True

        if board[r][c] != ".":
            return self.solve(board, r, c + 1)

        for value in self.values:
            if self.can_set(r, c, value):
                board[r][c] = value
                self.add(r, c, value, 1)

                if self.solve(board, r, c + 1):
                    return True

                board[r][c] = "."
                self.add(r, c, value, -1)

        return False

    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        self.values = list(map(str, range(1, 10)))
        self.rows = {(x, value): 0 for x in range(9) for value in self.values}
        self.cols = {(x, value): 0 for x in range(9) for value in self.values}
        self.sqrs = {
            (x, y, value): 0
            for x in range(3)
            for y in range(3)
            for value in self.values
        }

        for r, row in enumerate(board):
            for c, col in enumerate(row):
                if board[r][c] == ".":
                    continue

                self.add(r, c, board[r][c], 1)

        self.solve(board, 0, 0)
