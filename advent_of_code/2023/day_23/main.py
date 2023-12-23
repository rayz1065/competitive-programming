import sys
import re

sys.setrecursionlimit(10000)

MOV = [
    (0, 1),
    (1, 0),
    (0, -1),
    (-1, 0),
]
SLOPES = {
    ">": [(0, 1)],
    "<": [(0, -1)],
    "v": [(1, 0)],
    "^": [(-1, 0)],
    "*": [],  # dry slope, used to compute explicit graph
}


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield line


def get_empty(grid, row):
    return row, grid[row].index(".")


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def adj(grid, r, c):
    if grid[r][c] in SLOPES:
        directions = SLOPES[grid[r][c]]
    else:
        directions = MOV

    for dr, dc in directions:
        new_r, new_c = r + dr, c + dc
        if not in_range(grid, new_r, new_c):
            continue

        cell = grid[new_r][new_c]
        if cell == "#":
            continue

        if cell != "*" and cell in SLOPES and (dr, dc) not in SLOPES[cell]:
            continue

        yield new_r, new_c


def _topological_sort(grid, r, c, visited, stack):
    if (r, c) in visited:
        return

    visited.add((r, c))
    assert grid[r][c] != "#"

    for new_r, new_c in adj(grid, r, c):
        _topological_sort(grid, new_r, new_c, visited, stack)

    stack.append((r, c))


def topological_sort(grid):
    r, c = get_empty(grid, 0)
    visited = set()
    stack = []

    _topological_sort(grid, r, c, visited, stack)
    return stack


def get_nodes(grid):
    yield get_empty(grid, 0)
    yield get_empty(grid, len(grid) - 1)

    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if grid[r][c] == "#" or len(list(adj(grid, r, c))) <= 2:
                continue
            yield r, c


def dry_out(grid):
    return [re.sub("[" + "".join(SLOPES) + "]", ".", row) for row in grid]


def bfs(grid, r, c):
    distances = {(r, c): 0}
    ff = [(r, c)]
    while len(ff) > 0:
        r, c = ff[0]
        ff = ff[1:]

        for new_r, new_c in adj(grid, r, c):
            if (new_r, new_c) in distances:
                continue

            distances[new_r, new_c] = distances[r, c] + 1
            ff.append((new_r, new_c))

    return distances


def longest_path(node, visited: set, graph: dict, exit_node):
    if node in visited:
        return -(2**30)

    visited.add(node)

    res = 0
    for other_node, edge_len in graph[node].items():
        res = max(res, longest_path(other_node, visited, graph, exit_node) + edge_len)

    visited.remove(node)
    if res == 0 and node != exit_node:
        return -(2**30)

    return res


def part_1(grid):
    stack = topological_sort(grid)

    distances = {stack[0]: 0}
    for r, c in stack[1:]:
        distance = -1
        for new_r, new_c in adj(grid, r, c):
            if (new_r, new_c) not in distances:
                continue

            distance = max(distance, distances[new_r, new_c] + 1)
        distances[r, c] = distance

    return distances[get_empty(grid, 0)]


def part_2(grid):
    grid = dry_out(grid)
    nodes = set(get_nodes(grid))

    broken_grid = [
        ["*" if (r, c) in nodes else cell for c, cell in enumerate(row)]
        for r, row in enumerate(grid)
    ]

    # for row in broken_grid:
    #     print(" ".join(row))
    # print("nodes:", len(nodes))

    graph = {}

    for node in nodes:
        r, c = node
        broken_grid[r][c] = "."
        distances = bfs(broken_grid, r, c)
        graph[node] = {}

        for other_node in nodes:
            if other_node == node or other_node not in distances:
                continue

            graph[node][other_node] = distances.get((other_node))

        broken_grid[r][c] = "*"

    return longest_path(
        get_empty(grid, 0), set(), graph, get_empty(grid, len(grid) - 1)
    )


def main():
    grid = list(read_lines())
    print("part_1:", part_1(grid))
    print("part_2:", part_2(grid))


if __name__ == "__main__":
    main()
