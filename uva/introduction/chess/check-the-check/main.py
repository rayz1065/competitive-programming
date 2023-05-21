MOV = [
    # vertical and horizontal
    (-1, 0), (1, 0), (0, 1), (0, -1),
    # diagonal up
    (-1, -1), (-1, 1),
    # diagonal down
    (1, -1), (1, 1)
]
KNIGHT_MOV = [
    (dr, dc)
    for dr in range(-2, 3)
    for dc in range(-2, 3)
    if abs(dr) + abs(dc) == 3
]
MOVEMENTS = {
    'r': (MOV[0:4], 8),
    'b': (MOV[4:8], 8),
    'q': (MOV, 8),
    'k': (MOV, 1),
    'p': (MOV[6:8], 1),
    'P': (MOV[4:6], 1),
    'n': (KNIGHT_MOV, 1)
}


def in_range (r, c):
    return 0 <= r < 8 and 0 <= c < 8


def get_team (x):
    if x == '.':
        return None
    return 'W' if x.upper() == x else 'B'


def compute_ray (board, pos, direction, max_dist=8):
    r, c = pos
    dr, dc = direction
    team = get_team(board[r][c])
    for dist in range(1, max_dist + 1):
        new_r, new_c = r + dr * dist, c + dc * dist
        if not in_range(new_r, new_c) or team == get_team(board[new_r][new_c]):
            break
        yield new_r, new_c
        if board[new_r][new_c] != '.':
            break


def get_movements (board, pos):
    '''Movement of piece in pos'''
    r, c = pos
    piece = board[r][c]
    target_cells = []

    if piece in MOVEMENTS:
        directions, max_dist = MOVEMENTS[piece]
    else:
        directions, max_dist = MOVEMENTS[piece.lower()]

    for direction in directions:
        target_cells.extend(compute_ray(board, pos, direction, max_dist=max_dist))

    return target_cells


def compute_attacked_cells (board):
    res = set()
    for r in range(8):
        for c in range(8):
            if board[r][c] == '.':
                continue
            movements = get_movements(board, (r, c))
            res.update(movements)

    return res

tc = 0
while True:
    tc += 1
    board = [input().strip() for _ in range(8)]
    if len(set(x for line in board for x in line)) == 1:
        break # empty board
    input() # empty line

    attacked_cells = compute_attacked_cells(board)
    kings = { get_team(cell): (r, c) for r, row in enumerate(board)
                                     for c, cell in enumerate(row)
                                     if cell.lower() == 'k' }

    if kings['W'] in attacked_cells:
        print(f'Game #{tc}: white king is in check.')
    elif kings['B'] in attacked_cells:
        print(f'Game #{tc}: black king is in check.')
    else:
        print(f'Game #{tc}: no king is in check.')
