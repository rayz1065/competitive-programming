MOV = {
    "up": (-1, 0),
    "right": (0, 1),
    "down": (1, 0),
    "left": (0, -1),
}


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield list(line)


def transpose(grid):
    return [[grid[i][j] for i in range(len(grid))] for j in range(len(grid[0]))]


def tilt(grid, direction="up"):
    dr, dc = MOV[direction]
    if direction in ("left", "right"):
        dr, dc = dc, dr
        grid = transpose(grid)
    else:
        grid = list(list(x) for x in grid)

    for c in range(len(grid[0])):
        # when pushing up, starts from the first row and computes the first
        # free one, then swaps the free row with any rock found, when pushing
        # down does the same but in reverse

        r_it = range(len(grid))
        if dr > 0:
            r_it = reversed(r_it)

        free_row = None
        for r in r_it:
            cell = grid[r][c]
            if cell == "." and free_row is None:
                free_row = r
            elif cell == "#":
                free_row = None
            elif cell == "O" and free_row is not None:
                grid[free_row][c], grid[r][c] = grid[r][c], grid[free_row][c]
                free_row -= dr

    if direction in ("left", "right"):
        grid = transpose(grid)

    return grid


def total_load(grid):
    return sum(
        len(grid) - r for r, row in enumerate(grid) for cell in row if cell == "O"
    )


def part_1(grid):
    return total_load(tilt(grid))


def turtle_and_hare(initial_state, f):
    turtle = f(initial_state)
    hare = f(f(initial_state))

    while turtle != hare:
        turtle = f(turtle)
        hare = f(f(hare))

    hare = initial_state
    loop_delta = 0
    while turtle != hare:
        turtle = f(turtle)
        hare = f(hare)
        loop_delta += 1

    loop_length = 1
    hare = f(hare)
    while turtle != hare:
        hare = f(hare)
        loop_length += 1

    return loop_length, loop_delta


def cycle_directions(grid):
    for direction in ("up", "left", "down", "right"):
        grid = tilt(grid, direction)

    return grid


def part_2(grid):
    # turtle and hare
    loop_length, loop_delta = turtle_and_hare(grid, cycle_directions)

    total_cycles = 1000000000
    total_cycles -= ((total_cycles - loop_delta) // loop_length) * loop_length

    for _ in range(total_cycles):
        grid = cycle_directions(grid)

    return total_load(grid)


def main():
    grid = list(read_lines())
    print("part_1:", part_1(grid))
    print("part_2:", part_2(grid))


if __name__ == "__main__":
    main()
