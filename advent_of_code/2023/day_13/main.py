def read_lines():
    pattern = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        if line == "":
            yield pattern
            pattern = []
        else:
            pattern.append(line)

    yield pattern


def transpose(pattern):
    return [
        "".join(pattern[i][j] for i in range(len(pattern)))
        for j in range(len(pattern[0]))
    ]


def count_differences(a, b):
    return sum(a_ != b_ for a_, b_ in zip(a, b))


def count_smudges(pattern, row):
    """ "row" indicates the number of rows above this one"""
    assert 0 < row < len(pattern)
    mistakes = 0

    for i in range(row):
        new_i = 2 * row - i - 1
        if new_i < len(pattern):
            mistakes += count_differences(pattern[new_i], pattern[i])

    return mistakes


def get_mirror_value(pattern, target_smudges=0):
    mirror_value = None
    for row in range(1, len(pattern)):
        if count_smudges(pattern, row) == target_smudges:
            assert mirror_value is None
            mirror_value = row * 100

    pattern = transpose(pattern)
    for row in range(1, len(pattern)):
        if count_smudges(pattern, row) == target_smudges:
            assert mirror_value is None
            mirror_value = row

    assert mirror_value is not None
    return mirror_value


def part_1(patterns):
    return sum(get_mirror_value(x, target_smudges=0) for x in patterns)


def part_2(patterns):
    return sum(get_mirror_value(x, target_smudges=1) for x in patterns)


def main():
    patterns = list(read_lines())
    print("part_1:", part_1(patterns))
    print("part_2:", part_2(patterns))


if __name__ == "__main__":
    main()
