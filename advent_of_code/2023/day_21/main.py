MOV = [(0, 1), (1, 0), (0, -1), (-1, 0)]
MAX_DISTANCE = 64
MAX_DISTANCE_2 = 26501365


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield line


def get_starting(grid):
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if grid[r][c] == "S":
                return r, c


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def adj(grid, r, c, map_r, map_c):
    for dr, dc in MOV:
        new_r, new_c = r + dr, c + dc
        new_map_r, new_map_c = map_r, map_c
        if not in_range(grid, new_r, 0):
            new_r = (new_r + len(grid)) % len(grid)
            new_map_r += dr
        if not in_range(grid, 0, new_c):
            new_c = (new_c + len(grid[0])) % len(grid[0])
            new_map_c += dc

        if grid[new_r][new_c] == "#":
            continue

        yield new_r, new_c, new_map_r, new_map_c


def bfs(grid, r, c, max_distance):
    ff = [(r, c, 0, 0)]
    distances = {}
    distances[r, c, 0, 0] = 0

    while len(ff) > 0:
        r, c, map_r, map_c = ff[0]
        distance = distances[r, c, map_r, map_c]
        if distance >= max_distance:
            break

        ff = ff[1:]
        for node in adj(grid, r, c, map_r, map_c):
            if node in distances:
                continue

            distances[node] = distance + 1
            ff.append(node)

    return distances


def part_1(grid):
    distances = bfs(grid, *get_starting(grid), max_distance=MAX_DISTANCE)
    res = 0
    for (_, _, map_r, map_c), distance in distances.items():
        if (
            distance is not None
            and distance <= MAX_DISTANCE
            and distance % 2 == MAX_DISTANCE % 2
            and (map_r, map_c) == (0, 0)
        ):
            res += 1

    return res


def part_2(grid):
    lambda_ = 6 if len(grid) < 50 else 3
    distances = bfs(
        grid, *get_starting(grid), max_distance=(lambda_ + 1) * len(grid)
    )
    res = 0
    distance_freqs = {}
    for _, distance in distances.items():
        distance_freqs.setdefault(distance, 0)
        distance_freqs[distance] += 1
        if distance <= MAX_DISTANCE_2 and distance % 2 == MAX_DISTANCE_2 % 2:
            res += 1

    deltas = {}
    for distance in range(lambda_ * len(grid), (lambda_ + 1) * len(grid)):
        print(distance_freqs[distance] - distance_freqs[distance - len(grid)], end="\t")
        deltas[distance % len(grid)] = distance_freqs[distance], (
            distance_freqs[distance] - distance_freqs[distance - len(grid)]
        )
    print()

    res = 0
    for distance in range(MAX_DISTANCE_2 % 2, MAX_DISTANCE_2 + 1, 2):
        if distance < len(grid) * (lambda_ + 1):
            res += distance_freqs[distance]
        else:
            base, delta = deltas[distance % len(grid)]
            res += base + delta * (distance // len(grid) - lambda_)

    return res


def main():
    grid = list(read_lines())
    print("part_1:", part_1(grid))
    print("part_2:", part_2(grid))


if __name__ == "__main__":
    main()
