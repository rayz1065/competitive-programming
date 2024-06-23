from typing import List


class Solution:
    def can_solve(self, dungeon, health):
        distance = {(0, 0): health + dungeon[0][0]}

        for r, row in enumerate(dungeon):
            for c, cell in enumerate(row):
                if (r, c) == (0, 0):
                    continue

                distance[r, c] = -1e9
                if r > 0 and distance[r - 1, c] > 0:
                    distance[r, c] = max(distance[r, c], distance[r - 1, c] + cell)
                if c > 0 and distance[r, c - 1] > 0:
                    distance[r, c] = max(distance[r, c], distance[r, c - 1] + cell)

        return distance[len(dungeon) - 1, len(dungeon[0]) - 1] > 0

    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:
        a, b, s = 1, 2 * len(dungeon) * 1000, None

        while a <= b:
            mid = (a + b) // 2

            if self.can_solve(dungeon, mid):
                s = mid
                b = mid - 1
            else:
                a = mid + 1

        return s
