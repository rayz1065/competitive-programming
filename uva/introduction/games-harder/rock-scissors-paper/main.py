MOV = [(0, 1), (0, -1), (1, 0), (-1, 0)]
ENEMY = {
    'R': 'P',
    'P': 'S',
    'S': 'R'
}


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def adj(grid, r, c):
    for dr, dc in MOV:
        new_r, new_c = r + dr, c + dc
        if not in_range(grid, new_r, new_c):
            continue
        yield new_r, new_c


def simulate(grid):
    new_grid = [row.copy() for row in grid]

    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            for adj_r, adj_c in adj(grid, r, c):
                if not grid[adj_r][adj_c] == ENEMY[cell]:
                    continue
                new_grid[r][c] = ENEMY[cell]

    return new_grid


def print_grid(grid):
    for row in grid:
        print(''.join(row))


def main():
    line = ''
    while line == '':
        line = input().strip()
    rows, _, n_generations = (int(x) for x in line.split())
    grid = [list(input().strip()) for _ in range(rows)]

    for _ in range(n_generations):
        grid = simulate(grid)

    return grid


t = int(input().strip())
for tc in range(t):
    if tc > 0:
        print()
    print_grid(main())
