S_TETRINO = [
    [1, 1, 0],
    [0, 1, 1],
    [0, 0, 0],
]
T_TETRINO = [
    [1, 1, 1],
    [0, 1, 0],
    [0, 0, 0],
]


def rotate(mat):
    return list(zip(*mat[::-1]))


def transpose(mat):
    return list(zip(*mat))


def print_piece(mat):
    res = []
    for r, row in enumerate(mat):
        for c, cell in enumerate(row):
            if cell:
                res.append((r, c))
    min_r = min(r for r, c in res)
    min_c = min(c for r, c in res)
    return [(r - min_r, c - min_c) for r, c in res]


def pretty_print(mat):
    for row in mat:
        print(" ".join("O" if x else " " for x in row))


def make_all():
    res = []
    tetrino = S_TETRINO
    for _ in range(2):
        res.append(print_piece(tetrino))
        pretty_print(tetrino)
        tetrino = rotate(tetrino)
    tetrino = transpose(tetrino)
    for _ in range(2):
        res.append(print_piece(tetrino))
        pretty_print(tetrino)
        tetrino = rotate(tetrino)

    tetrino = T_TETRINO
    for _ in range(4):
        res.append(print_piece(tetrino))
        pretty_print(tetrino)
        tetrino = rotate(tetrino)

    return res


def main():
    res = make_all()
    print(",".join("{" + ",".join(str(r) for r, c in tetrino) + "}" for tetrino in res))
    print(",".join("{" + ",".join(str(c) for r, c in tetrino) + "}" for tetrino in res))


if __name__ == "__main__":
    main()
