from collections import namedtuple

Guard = namedtuple("Guard", ["Position", "Direction"])

guard_directions = {"v": (1, 0), "^": (-1, 0), ">": (0, 1), "<": (0, -1)}
clockwise_direction = {
    (-1, 0): (0, 1),
    (0, 1): (1, 0),
    (1, 0): (0, -1),
    (0, -1): (-1, 0),
}


def read_input():
    grid = []
    guard = None
    while True:
        try:
            line = list(input().strip())
        except EOFError:
            break
        column = next(
            (i for i, x in enumerate(line) if x in guard_directions.keys()), None
        )
        if column is not None:
            direction = guard_directions[line[column]]
            guard = Guard((len(grid), column), direction)
            line[column] = "."
        grid.append(line)

    return grid, guard


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[0])


def simulate(grid, guard):
    visited_grid = [[False for _ in row] for row in grid]
    visited = {}

    while True:
        (r, c), (dr, dc) = guard
        if guard in visited:
            return "loop", visited
        visited[guard] = True
        visited_grid[r][c] = True
        new_dr, new_dc = dr, dc
        new_r, new_c = r + dr, c + dc

        if not in_range(grid, new_r, new_c):
            return "escaped", visited

        if grid[new_r][new_c] == "#":
            guard = Guard((r, c), clockwise_direction[dr, dc])
        else:
            guard = Guard((new_r, new_c), (dr, dc))


def part_1(grid, guard):
    _, visited = simulate(grid, guard)
    return len(set(x for x, _ in visited))


def part_2(grid, guard):
    visited = set(x for x, _ in simulate(grid, guard)[1].keys())

    res = 0
    for r, c in visited:
        if (r, c) == guard.Position:
            continue
        grid[r][c] = "#"
        simulation_res, _ = simulate(grid, guard)
        res += simulation_res == "loop"
        grid[r][c] = "."

    return res


def main():
    grid, guard = read_input()
    print("part1:", part_1(grid, guard))
    print("part2:", part_2(grid, guard))


if __name__ == "__main__":
    main()
