MOV = [(dr, dc) for dr in range(-1, 2) for dc in range(-1, 2) if abs(dr) + abs(dc) != 0]


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        yield line


def is_number(cell):
    return "0" <= cell <= "9"


def is_symbol(cell):
    return cell != "." and not is_number(cell)


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def get_cell(grid, r, c):
    if not in_range(grid, r, c):
        return "."
    return grid[r][c]


def get_gear_ratio(grid, r, c):
    if grid[r][c] != "*":
        return 0

    # gears have exactly 2 adjacent numbers
    numbers = []
    for dr in range(-1, 2):
        # custom loop is used to avoid double (or triple) counting
        # the numbers on the top and bottom
        for dc in (0, -1, +1):
            new_r, new_c = r + dr, c + dc
            if is_number(get_cell(grid, new_r, new_c)):
                numbers.append(read_number(grid, new_r, new_c))

                # a nicer way to do this is marking the numbers as they are read
                # and avoid reading the same number twice that way
                if abs(dr) == 1 and dc == 0:
                    break

    if len(numbers) != 2:
        return 0

    return numbers[0] * numbers[1]


def adj(grid, r, c):
    for dr, dc in MOV:
        new_r, new_c = r + dr, c + dc
        if get_cell(grid, new_r, new_c) != ".":
            yield new_r, new_c


def dfs(grid, marked, r, c):
    if marked[r][c]:
        return
    marked[r][c] = True

    for new_r, new_c in adj(grid, r, c):
        dfs(grid, marked, new_r, new_c)


def read_number(grid, r, c):
    # go to the far left of the number
    while is_number(get_cell(grid, r, c - 1)):
        c -= 1

    # reach the right end
    number = []
    while is_number(get_cell(grid, r, c)):
        number.append(grid[r][c])
        c += 1

    return int("".join(number))


def part_1(grid):
    marked = [[False] * len(grid[0]) for _ in grid]

    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if is_symbol(cell):
                dfs(grid, marked, r, c)

    # extract the marked numbers from the grid
    res = 0

    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            # spot the beginning of a marked number
            if (
                marked[r][c]
                and is_number(cell)
                and not is_number(get_cell(grid, r, c - 1))
            ):
                res += read_number(grid, r, c)

    return res


def part_2(grid):
    res = 0
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            res += get_gear_ratio(grid, r, c)

    return res


def main():
    grid = list(read_lines())

    print("part_1:", part_1(grid))
    print("part_2:", part_2(grid))


if __name__ == "__main__":
    main()
