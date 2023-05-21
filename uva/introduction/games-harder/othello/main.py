import itertools

MOV = [ (x, y) for x in range(-1, 2) for y in range(-1, 2) if abs(x) + abs(y) > 0 ]
OTHER_PLAYER = { 'B': 'W', 'W': 'B' }

def print_state (state):
    for row in state:
        print(''.join(row))


def in_range (x, y):
    return 0 <= x < 8 and 0 <= y < 8


def swap_cells (state, player, pos):
    x, y = pos
    other_player = OTHER_PLAYER[player]
    for dx, dy in MOV:
        new_x, new_y = x + dx, y + dy
        if not in_range(new_x, new_y) or state[new_x][new_y] != other_player:
            continue
        while in_range(new_x, new_y) and state[new_x][new_y] == other_player:
            new_x, new_y = new_x + dx, new_y + dy
        if not in_range(new_x, new_y) or state[new_x][new_y] != player:
            continue

        while (new_x, new_y) != (x, y):
            state[new_x][new_y] = player
            new_x, new_y = new_x - dx, new_y - dy


def is_legal_move (state, player, pos):
    x, y = pos
    if state[x][y] != '-':
        return False
    other_player = OTHER_PLAYER[player]

    for dx, dy in MOV:
        new_x, new_y = x + dx, y + dy
        if not in_range(new_x, new_y) or state[new_x][new_y] != other_player:
            continue
        while in_range(new_x, new_y) and state[new_x][new_y] == other_player:
            new_x, new_y = new_x + dx, new_y + dy
        if not in_range(new_x, new_y) or state[new_x][new_y] != player:
            continue
        return True

    return False


def get_legal_moves (state, player):
    for x, y in itertools.product(range(8), range(8)):
        if is_legal_move(state, player, (x, y)):
            yield x, y


def solve ():
    state = [list(input().strip()) for _ in range(8)]
    player = input().strip()
    moves = []
    while len(moves) == 0 or moves[-1] != 'Q':
        moves.append(input().strip())

    for move in moves:
        if move == 'L':
            legal_moves = list(get_legal_moves(state, player))
            if len(legal_moves) == 0:
                print('No legal move.')
            else:
                print(' '.join(f'({x + 1},{y + 1})' for x, y in legal_moves))
        elif move[0] == 'M':
            x, y = (int(x) - 1 for x in move[1:])
            if not is_legal_move(state, player, (x, y)):
                player = OTHER_PLAYER[player]

            swap_cells(state, player, (x, y))
            state[x][y] = player
            player = OTHER_PLAYER[player]

            cell_counts = {
                'W': sum(x == 'W' for row in state for x in row),
                'B': sum(x == 'B' for row in state for x in row),
            }
            print(f'Black - {str(cell_counts["B"]).rjust(2)} '
                  f'White - {str(cell_counts["W"]).rjust(2)}')

    print_state(state)


t = int(input().strip())
for i in range(t):
    if i > 0:
        print()
    solve()
