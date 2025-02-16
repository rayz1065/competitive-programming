MOV = [(0, 1), (0, -1), (1, 0), (-1, 0)]


def read_input():
    grid = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        grid.append(list(map(int, line)))
    return grid


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid)


def adj(grid, r, c):
    for dr, dc in MOV:
        new_r, new_c = r + dr, c + dc
        if in_range(grid, new_r, new_c):
            yield new_r, new_c


def adj_reachable(grid, r, c):
    yield from (
        (new_r, new_c)
        for new_r, new_c in adj(grid, r, c)
        if grid[new_r][new_c] == grid[r][c] + 1
    )


def iter_grid(grid):
    for r, row in enumerate(grid):
        for c, _ in enumerate(row):
            yield r, c


def get_value_locations(grid):
    res = [[] for _ in range(10)]
    for r, c in iter_grid(grid):
        res[grid[r][c]].append((r, c))
    return res


def part_1(grid):
    value_locations = get_value_locations(grid)

    reachable = [
        [set([(r, c)]) if value == 9 else set() for c, value in enumerate(row)]
        for r, row in enumerate(grid)
    ]
    for value in reversed(range(9)):
        for r, c in value_locations[value]:
            for new_r, new_c in adj_reachable(grid, r, c):
                reachable[r][c].update(reachable[new_r][new_c])

    return sum(len(reachable[r][c]) for r, c in value_locations[0])


def part_2(grid):
    value_locations = get_value_locations(grid)

    targets = [
        [1 if value == 9 else 0 for c, value in enumerate(row)]
        for r, row in enumerate(grid)
    ]
    for value in reversed(range(9)):
        for r, c in value_locations[value]:
            for new_r, new_c in adj_reachable(grid, r, c):
                targets[r][c] += targets[new_r][new_c]

    return sum(targets[r][c] for r, c in value_locations[0])


def main():
    grid = read_input()
    print("part1:", part_1(grid))
    print("part2:", part_2(grid))


if __name__ == "__main__":
    main()
