COUNT_RECIPES_MEMO = {}


def read_input():
    towels = input().strip().split(", ")
    input()
    res = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        res.append(line)
    return towels, res


def make_design(towels, design):
    if design == "":
        return True
    return any(
        design.startswith(towel) and make_design(towels, design[len(towel) :])
        for towel in towels
    )


def count_recipes(towels, design):
    if design == "":
        return 1
    if design in COUNT_RECIPES_MEMO:
        return COUNT_RECIPES_MEMO[design]
    res = sum(
        count_recipes(towels, design[len(towel) :])
        for towel in towels
        if design.startswith(towel)
    )
    COUNT_RECIPES_MEMO[design] = res
    return res


def part_1(towels, designs):
    return sum(make_design(towels, x) for x in designs)


def part_2(towels, designs):
    return sum(count_recipes(towels, x) for x in designs)


def main():
    towels, designs = read_input()
    print("part1:", part_1(towels, designs))
    print("part2:", part_2(towels, designs))


if __name__ == "__main__":
    main()
