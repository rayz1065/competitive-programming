from itertools import tee


def pairwise(it):
    a, b = tee(it)
    next(b, None)
    return zip(a, b)


MOV = [(-1, 0), (1, 0), (0, -1), (0, 1)]


def read_input():
    res = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        res.append(line)
    return res


def iter_grid(grid):
    for r, row in enumerate(grid):
        for c, _ in enumerate(row):
            yield r, c


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def adj(grid, r, c):
    for dr, dc in MOV:
        new_r, new_c = r + dr, c + dc
        if in_range(grid, new_r, new_c):
            yield new_r, new_c


def cc_dfs(grid, r, c, ccs_grid, cc_id):
    ccs_grid[r][c] = cc_id
    for new_r, new_c in adj(grid, r, c):
        if grid[r][c] == grid[new_r][new_c] and ccs_grid[new_r][new_c] != cc_id:
            cc_dfs(grid, new_r, new_c, ccs_grid, cc_id)


def find_ccs(grid):
    ccs_grid = [[-1 for _ in row] for row in grid]
    cc_id = 0
    for r, c in iter_grid(grid):
        if ccs_grid[r][c] == -1:
            cc_dfs(grid, r, c, ccs_grid, cc_id)
            cc_id += 1

    res = [[] for _ in range(cc_id)]
    for r, c in iter_grid(grid):
        res[ccs_grid[r][c]].append((r, c))

    return res, ccs_grid


def part_1(grid):
    ccs, ccs_grid = find_ccs(grid)
    perimeters = [
        sum(
            ccs_grid[new_r][new_c] != ccs_grid[r][c]
            for r, c in cc
            for new_r, new_c in adj(grid, r, c)
        )
        + sum(4 - len(list(adj(grid, r, c))) for r, c in cc)
        for cc in ccs
    ]
    areas = [len(x) for x in ccs]
    return sum(x * y for x, y in zip(perimeters, areas))


def part_2(grid):
    ccs, ccs_grid = find_ccs(grid)
    sides_ids = [{} for cc in ccs]
    areas = [len(x) for x in ccs]

    for r, c in iter_grid(grid):
        for dr, dc in MOV:
            new_r, new_c = r + dr, c + dc
            if in_range(grid, new_r, new_c) and grid[new_r][new_c] == grid[r][c]:
                # not an edge
                continue
            sides_ids[ccs_grid[r][c]].setdefault(
                (r * abs(dr), c * abs(dc), dr, dc), []
            ).append((r, c))

    sides = [0 for cc in ccs]
    for cc_id, cc_sides_ids in enumerate(sides_ids):
        for cells in cc_sides_ids.values():
            sides[cc_id] += 1
            # find holes within the edge
            for (r, c), (new_r, new_c) in pairwise(cells):
                sides[cc_id] += abs(new_r - r) + abs(new_c - c) > 1

    return sum(x * y for x, y in zip(sides, areas))


def main():
    grid = read_input()
    print("part1:", part_1(grid))
    print("part2:", part_2(grid))


if __name__ == "__main__":
    main()
