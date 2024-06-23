class Solution:
    def can_set(self, r, c):
        return (
            not self.col_used[c]
            and not self.diag_used[r + c]
            and not self.rdiag_used[r - c + self.n]
        )

    def add(self, r, c, amount):
        self.col_used[c] += amount
        self.diag_used[r + c] += amount
        self.rdiag_used[r - c + self.n] += amount

    def solve(self, grid, r):
        if r == len(grid):
            self.solutions.append(["".join(row) for row in grid])
            return

        for c in range(len(grid)):
            if self.can_set(r, c):
                self.add(r, c, 1)
                grid[r][c] = "Q"
                self.solve(grid, r + 1)
                grid[r][c] = "."
                self.add(r, c, -1)

    def totalNQueens(self, n: int) -> int:
        self.solutions = []
        self.col_used = [0] * n
        self.diag_used = [0] * (2 * n)
        self.rdiag_used = [0] * (2 * n)
        self.n = n
        grid = [["."] * n for _ in range(n)]

        self.solve(grid, 0)

        return len(self.solutions)
