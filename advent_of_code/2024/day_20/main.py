from collections import namedtuple

MOV = [(-1, 0), (0, -1), (1, 0), (0, 1)]


def read_input():
    res = []
    start = None
    end = None
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        line = list(line)
        if "S" in line:
            start = len(res), line.index("S")
            line[start[1]] = "."
        if "E" in line:
            end = len(res), line.index("E")
            line[end[1]] = "."
        res.append(line)
    return res, start, end


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def iter_grid(grid):
    for r, row in enumerate(grid):
        for c, _ in enumerate(row):
            yield r, c


def adj(grid, r, c):
    for dr, dc in MOV:
        new_r, new_c = r + dr, c + dc
        if in_range(grid, new_r, new_c):
            yield new_r, new_c


def bfs(grid, start):
    dist = {start: 0}
    ff = [start]
    while ff:
        r, c = ff[0]
        ff = ff[1:]
        for new_r, new_c in adj(grid, r, c):
            if grid[new_r][new_c] == "." and (new_r, new_c) not in dist:
                dist[new_r, new_c] = dist[r, c] + 1
                ff.append((new_r, new_c))
    return dist


def get_cheats(grid, r, c, max_dist):
    return (
        (new_r, new_c)
        for new_r in range(r - max_dist, r + max_dist + 1)
        for new_c in range(c - max_dist, c + max_dist + 1)
        if (
            in_range(grid, new_r, new_c)
            and abs(new_r - r) + abs(new_c - c) <= max_dist
            and grid[new_r][new_c] == "."
        )
    )


def find_shortcuts(grid, start, end, max_cheat_len):
    distances = bfs(grid, start)

    res = 0
    empty_cells = ((r, c) for r, c in iter_grid(grid) if grid[r][c] == ".")
    for r, c in empty_cells:
        for new_r, new_c in get_cheats(grid, r, c, max_cheat_len):
            original_dist = distances[new_r, new_c] - distances[r, c]
            new_dist = abs(r - new_r) + abs(c - new_c)
            if new_dist <= original_dist - 100:
                res += 1

    return res


def part_1(grid, start, end):
    return find_shortcuts(grid, start, end, 2)


def part_2(grid, start, end):
    return find_shortcuts(grid, start, end, 20)


def main():
    grid, start, end = read_input()
    print("part1:", part_1(grid, start, end))
    print("part2:", part_2(grid, start, end))


if __name__ == "__main__":
    main()
