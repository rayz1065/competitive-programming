KNIGHTS_MOVEMENTS = [
    (r, c) for r in range(-2, +3) for c in range(-2, +3) if abs(r) + abs(c) == 3
]
PAWNS_MOVEMENTS = {
    "b": [(+1, -1), (+1, +1)],
    "w": [(-1, -1), (-1, +1)],
}
RAYS = {
    "b": [(r, c) for r in range(-1, 2) for c in range(-1, 2) if abs(r) + abs(c) == 2],
    "r": [(r, c) for r in range(-1, 2) for c in range(-1, 2) if abs(r) + abs(c) == 1],
    "q": [(r, c) for r in range(-1, 2) for c in range(-1, 2) if abs(r) + abs(c) > 0],
}


def find_piece(board, target):
    for r, row in enumerate(board):
        for c, cell in enumerate(row):
            if cell == target:
                return (r, c)

    return None


def in_range(r, c):
    return 0 <= r < 8 and 0 <= c < 8


def get_team(cell):
    piece = cell.lower()
    if piece == ".":
        return "."

    return "b" if cell == piece else "w"


def find_targets(board, r, c):
    piece = board[r][c].lower()
    team = get_team(board[r][c])
    if piece == ".":
        return

    if piece == "n":
        for dr, dc in KNIGHTS_MOVEMENTS:
            new_r, new_c = r + dr, c + dc
            if not in_range(new_r, new_c) or get_team(board[new_r][new_c]) == team:
                continue
            yield new_r, new_c

        return

    if piece == "p":
        for dr, dc in PAWNS_MOVEMENTS[team]:
            new_r, new_c = r + dr, c + dc
            if not in_range(new_r, new_c) or get_team(board[new_r][new_c]) == team:
                continue
            yield new_r, new_c

        return

    assert piece in RAYS
    for dr, dc in RAYS[piece]:
        for dist in range(1, 8):
            new_r, new_c = r + dr * dist, c + dc * dist
            if not in_range(new_r, new_c) or get_team(board[new_r][new_c]) == team:
                break

            yield new_r, new_c

            if board[new_r][new_c] != ".":
                break


def solve(board):
    queen_position = find_piece(board, "q")
    for r, row in enumerate(board):
        for c, cell in enumerate(row):
            if get_team(board[r][c]) != "w":
                continue

            if queen_position in set(find_targets(board, r, c)):
                return True

    return False


def visualize(background="."):
    start_r, start_c = 0, 0
    for cell in "QRNPBp":
        board = [[background for _ in range(8)] for _ in range(8)]
        board[start_r][start_c] = cell
        board = ["".join(row) for row in board]
        targets = set(find_targets(board, start_r, start_c))
        for r, row in enumerate(board):
            for c, cell in enumerate(row):
                cell_str = "*" if (r, c) in targets else cell
                print(cell_str, end="")
            print()
        print()


def main():
    t = int(input().strip())
    for _ in range(t):
        input()
        board = [input().strip() for _ in range(8)]

        print("YES" if solve(board) else "NO")


if __name__ == "__main__":
    main()
