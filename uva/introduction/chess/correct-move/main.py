def num_to_coord (pos):
    return (pos // 8, pos % 8)

def in_range (x, y):
    return 0 <= x < 8 and 0 <= y < 8

def adj (pos, max_dist=1):
    x, y = pos
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        for _ in range(max_dist):
            new_x, new_y = x + dx, y + dy
            if not in_range(new_x, new_y):
                break
            yield new_x, new_y

def cells_in_path (pos1, pos2):
    dx, dy = pos2[0] - pos1[0], pos2[1] - pos1[1]
    dx //= max(abs(dx), 1)
    dy //= max(abs(dy), 1)
    x, y = pos1
    while not (x == pos2[0] and y == pos2[1]):
        x, y = x + dx, y + dy
        yield x, y

while True:
    try:
        line = input().strip()
    except EOFError:
        break
    king, queen, queen_move = (num_to_coord(int(x)) for x in line.split())

    if king == queen:
        print('Illegal state')
    elif (queen == queen_move) or (queen[0] != queen_move[0] and queen[1] != queen_move[1]):
        print('Illegal move')
    elif king in set(cells_in_path(queen, queen_move)):
        print('Illegal move')
    elif queen_move in list(adj(king)):
        print('Move not allowed')
    elif len(set(adj(king)) - set(adj(queen_move, 8))) == 0:
        print('Stop')
    else:
        print('Continue')
