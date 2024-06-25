from typing import List
from functools import cache


class Solution:
    def in_range(self, r, c):
        return 0 <= r < len(self.matrix) and 0 <= c < len(self.matrix[r])

    @cache
    def solve(self, r, c):
        res = 1

        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            new_r, new_c = r + dr, c + dc
            if (
                not self.in_range(new_r, new_c)
                or self.matrix[new_r][new_c] <= self.matrix[r][c]
            ):
                continue

            res = max(res, self.solve(new_r, new_c) + 1)

        return res

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        self.matrix = matrix

        return max(
            self.solve(r, c)
            for r, row in enumerate(self.matrix)
            for c, _ in enumerate(row)
        )
