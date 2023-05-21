BOARD_SHAPE = [
    '  ###  ',
    '  ###  ',
    '#######',
    '#######',
    '#######',
    '  ###  ',
    '  ###  ',
]
MOV = [(-1, 0), (1, 0), (0, -1), (0, 1)]
PEGS_JUMPED_AT_MOST = 1

def compute_board_values ():
    res = [
        [0 for _ in row]
        for row in BOARD_SHAPE
    ]
    acc = 1
    for r, row in enumerate(BOARD_SHAPE):
        for c, cell in enumerate(row):
            if cell == '#':
                res[r][c] = acc
                acc += 1
    return res

BOARD_VALUES = compute_board_values()
VALUES_MAP = { cell: (r, c) for r, row in enumerate(BOARD_VALUES)
                            for c, cell in enumerate(row)
                            if cell != 0 }
def in_range (r, c):
    return 0 <= r < len(BOARD_VALUES) and 0 <= c < len(BOARD_VALUES[r]) and \
        BOARD_VALUES[r][c] != 0


def print_grid (grid):
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            content = '#' if cell else '.'
            cell = content if in_range(r, c) else ' '
            print(cell, end='')
        print()
    print()


def find_moves_at (grid, pos):
    moves = []
    r, c = pos
    for dr, dc in MOV:
        # find occupied cell followed by empty
        r_new, c_new = r + dr, c + dc
        if not in_range(r_new, c_new) or not grid[r_new][c_new]:
            continue
        jumps = 0
        while in_range(r_new, c_new) and grid[r_new][c_new]:
            jumps += 1
            r_new, c_new = r_new + dr, c_new + dc
        if not in_range(r_new, c_new) or jumps > PEGS_JUMPED_AT_MOST:
            continue
        moves.append((r_new, c_new))
    return moves


def find_move (grid):
    best_target, best_source = 0, 0
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if not cell:
                continue

            source = BOARD_VALUES[r][c]
            moves = find_moves_at(grid, (r, c))
            if len(moves) == 0:
                continue

            # apply criteria for move
            for r_new, c_new in moves:
                target = BOARD_VALUES[r_new][c_new]
                if target < best_target:
                    continue
                if target == best_target and source < best_source:
                    continue
                best_target, best_source = target, source

    return best_target, best_source


def apply_move (grid, source, target):
    r, c = VALUES_MAP[source]
    to_r, to_c = VALUES_MAP[target]
    dr = (to_r - r) // max(1, abs(to_r - r))
    dc = (to_c - c) // max(1, abs(to_c - c))

    while (r, c) != (to_r, to_c):
        grid[r][c] = 1 - grid[r][c]
        r, c = r + dr, c + dc
    grid[r][c] = 1 - grid[r][c]


def solve (case):
    grid = [[0] * len(row) for row in BOARD_SHAPE]
    for cell in case:
        r, c = VALUES_MAP[cell]
        grid[r][c] = 1

    while True:
        best_target, best_source = find_move(grid)
        if best_target == 0:
            break
        apply_move(grid, best_source, best_target)

    res = sum(BOARD_VALUES[r][c] for r, row in enumerate(grid)
                                 for c, cell in enumerate(row)
                                 if cell)
    print(res)


def main ():
    input()
    numbers = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        numbers.extend(int(x) for x in line.split())

    cases = [[]]
    for number in numbers:
        if number == 0:
            cases.append([])
        else:
            cases[-1].append(number)
    cases.pop()

    print('HI Q OUTPUT')
    for case in cases:
        solve(case)
    print('END OF OUTPUT')


if __name__ == '__main__':
    main()
