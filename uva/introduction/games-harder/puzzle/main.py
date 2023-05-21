def get_empty (grid):
    return next(((r, c) for r, row in enumerate(grid)
                        for c, cell in enumerate(row)
                        if cell == ' '))

def in_range (r, c):
    return 0 <= r < 5 and 0 <= c < 5

MOV = {
    'A': (-1, 0),
    'B': (1, 0),
    'R': (0, 1),
    'L': (0, -1),
}

puzzle_id = 0
while True:
    try:
        state = [list(input().ljust(5)) for _ in range(5)]
    except EOFError:
        break
    moves = []
    while len(moves) == 0 or moves[-1][-1] != '0':
        moves.append(input().strip())
    moves = ''.join(moves)[:-1]

    is_legal = True
    r_empty, c_empty = get_empty(state)
    for move in moves:
        # If move not in MOV -> illegal
        dr, dc = MOV.get(move, (500, 500))
        r_new, c_new = r_empty + dr, c_empty + dc
        if not in_range(r_new, c_new):
            is_legal = False
            break

        # swap
        state[r_empty][c_empty], state[r_new][c_new] = \
            state[r_new][c_new], state[r_empty][c_empty]
        r_empty, c_empty = r_new, c_new

    puzzle_id += 1
    if puzzle_id > 1:
        print()
    print(f'Puzzle #{puzzle_id}:')
    if is_legal:
        print('\n'.join((' '.join(x) for x in state)))
    else:
        print('This puzzle has no final configuration.')
