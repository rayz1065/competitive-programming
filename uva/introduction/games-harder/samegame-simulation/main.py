MOV = [(-1, 0), (1, 0), (0, -1), (0, 1)]


def in_range (grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def adj (grid, r, c):
    for dr, dc in MOV:
        new_r, new_c = r + dr, c + dc
        if in_range(grid, new_r, new_c):
            yield new_r, new_c


def print_grid (grid, rows, columns):
    for r in range(rows - 1, -1, -1):
        print('   ', end='')
        for c in range(0, columns):
            cell = grid[r][c] if in_range(grid, r, c) else None
            cell = cell if cell is not None else ' '
            print(f' {cell}', end='')
        print()


def normalize_grid (grid):
    # apply gravity
    for c, _ in enumerate(grid[0]):
        empty_row = None
        for r, _ in enumerate(grid):
            if grid[r][c] is None and empty_row is None:
                empty_row = r
            if grid[r][c] is not None and empty_row is not None:
                grid[empty_row][c], grid[r][c] = grid[r][c], None
                empty_row += 1

    # remove empty columns
    for c in range(len(grid[0]) - 1, -1, -1):
        empty_row = None
        if all(row[c] is None for row in grid):
            for row in grid:
                row.pop(c)


def get_connected_region (grid, r, c):
    if not in_range(grid, r, c) or grid[r][c] is None:
        return []

    target_value = grid[r][c]
    visited = { (r, c): True }
    ff = [(r, c)]

    while len(ff) != 0:
        r, c = ff.pop()
        for new_r, new_c in adj(grid, r, c):
            if grid[new_r][new_c] != target_value or (new_r, new_c) in visited:
                continue
            ff.append((new_r, new_c))
            visited[new_r, new_c] = True

    return list(visited.keys())


def erase_cells (grid, cells):
    for r, c in cells:
        grid[r][c] = None
    normalize_grid(grid)


def main ():
    grid_id = 0
    while True:
        line = ''
        while line == '':
            line = input().strip()
        rows, columns = (int(x) for x in line.split())
        if rows == 0 or columns == 0:
            break
        grid = [[int(x) for x in input().strip().split()] for _ in range(rows)]

        numbers = []
        while len(numbers) < 2 or (numbers[-1], numbers[-2]) != (-1, -1):
            numbers.extend([int(x) - 1 for x in input().strip().split()])
        moves = ((numbers[i * 2], numbers[i * 2 + 1]) for i in range(len(numbers) // 2 - 1))

        for r, c in moves:
            cc = get_connected_region(grid, r, c)
            if len(cc) <= 1:
                continue
            erase_cells(grid, cc)

        grid_id += 1
        if grid_id > 1:
            print()
        print(f'Grid {grid_id}.')
        if all(len(row) == 0 for row in grid):
            print('    Game Won')
        else:
            print_grid(grid, rows, columns)


if __name__ == '__main__':
    main()
