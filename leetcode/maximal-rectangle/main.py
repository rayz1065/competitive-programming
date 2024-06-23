from typing import List


class Solution:
    def maximal_with_corner(self, matrix, tl_r, tl_c):
        c = self.right_bounds[tl_r][tl_c]
        best = 0

        for r in range(tl_r, len(matrix)):
            new_c = self.right_bounds[r][tl_c]
            if new_c is None:
                return best
            c = min(c, new_c)
            best = max(best, (r - tl_r + 1) * (c - tl_c + 1))

        return best

    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        self.right_bounds = [[None] * (len(row) + 1) for row in matrix]
        for r, row in enumerate(matrix):
            for c, col in reversed(list(enumerate(row))):
                if col == "0":
                    continue

                right = self.right_bounds[r][c + 1]
                if right is None:
                    right = c

                self.right_bounds[r][c] = right

        best = 0
        for r, row in enumerate(matrix):
            for c, _ in enumerate(row):
                best = max(best, self.maximal_with_corner(matrix, r, c))

        return best
