MOV = [(-1, 0), (0, -1), (1, 0), (0, 1)]
GRID_SIZE = 71
PART_1_FALLEN = 1024


def read_input():
    res = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        res.append(tuple(int(x) for x in line.strip().split(",")))
    if all(x[0] <= 6 for x in res):
        global GRID_SIZE, PART_1_FALLEN
        GRID_SIZE = 7
        PART_1_FALLEN = 12
    return res


def iter_grid():
    for y in range(GRID_SIZE):
        for x in range(GRID_SIZE):
            yield x, y


def in_range(x, y):
    return 0 <= x < GRID_SIZE and 0 <= y < GRID_SIZE


def adj(grid, x, y):
    for dx, dy in MOV:
        new_x, new_y = x + dx, y + dy
        if in_range(new_x, new_y) and grid[new_x][new_y] == ".":
            yield new_x, new_y


def print_grid(grid):
    for y in range(GRID_SIZE):
        for x in range(GRID_SIZE):
            print(grid[x][y], end="")
        print()


def bfs(grid):
    x, y = 0, 0
    ff = [(x, y)]
    dist = {(x, y): 0}
    while ff:
        x, y = ff[0]
        ff = ff[1:]
        for new_x, new_y in adj(grid, x, y):
            if (new_x, new_y) not in dist:
                dist[new_x, new_y] = dist[x, y] + 1
                ff.append((new_x, new_y))
    return dist[GRID_SIZE - 1, GRID_SIZE - 1]


def ufds_join(parents, a, b):
    a = ufds_get_parent(parents, a)
    b = ufds_get_parent(parents, b)
    parents[a] = b


def ufds_get_parent(parents, a):
    if parents[a] == a:
        return a
    parents[a] = ufds_get_parent(parents, parents[a])
    return parents[a]


def part_1(locations):
    grid = [["."] * GRID_SIZE for _ in range(GRID_SIZE)]
    for x, y in locations[:PART_1_FALLEN]:
        grid[x][y] = "#"
    return bfs(grid)


def part_2(locations):
    grid = [["."] * GRID_SIZE for _ in range(GRID_SIZE)]
    for x, y in locations:
        grid[x][y] = "#"

    parents = {(x, y): (x, y) for x, y in iter_grid()}

    for x, y in iter_grid():
        if grid[x][y] == "#":
            continue
        for new_x, new_y in adj(grid, x, y):
            ufds_join(parents, (x, y), (new_x, new_y))

    for x, y in reversed(locations):
        grid[x][y] = "."
        for new_x, new_y in adj(grid, x, y):
            ufds_join(parents, (x, y), (new_x, new_y))

        if ufds_get_parent(parents, (0, 0)) == ufds_get_parent(
            parents, (GRID_SIZE - 1, GRID_SIZE - 1)
        ):
            return f"{x},{y}"

    assert False


def main():
    locations = read_input()
    print("part1:", part_1(locations))
    print("part2:", part_2(locations))


if __name__ == "__main__":
    main()
