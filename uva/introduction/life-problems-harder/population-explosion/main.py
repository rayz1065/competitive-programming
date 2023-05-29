MAP_SIZE = 20
SEP = '*' * MAP_SIZE


def read_initial_positions ():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        if line == '':
            break

        x, y = (int(x) - 1 for x in line.split())
        yield x, y


def print_state (state):
    for row in state:
        print(''.join(row))
    print(SEP)


def in_range (state, r, c):
    return 0 <= r < len(state) and 0 <= c < len(state[r])


def adj (state, r, c):
    for dr in range(-1, +2):
        for dc in range(-1, +2):
            new_r, new_c = r + dr, c + dc
            if not in_range(state, new_r, new_c) or (dr, dc) == (0, 0):
                continue
            yield new_r, new_c


def simulate (state):
    new_state = [[' '] * MAP_SIZE for _ in range(MAP_SIZE)]
    for r, row in enumerate(state):
        for c, cell in enumerate(row):
            neigh_quarters = sum(state[adj_r][adj_c] == 'O' for adj_r, adj_c in adj(state, r, c))
            if neigh_quarters == 3 or (cell == 'O' and neigh_quarters == 2):
                new_state[r][c] = 'O'

    return new_state


def solve ():
    years = int(input().strip())
    state = [[' '] * MAP_SIZE for _ in range(MAP_SIZE)]
    for x, y in read_initial_positions():
        state[x][y] = 'O'

    for _ in range(years - 1):
        print_state(state)
        state = simulate(state)
    print_state(state)


def main ():
    t = int(input().strip())
    input()
    for tc in range(t):
        print(SEP)
        solve()
        if tc + 1 < t:
            print()


if __name__ == '__main__':
    main()
