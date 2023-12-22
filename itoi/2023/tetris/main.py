piece_counter = 0


def transpose(grid):
    return [[grid[j][i] for j, _ in enumerate(grid)] for i, _ in enumerate(grid[0])]


def get_next_piece():
    global piece_counter
    piece_counter += 1
    return piece_counter - 1


def place_line(grid, row, column):
    # places a vertical line with bottom left (row, column)
    piece = get_next_piece()
    for i in range(4):
        grid[row + i][column] = piece


def place_square(grid, row, column):
    # places a square with bottom left (row, column)
    piece = get_next_piece()
    for i in range(2):
        grid[row + i][column] = piece
        grid[row + i][column + 1] = piece


def fill_grid(grid, column_from, column_to):
    # assumes the grid has an even number of rows
    if column_to - column_from == 1:
        for row in range(len(grid) // 4):
            place_line(grid, row * 4, column_from)
        return

    if column_to - column_from == 2:
        for row in range(len(grid) // 2):
            place_square(grid, row * 2, column_from)
        return

    for a_column in range(column_from, column_to, 2):
        fill_grid(grid, a_column, min(a_column + 2, column_to))


def main():
    n, m = (int(x) for x in input().strip().split())

    if (n * m) % 4 != 0:
        print(-1)
        return

    grid = [[None] * m for _ in range(n)]

    if n % 2 == 0:
        fill_grid(grid, 0, m)
    else:
        grid = transpose(grid)
        fill_grid(grid, 0, n)
        grid = transpose(grid)

    print(piece_counter)
    for line in grid:
        print(" ".join(str(x) for x in line))


if __name__ == "__main__":
    main()
