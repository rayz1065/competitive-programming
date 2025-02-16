def read_input():
    lines = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        lines.append(line)

    lines.append("")
    curr = []
    keys, locks = [], []
    for line in lines:
        if line == "" and "." not in curr[0]:
            locks.append(curr)
            curr = []
        elif line == "":
            keys.append(curr)
            curr = []
        else:
            curr.append(line)

    return keys, locks


def get_height(grid):
    res = [0] * len(grid[0])
    for row in grid:
        for i, cell in enumerate(row):
            res[i] += cell == "#"
    return [x - 1 for x in res]


def can_fit(key, lock):
    return all(k + l <= 5 for k, l in zip(key, lock))


def part_1(keys, locks):
    keys = list(map(get_height, keys))
    locks = list(map(get_height, locks))

    res = 0
    for key in keys:
        for lock in locks:
            res += can_fit(key, lock)

    return res


def main():
    keys, locks = read_input()
    print("part_1:", part_1(keys, locks))


if __name__ == "__main__":
    main()
