from functools import cache
import re

DIRECTIONAL = {(-1, 0): "^", (1, 0): "v", (0, -1): "<", (0, 1): ">"}
KEYBOARDS = [
    [
        ["7", "8", "9"],
        ["4", "5", "6"],
        ["1", "2", "3"],
        [None, "0", "A"],
    ],
    [
        [None, "^", "A"],
        ["<", "v", ">"],
    ],
]


@cache
def find_letter(keyboard_id, letter):
    keyboard = KEYBOARDS[keyboard_id]
    for r, row in enumerate(keyboard):
        for c, cell in enumerate(row):
            if letter == cell:
                return r, c


def in_range(keyboard, r, c):
    return keyboard[r][c] is not None


@cache
def get_paths(keyboard_id, source, dest):
    if source == dest:
        return [""]

    keyboard = KEYBOARDS[keyboard_id]
    r, c = source
    dr, dc = dest[0] - r, dest[1] - c
    dr //= max(abs(dr), 1)
    dc //= max(abs(dc), 1)

    res = []
    if dr and in_range(keyboard, r + dr, c):
        for x in get_paths(keyboard_id, (r + dr, c), dest):
            res.append(DIRECTIONAL[dr, 0] + x)
    if dc and in_range(keyboard, r, c + dc):
        for x in get_paths(keyboard_id, (r, c + dc), dest):
            res.append(DIRECTIONAL[0, dc] + x)

    return res


@cache
def optimize(robot_id, sequence, robots_count=4):
    if robot_id == robots_count:
        return len(sequence)

    keyboard_id = min(1, robot_id)
    position = find_letter(keyboard_id, "A")
    res = 0

    for letter in sequence:
        letter_cost = None
        target = find_letter(keyboard_id, letter)
        for path in get_paths(keyboard_id, position, target):
            path += "A"
            path_sequence = optimize(robot_id + 1, path, robots_count=robots_count)
            if letter_cost is None or path_sequence < letter_cost:
                letter_cost = path_sequence
        res += letter_cost
        position = target

    return res


def read_input():
    res = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        res.append(line)
    return res


def part_1(sequences):
    return sum(optimize(0, sequence, 3) * int(sequence[:-1]) for sequence in sequences)


def part_2(sequences):
    return sum(optimize(0, sequence, 26) * int(sequence[:-1]) for sequence in sequences)


def main():
    sequences = read_input()
    print("part1:", part_1(sequences))
    print("part2:", part_2(sequences))


if __name__ == "__main__":
    main()
