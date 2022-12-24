import queue
from math import lcm
from enum import Enum

class BlizzardDire(Enum):
    UP = '^'
    RIGHT = '>'
    DOWN = 'v'
    LEFT = '<'

MOV = {
    BlizzardDire.UP: (-1, 0),
    BlizzardDire.RIGHT: (0, 1),
    BlizzardDire.DOWN: (1, 0),
    BlizzardDire.LEFT: (0, -1)
}

class Grid:
    def __init__(self, grid: list[list[str]], blizzards: list[(int, int, BlizzardDire)]):
        self.grid: list[list[str]] = grid
        self.blizzards: list[(int, int, BlizzardDire)] = blizzards

    def __str__(self):
        res = []
        blizzard_dirs = self.get_blizzards_dirs()
        for r, row in enumerate(self.grid):
            row_str = []
            for c, cell in enumerate(row):
                blizzards = blizzards_dirs.get((r, c), [])
                if len(blizzards) > 1:
                    cell = str(len(blizzards))
                elif len(blizzards) == 1:
                    cell = blizzards[0].value
                row_str.append(cell)
            res.append(''.join(row_str))
        return '\n'.join(res)

    def get_blizzards_dirs (self):
        res = {}
        for blizzard in self.blizzards:
            r, c, dire = blizzard
            res.setdefault((r, c), [])
            res[r, c].append(dire)
        return res

def construct_grid (grid: list[str]):
    blizzards: list[(int, int, BlizzardDir)] = []
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if cell in '.#':
                continue
            dire = BlizzardDire(cell)
            blizzards.append((r, c, dire))
    grid = [['#' if cell == '#' else '.'
                 for cell in row]
                 for row in grid]
    return Grid(grid, blizzards)

def read_input ():
    grid = []
    try:
        while True:
            line = input()
            grid.append(list(line))
    except EOFError:
        pass
    return construct_grid(grid)

def simulate (grid: Grid) -> Grid:
    res = []
    n_rows = len(grid.grid) - 2
    m_cols = len(grid.grid[0]) - 2
    for blizzard in grid.blizzards:
        r, c, dire = blizzard
        dr, dc = MOV[dire]
        r = (r + dr + n_rows - 1) % n_rows + 1
        c = (c + dc + m_cols - 1) % m_cols + 1
        res.append((r, c, dire))
    return Grid(grid.grid, res)

def find_safe_cells (grid: Grid) -> set[(int, int)]:
    res = set()
    blizzard_dirs = grid.get_blizzards_dirs()
    for r, row in enumerate(grid.grid):
        for c, cell in enumerate(row):
            if cell == '.' and (r, c) not in blizzard_dirs:
                res.add((r, c))
    return res

def adj (r, c, safe_cells: set[(int, int)]):
    if (r, c) in safe_cells:
        yield r, c
    for dire in BlizzardDire:
        dr, dc = MOV[dire]
        if (r + dr, c + dc) in safe_cells:
            yield (r + dr, c + dc)

def get_all_safe_cells (grid: Grid):
    n_rows = len(grid.grid) - 2
    m_cols = len(grid.grid[0]) - 2
    end_time = lcm(n_rows, m_cols)
    all_safe_cells = []
    for _ in range(end_time):
        all_safe_cells.append(find_safe_cells(grid))
        grid = simulate(grid)
    return all_safe_cells

def find_path (grid: Grid, start, end, start_time=0):
    all_safe_cells = get_all_safe_cells(grid)
    ff = queue.SimpleQueue()
    r, c = start
    t = start_time % len(all_safe_cells)
    ff.put_nowait((r, c, t))
    dist: map[(int, int, int), int] = { (r, c, t): start_time }
    # bfs
    while not ff.empty():
        r, c, t = ff.get_nowait()
        new_t = (t + 1) % len(all_safe_cells)
        for adj_r, adj_c in adj(r, c, all_safe_cells[new_t]):
            if (adj_r, adj_c, new_t) not in dist:
                dist[adj_r, adj_c, new_t] = dist[r, c, t] + 1
                ff.put_nowait((adj_r, adj_c, new_t))
    return min(x for key, x in dist.items() if (key[0], key[1]) == end)

def part_2 (grid: Grid):
    first_cell = (0, 1)
    last_cell = (len(grid.grid) - 1, len(grid.grid[0]) - 2)
    curr_t = 0
    curr_t = find_path(grid, first_cell, last_cell, curr_t) # go forward
    curr_t = find_path(grid, last_cell, first_cell, curr_t) # go back
    curr_t = find_path(grid, first_cell, last_cell, curr_t) # go foward again
    return curr_t

def part_1 (grid: Grid):
    first_cell = (0, 1)
    last_cell = (len(grid.grid) - 1, len(grid.grid[0]) - 2)
    return find_path(grid, first_cell, last_cell)

def main ():
    grid = read_input()
    first_cell = (0, 1)
    last_cell = (len(grid.grid) - 1, len(grid.grid[0]) - 2)
    print('part_1:', part_1(grid))
    print('part_2:', part_2(grid))

if __name__ == '__main__':
    main()
