import heapq

MOV = [(-1, 0), (0, 1), (1, 0), (0, -1)]
COST_TURN = 1000
UNREACHED = 2**32


def read_input():
    res = []
    start = None
    end = None
    while True:
        try:
            line = list(input().strip())
        except EOFError:
            break
        if "S" in line:
            start = len(res), line.index("S")
            line[start[1]] = "."
        if "E" in line:
            end = len(res), line.index("E")
            line[end[1]] = "."
        res.append(line)
    return res, start, end


def get_movements(grid, loc):
    (r, c), (dr, dc) = loc
    yield ((r, c), (dc, dr)), COST_TURN
    yield ((r, c), (-dc, -dr)), COST_TURN
    new_r, new_c = r + dr, c + dc
    if grid[new_r][new_c] == ".":
        yield ((new_r, new_c), (dr, dc)), 1


def dijkstra(grid, start_set):
    ff = [(0, start) for start in start_set]
    distances = {start: 0 for start in start_set}

    while ff:
        distance, loc = heapq.heappop(ff)
        if distance > distances[loc]:
            continue

        for new_loc, cost in get_movements(grid, loc):
            new_dist = distance + cost
            if distances.get(new_loc, UNREACHED) > new_dist:
                heapq.heappush(ff, (new_dist, new_loc))
                distances[new_loc] = new_dist

    return distances


def iter_grid(grid):
    for r, row in enumerate(grid):
        for c, _ in enumerate(grid):
            yield r, c


def part_1(grid, start, end):
    distances = dijkstra(grid, [(start, (1, 0))])
    return min(distances[end, (dr, dc)] for dr, dc in MOV)


def part_2(grid, start, end):
    distances = dijkstra(grid, [(start, (1, 0))])
    distances_reversed = dijkstra(grid, [(end, (dr, dc)) for dr, dc in MOV])

    target = min(distances[end, (dr, dc)] for dr, dc in MOV)
    res = set()

    for r, c in iter_grid(grid):
        if grid[r][c] != ".":
            continue
        for dr, dc in MOV:
            if (
                distances_reversed.get(((r, c), (-dr, -dc)), UNREACHED)
                + distances.get(((r, c), (dr, dc)), UNREACHED)
                == target
            ):
                res.add((r, c))

    return len(res)


def main():
    grid, start, end = read_input()
    print("part1:", part_1(grid, start, end))
    print("part2:", part_2(grid, start, end))


if __name__ == "__main__":
    main()
