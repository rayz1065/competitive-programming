from math import isqrt

RIGHT = 0
DOWN = 1
LEFT = 2
UP = 3

MOV_STR = [ '>', 'v', '<', '^' ]

# example
MINIMAP = [
    [0, 0, 1, 0],
    [4, 3, 2, 0],
    [0, 0, 5, 6],
]
MOV_WRAPS = { # new tile, delta dire
    (1, UP): (4, 2),
    (1, RIGHT): (6, 2),
    (1, LEFT): (3, 1),
    (2, RIGHT): (6, 3),
    (3, UP): (1, 3),
    (3, DOWN): (5, 1),
    (4, UP): (1, 2),
    (4, LEFT): (6, 3),
    (4, DOWN): (5, 2),
    (5, LEFT): (3, 3),
    (5, DOWN): (4, 2),
    (6, DOWN): (4, 1),
    (6, UP): (2, 1),
    (6, RIGHT): (1, 2),
}
# input
MINIMAP = [
    [0, 1, 2],
    [0, 3],
    [5, 4],
    [6],
]
MOV_WRAPS = {
    (1, UP): (6, 3),
    (1, LEFT): (5, 2),
    (2, UP): (6, 0),
    (2, RIGHT): (4, 2),
    (2, DOWN): (3, 3),
    (3, RIGHT): (2, 1),
    (3, LEFT): (5, 1),
    (4, RIGHT): (2, 2),
    (4, DOWN): (6, 3),
    (5, UP): (3, 3),
    (5, LEFT): (1, 2),
    (6, LEFT): (1, 1),
    (6, DOWN): (2, 0),
    (6, RIGHT): (4, 1)
}

MOV = [
    (0, 1),
    (1, 0),
    (0, -1),
    (-1, 0),
]

grid = []
tile_size = 0
grid_movs = []

def tokenize_instructions (line):
    line = list(line)
    instructions = []
    curr = 0
    line.append('$')
    for i in range(len(line)):
        if line[i] in "LR$":
            if curr != 0:
                instructions.append(curr)
                curr = 0
            if line[i] in "LR":
                instructions.append(line[i])
        else:
            curr = curr * 10 + ord(line[i]) - ord('0')
    return instructions

def read_input ():
    grid = []
    while True:
        line = input()
        if line == '':
            break
        grid.append(line)
    line = input()
    return grid, tokenize_instructions(line)

def get_tile (r, c):
    r //= tile_size
    c //= tile_size
    if r < 0 or c < 0 or r >= len(MINIMAP) or c >= len(MINIMAP[r]):
        return 0
    return MINIMAP[r][c]

def get_tile_root (tile):
    for r, row in enumerate(MINIMAP):
        for c, x in enumerate(row):
            if x == tile:
                return r * tile_size, c * tile_size

def get_cell (r, c):
    if r < 0 or c < 0 or r >= len(grid) or c >= len(grid[r]):
        return ' '
    return grid[r][c]

def print_movs ():
    for r, row in enumerate(grid):
        for c, x in enumerate(row):
            if grid_movs[r][c] != ' ':
                print(grid_movs[r][c], end='')
            else:
                print(x, end='')
        print()

def front_cell_2 (r, c, dire):
    dr, dc = MOV[dire]
    if get_cell(r + dr, c + dc) != ' ':
        return r + dr, c + dc, dire
    # wrap around the cube
    initial_tile = get_tile(r, c)
    new_tile, rot = MOV_WRAPS[initial_tile, dire]
    relative_r, relative_c = r - get_tile_root(initial_tile)[0], c - get_tile_root(initial_tile)[1]
    # find the appropriate relative coords
    if (rot, dire) == (3, RIGHT):
        r, c = 0, tile_size - relative_r - 1
    elif (rot, dire) in [(3, DOWN), (3, UP)]:
        r, c = relative_c, 0
    elif (rot, dire) in [(2, LEFT), (2, RIGHT)]:
        r, c = tile_size - relative_r - 1, 0
    elif (rot, dire) == (2, DOWN):
        r, c = 0, tile_size - relative_c - 1
    elif (rot, dire) in [(1, LEFT), (1, RIGHT)]:
        r, c = 0, relative_r
    elif (rot, dire) in [(0, UP), (0, DOWN)]:
        r, c = 0, relative_c
    else:
        assert False, f'Unhandled {rot, dire}'
    # transform to global coords
    r += get_tile_root(new_tile)[0]
    c += get_tile_root(new_tile)[1]
    dire = (dire - rot + 4) % 4
    dr, dc = MOV[dire]
    while get_tile(r - dr, c - dc) == new_tile:
        # move backwards until the edge
        r, c = r - dr, c - dc
    return r, c, dire

def front_cell (r, c, dire):
    dr, dc = MOV[dire]
    new_r, new_c = r + dr, c + dc
    if get_cell(new_r, new_c) == ' ':
        # wrap around
        while get_cell(new_r - dr, new_c - dc) != ' ':
            new_r, new_c = new_r - dr, new_c - dc
    return new_r, new_c, dire

def apply_move (r, c, dire, instruction, front_cell_getter):
    global grid_movs
    grid_movs[r][c] = MOV_STR[dire]
    if instruction == 'L':
        return r, c, (dire + 3) % 4
    if instruction == 'R':
        return r, c, (dire + 1) % 4
    for _ in range(instruction):
        new_r, new_c, new_dire = front_cell_getter(r, c, dire)
        if grid[new_r][new_c] == '#':
            break
        r, c, dire = new_r, new_c, new_dire
        grid_movs[r][c] = MOV_STR[dire]
    return r, c, dire

def exec_instructions (instructions, front_cell_getter):
    clear_grid_movs()
    r = 0
    c = next(i for i, x in enumerate(grid[0]) if x == '.')
    dire = RIGHT
    for instruction in instructions:
        r, c, dire = apply_move(r, c, dire, instruction, front_cell_getter)
    return (r + 1) * 1000 + (c + 1) * 4 + dire

def clear_grid_movs ():
    global grid_movs
    grid_movs.clear()
    for r, row in enumerate(grid):
        grid_movs.append([' ' for _ in row])

def main ():
    global grid, tile_size, grid_movs
    grid, instructions = read_input()
    tile_size = isqrt(sum(sum(x in '.#' for x in row) for row in grid) // 6)
    print('part_1:', exec_instructions(instructions, front_cell))
    print('part_2:', exec_instructions(instructions, front_cell_2))

if __name__ == '__main__':
    main()
