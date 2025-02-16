from itertools import combinations


def read_input():
    res = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        res.append(list(line))
    return res


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[0])


def get_antennae(grid):
    res = []
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if cell != ".":
                res.append((r, c, cell))
    return res


def part_1(grid):
    antinodes = set()
    rows = len(grid)
    cols = len(grid[0])
    antennae = get_antennae(grid)
    for (r, c, antenna), (r2, c2, antenna2) in combinations(antennae, r=2):
        if antenna != antenna2:
            continue
        dr, dc = r2 - r, c2 - c
        antinodes.add((r - dr, c - dc, antenna))
        antinodes.add((r + 2 * dr, c + 2 * dc, antenna))
    antinodes = set((x[0], x[1]) for x in antinodes if in_range(grid, x[0], x[1]))

    return len(antinodes)


def part_2(grid):
    antinodes = set()
    rows = len(grid)
    cols = len(grid[0])
    antennae = get_antennae(grid)
    for (r, c, antenna), (r2, c2, antenna2) in combinations(antennae, r=2):
        if antenna != antenna2:
            continue
        dr, dc = r2 - r, c2 - c

        new_r, new_c = r, c
        while in_range(grid, new_r, new_c):
            antinodes.add((new_r, new_c, antenna))
            new_r += dr
            new_c += dc
        new_r, new_c = r, c
        while in_range(grid, new_r, new_c):
            antinodes.add((new_r, new_c, antenna))
            new_r -= dr
            new_c -= dc
    antinodes = set((x[0], x[1]) for x in antinodes if in_range(grid, x[0], x[1]))

    return len(antinodes)


def main():
    grid = read_input()
    print("part1:", part_1(grid))
    print("part2:", part_2(grid))


if __name__ == "__main__":
    main()
