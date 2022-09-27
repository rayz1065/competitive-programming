def read_in():
    grid = []
    try:
        while True:
            line = input()
            grid.append([int(x) for x in line])
    except EOFError:
        pass
    return OctopusGrid(grid)

class OctopusGrid:
    def __init__(self, grid):
        self.n = len(grid)
        self.m = len(grid[0])
        self.grid = grid
        assert all(len(row) == self.m for row in self.grid)

    def __str__(self):
        return '\n'.join(''.join(str(cell) for cell in row) for row in self.grid) + '\n'

    def cells(self):
        for r in range(self.n):
            for c in range(self.m):
                yield r, c, self.grid[r][c]

    def in_range(self, r, c):
        return 0 <= r < self.n and 0 <= c < self.m

    def neighbors(self, r, c):
        for dr in range(-1, 2):
            for dc in range(-1, 2):
                if dr == 0 and dc == 0:
                    # same cell
                    continue
                new_r, new_c = r + dr, c + dc
                if self.in_range(new_r, new_c):
                    yield new_r, new_c

    def increment_all(self, inc_am = 1):
        # step 1, increase
        for r, c, _ in self.cells():
            self.grid[r][c]+= inc_am

    def run_flashes(self):
        # step 2, flashes
        flashes_map = [[False] * self.m for _ in range(self.n)]
        to_check = [(r, c) for r, c, v in self.cells() if v > 9]
        for r, c in to_check:
            flashes_map[r][c] = True
        while len(to_check) > 0:
            r, c = to_check.pop()
            for neigh_r, neigh_c in self.neighbors(r, c):
                self.grid[neigh_r][neigh_c]+= 1
                if not flashes_map[neigh_r][neigh_c] and self.grid[neigh_r][neigh_c] > 9:
                    to_check.append((neigh_r, neigh_c))
                    flashes_map[neigh_r][neigh_c] = True
        return flashes_map

    def reset_energy(self):
        # step 3, reset energy to 0
        for r, c, v in self.cells():
            if v > 9:
                self.grid[r][c] = 0

    def simulate(self):
        self.increment_all()
        flashes_map = self.run_flashes()
        self.reset_energy()
        return flashes_map

    def copy(self):
        new_grid = [row.copy() for row in self.grid]
        return OctopusGrid(new_grid)

def pretty_flashes(flashes):
    for row in flashes:
        for cell in row:
            print('O' if cell else '.', end='')
        print()
    print()

def count_flashes(grid, steps):
    grid = grid.copy()
    count = 0
    for _ in range(steps):
        flashes = grid.simulate()
        for r, c, _ in grid.cells():
            count+= flashes[r][c]
    return count

def part_1(grid):
    return count_flashes(grid, 100)

def part_2(grid):
    grid = grid.copy()
    step = 0
    while True:
        flashes = grid.simulate()
        step+= 1
        if all(all(cell for cell in row) for row in flashes):
            break
    return step

def main():
    grid = read_in()
    print("part_1:", part_1(grid))
    print("part_2:", part_2(grid))

if __name__ == '__main__':
    main()
