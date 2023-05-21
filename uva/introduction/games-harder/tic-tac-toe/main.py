OTHER_PLAYER = { 'X': 'O', 'O': 'X' }


def count_freqs (cells):
    return {
        'X': sum(cell == 'X' for cell in cells),
        'O': sum(cell == 'O' for cell in cells),
    }


def get_tris_player (freqs):
    for player, freq in freqs.items():
        if freq == 3:
            return player
    return None


def get_tris (grid):
    tris = { 'X': 0, 'O': 0 }
    possible_places = [
        *grid,                                         # rows
        *[[row[c] for row in grid] for c in range(3)], # columns
        [grid[r][r] for r in range(3)],                # main diagonal
        [grid[r][2 - r] for r in range(3)],            # secondary diagonal
    ]
    for place in possible_places:
        freqs = count_freqs(place)
        player = get_tris_player(freqs)
        if player is not None:
            tris[player] += 1

    return tris


def main ():
    t = int(input().strip())
    for _ in range(t):
        grid = [input() for _ in range(3)]
        freqs = count_freqs([cell for row in grid for cell in row])
        tris = get_tris(grid)
        last_player = 'X' if freqs['X'] > freqs['O'] else 'O'

        if freqs['O'] > freqs['X'] or abs(freqs['X'] - freqs['O']) > 1:
            # unbalanced moves
            print('no')
        elif tris[OTHER_PLAYER[last_player]]:
            # before last move game already over
            print('no')
        else:
            print('yes')

        try:
            input()
        except EOFError:
            pass


if __name__ == '__main__':
    main()
