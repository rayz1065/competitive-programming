MOV = [(-1, -1), (-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1)]


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def iter_grid(grid):
    for r, row in enumerate(grid):
        for c, _ in enumerate(row):
            yield r, c


def iter_ray(grid, r, c, dr, dc, len_):
    for i in range(len_):
        new_r, new_c = r + dr * i, c + dc * i
        if in_range(grid, new_r, new_c):
            yield new_r, new_c


def part_1(grid):
    res = 0

    for r, c in iter_grid(grid):
        if grid[r][c] != "X":
            continue
        for dr, dc in MOV:
            cells = tuple(iter_ray(grid, r, c, dr, dc, 4))
            letters = "".join(grid[r_][c_] for r_, c_ in cells)
            res += letters == "XMAS"

    return res


def part_2(grid):
    res = 0

    for r, c in iter_grid(grid):
        if (
            grid[r][c] != "A"
            or not in_range(grid, r - 1, c - 1)
            or not in_range(grid, r + 1, c + 1)
        ):
            continue

        corners = [grid[r + dr][c + dc] for dr, dc in MOV if dr and dc]
        if corners[0] != corners[2] and "".join(sorted(corners)) == "MMSS":
            res += 1

    return res


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield line


def read_input():
    return list(read_lines())


def main():
    grid = read_input()
    print("part1:", part_1(grid))
    print("part2:", part_2(grid))


if __name__ == "__main__":
    main()
