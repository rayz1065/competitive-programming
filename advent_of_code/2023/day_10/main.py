import sys
from itertools import product

sys.setrecursionlimit(100000)

PIPES = {
    "|": ((-1, 0), (1, 0)),
    "-": ((0, -1), (0, 1)),
    "L": ((-1, 0), (0, 1)),
    "J": ((-1, 0), (0, -1)),
    "7": ((1, 0), (0, -1)),
    "F": ((1, 0), (0, 1)),
    ".": None,
    "S": None,
}
MOV = [(dr, dc) for dr in range(-1, 2) for dc in range(-1, 2) if abs(dr) + abs(dc) == 1]


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield line


def in_range(maze, r, c):
    return 0 <= r < len(maze) and 0 <= c < len(maze[r])


def get_cell(maze, r, c):
    if not in_range(maze, r, c):
        return "."
    return maze[r][c]


def iterate_cells(maze):
    for r, row in enumerate(maze):
        for c, cell in enumerate(row):
            yield r, c, cell


def is_pipe_compatible(pipe, dr, dc):
    # whether from pipe we can move in direction dr, dc
    if PIPES[pipe] is None:
        return False

    return (dr, dc) in PIPES[pipe]


def mark_cc(maze, ccs, cc, r, c):
    if ccs[r][c] is not None:
        return
    ccs[r][c] = cc

    for dr, dc in PIPES[maze[r][c]]:
        new_r, new_c = r + dr, c + dc
        if is_pipe_compatible(get_cell(maze, new_r, new_c), -dr, -dc):
            mark_cc(maze, ccs, cc, new_r, new_c)


def compute_ccs(maze):
    # computes connected components
    ccs = [[None for _ in range(len(maze[0]))] for _ in range(len(maze))]
    cc = 0

    for r, c, cell in iterate_cells(maze):
        if PIPES[cell] is not None and ccs[r][c] is None:
            mark_cc(maze, ccs, cc, r, c)
            cc += 1

    return ccs


def get_starting_cell_pipe(maze, ccs):
    r, c = next(((r, c) for r, c, cell in iterate_cells(maze) if cell == "S"), None)

    for pipe, directions in PIPES.items():
        if directions is None:
            continue

        adj_ccs = set()
        for dr, dc in directions:
            new_r, new_c = r + dr, c + dc
            if not is_pipe_compatible(get_cell(maze, new_r, new_c), -dr, -dc):
                # invalid movement
                adj_ccs.clear()
                break

            adj_ccs.add(ccs[new_r][new_c])

        if len(adj_ccs) == 1:
            # found the right pipe
            return r, c, pipe, adj_ccs.pop()


def part_1(maze):
    ccs = compute_ccs(maze)
    r, c, pipe, cc = get_starting_cell_pipe(maze, ccs)

    # count the number of elements in the CC
    return sum(other_cc == cc for _, _, other_cc in iterate_cells(ccs)) / 2


def flood_fill(expanded_maze, marked, r, c):
    if marked[r][c]:
        return
    marked[r][c] = True

    for dr, dc in MOV:
        new_r, new_c = r + dr, c + dc
        if (
            not in_range(expanded_maze, new_r, new_c)
            or expanded_maze[new_r][new_c] == "#"
        ):
            continue

        flood_fill(expanded_maze, marked, new_r, new_c)


def fast_part_2(maze):
    ccs = compute_ccs(maze)
    maze = list([list(row) for row in maze])

    r, c, pipe, cc = get_starting_cell_pipe(maze, ccs)
    maze[r][c] = pipe
    ccs[r][c] = cc

    res = 0
    for r, row in enumerate(maze):
        is_in_maze = False
        for c, cell in enumerate(row):
            print(maze[r][c] if ccs[r][c] == cc else " ", end="")
            if ccs[r][c] == cc:
                if cell in ("F", "7", "|"):
                    is_in_maze = not is_in_maze

            elif is_in_maze:
                res += 1

    return res


def part_2(maze):
    # blow out the map by adding a new cell between each cell based on the ccs
    ccs = compute_ccs(maze)
    maze = list([list(row) for row in maze])

    expanded_maze = [
        ["." for _ in range(len(maze[0]) * 2 + 1)] for _ in range(len(maze) * 2 + 1)
    ]
    r, c, pipe, cc = get_starting_cell_pipe(maze, ccs)
    maze[r][c] = pipe
    ccs[r][c] = cc

    for r, c, other_cc in iterate_cells(ccs):
        if other_cc != cc:
            continue

        expanded_maze[r * 2 + 1][c * 2 + 1] = "#"
        pipe = maze[r][c]
        for dr, dc in PIPES[pipe]:
            expanded_maze[r * 2 + dr + 1][c * 2 + dc + 1] = "#"

    marked = [
        [False for _ in range(len(expanded_maze[0]))] for _ in range(len(expanded_maze))
    ]
    flood_fill(expanded_maze, marked, 0, 0)

    res = 0
    for r, row in enumerate(expanded_maze):
        for c, cell in enumerate(row):
            if marked[r][c]:
                cell = " "

            elif (r - 1) % 2 == 0 and (c - 1) % 2 == 0 and expanded_maze[r][c] != "#":
                res += 1
                cell = "I"

            print(cell, end="")
        print()

    return res


def main():
    maze = list(read_lines())
    print("part_1:", part_1(maze))
    print("part_2:", part_2(maze))


if __name__ == "__main__":
    main()
