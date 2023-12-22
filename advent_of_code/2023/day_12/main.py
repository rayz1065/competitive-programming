import re
from collections import namedtuple

SpringsRow = namedtuple("SpringsRow", ["state", "broken_counts"])


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        res = re.match(r"^([?.#]+)\s+([\d,]+)$", line)
        state = res[1]
        broken_counts = [int(x) for x in res[2].split(",")]
        yield SpringsRow(state, broken_counts)


def match_broken(state, state_idx, count):
    for i in range(count):
        if state_idx + i >= len(state) or state[state_idx + i] == ".":
            return False

    # next must be fixed
    next_ = state[state_idx + count] if state_idx + count < len(state) else "."
    return next_ in "?."


def find_arrangements(row: SpringsRow, state_idx, counts_idx, memo):
    state, counts = row

    if (state_idx, counts_idx) in memo:
        # memoization trick
        return memo[state_idx, counts_idx]

    if state_idx >= len(state):
        return int(counts_idx == len(counts))

    if counts_idx == len(counts) and state[state_idx] == "#":
        # fail
        return 0

    def memoize(result):
        nonlocal state_idx, counts_idx, memo
        memo[state_idx, counts_idx] = result
        return result

    if state[state_idx] == "." or counts_idx == len(counts):
        # only one possibility
        return memoize(find_arrangements(row, state_idx + 1, counts_idx, memo))

    res = 0

    # check that the next ones can all be broken
    if match_broken(state, state_idx, counts[counts_idx]):
        # skip ahead
        res += find_arrangements(
            row, state_idx + counts[counts_idx] + 1, counts_idx + 1, memo
        )

    if state[state_idx] == "?":
        # maybe it's not broken
        res += find_arrangements(row, state_idx + 1, counts_idx, memo)

    return memoize(res)


def part_1(rows: list[SpringsRow]):
    return sum(find_arrangements(row, 0, 0, {}) for row in rows)


def part_2(rows: list[SpringsRow]):
    res = 0
    for row in rows:
        state = "?".join(row.state for _ in range(5))
        counts = row.broken_counts * 5
        row = SpringsRow(state, counts)
        res += find_arrangements(row, 0, 0, {})

    return res


def main():
    rows = list(read_lines())
    print("part_1:", part_1(rows))
    print("part_2:", part_2(rows))


if __name__ == "__main__":
    main()
