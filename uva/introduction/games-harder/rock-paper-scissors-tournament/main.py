SIGN_BEATS = {
    'rock': 'paper',
    'paper': 'scissors',
    'scissors': 'rock'
}


def solve (n_players, k_games):
    wins = [0] * n_players
    losses = [0] * n_players
    for _ in range(k_games * n_players * (n_players - 1) // 2):
        player_a, move_a, player_b, move_b = input().strip().split()
        player_a, player_b = (int(x) - 1 for x in (player_a, player_b))
        if SIGN_BEATS[move_a] == move_b:
            wins[player_b] += 1
            losses[player_a] += 1
        elif SIGN_BEATS[move_b] == move_a:
            wins[player_a] += 1
            losses[player_b] += 1

    return wins, losses


def main ():
    tc = 0
    while True:
        line = input().strip()
        if line == '0':
            break
        n, k = (int(x) for x in line.split())
        wins, losses = solve(n, k)

        if tc > 0:
            print()
        tc += 1
        for w, l in zip(wins, losses):
            if w + l == 0:
                print('-')
            else:
                print(f'{(w / (w + l)):.3f}')


if __name__ == '__main__':
    main()
