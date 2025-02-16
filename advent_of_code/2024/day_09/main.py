def read_input():
    return list(map(int, input().strip()))


def part_1(disk):
    disk_location = 0
    empty_spaces = []
    full_spaces = []
    for i, length in enumerate(disk):
        for _ in range(length):
            if i % 2 == 0:
                full_spaces.append((disk_location, i // 2))
            else:
                empty_spaces.append(disk_location)
            disk_location += 1

    res = []
    empty_spaces = list(reversed(empty_spaces))
    for disk_location, file_id in reversed(full_spaces):
        if empty_spaces[-1] < disk_location:
            disk_location = empty_spaces.pop()
        res.append((disk_location, file_id))

    return sum(i * x for i, x in res)


def part_2(disk):
    disk_location = 0
    empty_spaces = []
    files = []
    for i, length in enumerate(disk):
        if i % 2 == 0:
            files.append((disk_location, length, i // 2))
        else:
            empty_spaces.append((disk_location, length))
        disk_location += length

    res = []
    for disk_location, length, file_id in reversed(files):
        while len(empty_spaces) > 0 and empty_spaces[-1][0] > disk_location:
            empty_spaces.pop()

        found = next(
            (
                i
                for i, (empty_location, empty_length) in enumerate(empty_spaces)
                if empty_length >= length
            ),
            None,
        )
        if found is not None:
            disk_location, empty_length = empty_spaces[found]
            empty_location = disk_location + length
            empty_length -= length
            empty_spaces[found] = empty_location, empty_length

        for i in range(length):
            res.append((disk_location + i, file_id))

    return sum(i * x for i, x in res)


def main():
    disk = read_input()
    print("part1:", part_1(disk))
    print("part2:", part_2(disk))


if __name__ == "__main__":
    main()
