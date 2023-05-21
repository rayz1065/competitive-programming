def simulate (n_players, rolls, pipes, special_cells):
    grid = [(None, None)] * 101
    for cell in special_cells:
        grid[abs(cell)] = (cell // max(1, abs(cell)), None)
    for cell_from, cell_to in pipes:
        grid[cell_from] = (None, cell_to)

    players = [0] * n_players
    skip_turn = [False] * n_players
    player_idx = 0

    for roll in rolls:
        while skip_turn[player_idx]:
            skip_turn[player_idx] = False
            player_idx = (player_idx + 1) % n_players

        new_cell = players[player_idx] + roll
        if new_cell > 100:
            # invalid roll
            player_idx = (player_idx + 1) % n_players
            continue

        players[player_idx] = new_cell
        special, pipe = grid[new_cell]

        if pipe is not None:
            players[player_idx] = pipe
        if players[player_idx] == 100:
            # game over
            break

        next_player_idx = (player_idx + 1) % n_players
        if special == +1:
            # player rolls again
            next_player_idx = player_idx
        elif special == -1:
            # next turn skipped
            skip_turn[player_idx] = True

        player_idx = next_player_idx

    return player_idx


def main ():
    rolls = []
    while len(rolls) == 0 or rolls[-1] != 0:
        rolls.extend(int(x) for x in input().strip().split())
    rolls.pop()

    while True:
        n_players = int(input().strip())
        if n_players == 0:
            break
        pipes = []
        while len(pipes) == 0 or pipes[-1] != (0, 0):
            pipes.append(tuple(int(x) for x in input().strip().split()))
        pipes.pop()

        special_cells = []
        while len(special_cells) == 0 or special_cells[-1] != 0:
            special_cells.append(int(input().strip()))
        special_cells.pop()

        print(simulate(n_players, rolls, pipes, special_cells) + 1)


if __name__ == '__main__':
    main()
