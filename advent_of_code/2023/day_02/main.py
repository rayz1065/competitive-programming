import re


AVAILABLE_COLORS = {"red": 12, "green": 13, "blue": 14}


def parse_extraction(extraction):
    colors = extraction.split(", ")
    for color in colors:
        color_info = color.split(" ")
        yield int(color_info[0]), color_info[1]


def get_games():
    try:
        while True:
            line = input().strip()
            if line == "":
                break

            res = re.match(r"^Game (\d+): (.+)$", line)
            game_id = int(res[1])
            extractions = res[2].split("; ")
            extractions = [
                {color: count for count, color in parse_extraction(extraction)}
                for extraction in extractions
            ]

            yield game_id, extractions
    except EOFError:
        pass


def is_possible(extraction):
    for color, count in extraction.items():
        if count > AVAILABLE_COLORS[color]:
            return False

    return True


def get_fewest_cubes(extractions):
    result = {}
    for extraction in extractions:
        for color, count in extraction.items():
            result.setdefault(color, 0)
            result[color] = max(result[color], count)

    return result


def part_1(games):
    res = 0
    for game_id, extractions in games:
        if all(is_possible(x) for x in extractions):
            res += game_id

    return res


def part_2(games):
    res = 0
    for game_id, extractions in games:
        bag = get_fewest_cubes(extractions)
        res += bag["red"] * bag["green"] * bag["blue"]

    return res


def main():
    games = list(get_games())

    print("part_1:", part_1(games))
    print("part_2:", part_2(games))


if __name__ == "__main__":
    main()
