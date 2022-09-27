from queue import PriorityQueue

MOVEMENTS = [
    (1, 0),
    (0, 1),
    (-1, 0),
    (0, -1)
]

class CaveMap:
    def __init__(self, grid):
        self.grid = [row.copy() for row in grid]
        self.original_n = len(self.grid)
        self.original_m = len(self.grid[0])
        self.size_multiplier = 1

    @property
    def n(self):
        return self.original_n * self.size_multiplier

    @property
    def m(self):
        return self.original_m * self.size_multiplier

    def cells(self):
        for r in range(self.n):
            for c in range(self.m):
                yield r, c

    def in_range(self, r, c):
        return 0 <= r < self.n and \
               0 <= c < self.m

    def adj_cells(self, r, c):
        for dr, dc in MOVEMENTS:
            new_r, new_c = r + dr, c + dc
            if self.in_range(new_r, new_c):
                yield new_r, new_c

    def get_risk(self, r, c):
        r, r_tile = r % self.original_n, r//self.original_n
        c, c_tile = c % self.original_m, c//self.original_m
        return (self.grid[r][c] + r_tile + c_tile - 1) % 9 + 1

    def extend_grid(self, factor):
        self.size_multiplier = factor

    def djikstra(self, r, c, to_r, to_c):
        ff = PriorityQueue()
        dist = [[self.n * self.m * 10] * self.m for _ in range(self.n)]

        dist[r][c] = 0
        ff.put_nowait((dist[r][c], (r, c)))

        while not ff.empty():
            _, (r, c) = ff.get_nowait()
            for new_r, new_c in self.adj_cells(r, c):
                new_dist = dist[r][c] + self.get_risk(new_r, new_c)
                if new_dist < dist[new_r][new_c]:
                    dist[new_r][new_c] = new_dist
                    ff.put_nowait((new_dist, (new_r, new_c)))
        return dist[to_r][to_c]

def read_in():
    grid = []
    try:
        while True:
            line = input()
            grid.append([int(x) for x in line])
    except EOFError:
        pass
    return CaveMap(grid)

def part_1(problem):
    return problem.djikstra(0, 0, problem.n - 1, problem.m - 1)

def part_2(problem):
    problem.extend_grid(5)
    return problem.djikstra(0, 0, problem.n - 1, problem.m - 1)

def main():
    problem = read_in()
    print("part_1:", part_1(problem))
    print("part_2:", part_2(problem))

if __name__ == '__main__':
    main()
