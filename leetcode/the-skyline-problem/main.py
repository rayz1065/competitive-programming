from typing import List
import heapq


class Solution:
    def getSkyline(self, buildings: List[List[int]]) -> List[List[int]]:
        locations = [(x[0], "s", x[2]) for x in buildings] + [
            (x[1], "e", x[2]) for x in buildings
        ]
        locations.sort()

        i = 0
        frequencies = {}
        res = []
        ordering = []

        while i < len(locations):
            x = locations[i][0]
            while i < len(locations) and locations[i][0] == x:
                _, loc_t, height = locations[i]
                if loc_t == "s":
                    frequencies.setdefault(height, 0)
                    frequencies[height] += 1
                    if frequencies[height] == 1:
                        heapq.heappush(ordering, -height)
                else:
                    frequencies[height] -= 1
                    if frequencies[height] == 0:
                        frequencies.pop(height)
                i += 1

            while ordering and -ordering[0] not in frequencies:
                heapq.heappop(ordering)

            height = -ordering[0] if ordering else 0

            if not res or res[-1][1] != height:
                res.append((x, height))

        return res
