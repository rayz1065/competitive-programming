from functools import reduce

ADJ_POSITIONS = [
    (0, 1),
    (1, 0),
    (0, -1),
    (-1, 0)
]

BASIN_MAX_HEIGHT = 8

def read_in():
    problem = []
    try:
        while True:
            line = input()
            problem.append([int(x) for x in line])
    except EOFError:
        pass
    return problem

class Solver:
    def __init__(self, problem):
        self.grid = problem
        self.n = len(self.grid)
        self.m = len(self.grid[0])

    def cells(self):
        for r in range(self.n):
            for c in range(self.m):
                yield r, c, self.grid[r][c]

    def in_range(self, r, c):
        return 0 <= r < self.n and \
               0 <= c < self.m

    def adj_cells(self, r, c):
        for dr, dc in ADJ_POSITIONS:
            adj_r, adj_c = r + dr, c + dc
            if self.in_range(adj_r, adj_c):
                yield adj_r, adj_c

    def is_low_point(self, r, c):
        for adj_r, adj_c in self.adj_cells(r, c):
            if self.grid[adj_r][adj_c] <= self.grid[r][c]:
                return False
        return True

    def part_1(self):
        s = 0
        for r, c, _ in self.cells():
            if self.is_low_point(r, c):
                s+= self.grid[r][c] + 1
        return s

    def is_h_part_of_basin(self, h):
        return h <= BASIN_MAX_HEIGHT

    def is_part_of_basin(self, r, c):
        return self.is_h_part_of_basin(self.grid[r][c])

    def ccdfs_rec(self, r, c, basins, cc_id):
        basins[r][c] = cc_id
        for adj_r, adj_c in self.adj_cells(r, c):
            if basins[adj_r][adj_c] is None and self.is_part_of_basin(adj_r, adj_c):
                self.ccdfs_rec(adj_r, adj_c, basins, cc_id)

    def ccdfs(self, r, c, basins, cc_id):
        cells = [(r, c)]

        while len(cells) > 0:
            r, c = cells.pop()
            basins[r][c] = cc_id
            for adj_r, adj_c in self.adj_cells(r, c):
                if basins[adj_r][adj_c] is None and self.is_part_of_basin(adj_r, adj_c):
                    cells.append([adj_r, adj_c])

    def find_basins(self):
        basins = [[None] * self.m for r in range(self.n)]
        cc_count = 0
        for r, c, h_val in self.cells():
            if basins[r][c] is None and self.is_h_part_of_basin(h_val):
                self.ccdfs(r, c, basins, cc_count)
                cc_count+= 1
        return basins

    def part_2(self):
        basins = self.find_basins()
        cc_sizes_map = {}

        for r, c, _ in self.cells():
            basin = basins[r][c]
            if basin is not None:
                cc_sizes_map[basin] = cc_sizes_map.get(basin, 0) + 1

        cc_sizes = list(sorted(cc_sizes_map.values()))
        # multiply the 3 largest sizes
        return reduce(lambda x, y: x * y, cc_sizes[len(cc_sizes) - 3:], 1)

def main():
    problem = read_in()
    solver = Solver(problem)
    print("part_1:", solver.part_1())
    print("part_2:", solver.part_2())

if __name__ == '__main__':
    main()
