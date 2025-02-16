from functools import cache


def simulate_step(stones):
    res = []
    for stone in stones:
        stone_str = str(stone)
        if stone == 0:
            res.append(1)
        elif len(stone_str) % 2 == 0:
            half_len = len(stone_str) // 2
            res.append(int(stone_str[:half_len]))
            res.append(int(stone_str[half_len:]))
        else:
            res.append(stone * 2024)

    return res


@cache
def solve(stone, steps):
    if steps == 0:
        return 1

    stones = simulate_step([stone])

    return sum(solve(x, steps - 1) for x in stones)


def part_1(stones):
    return sum(solve(x, 25) for x in stones)


def part_2(stones):
    return sum(solve(x, 75) for x in stones)


def read_input():
    return [int(x) for x in input().strip().split()]


def main():
    stones = read_input()
    print("part1:", part_1(stones))
    print("part2:", part_2(stones))


if __name__ == "__main__":
    main()
