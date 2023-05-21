import re


def solve (grid, extractions):
    called = [[False] * len(grid) for _ in enumerate(grid)]
    called[2][2] = True
    numbers = { x: (r, c) for r, row in enumerate(grid)
                for c, x in enumerate(row) }

    for extraction_id, extraction in enumerate(extractions):
        if extraction not in numbers:
            continue
        r, c = numbers[extraction]
        called[r][c] = True
        if all(called[i][c] for i in range(5)):
            return extraction_id
        if all(called[r]):
            return extraction_id

        if all(called[i][i] for i in range(5)):
            return extraction_id
        if all(called[i][4 - i] for i in range(5)):
            return extraction_id

    return -1


def get_numbers (line):
    return [int(x) for x in re.findall(r'\d+', line)]


def main ():
    t = int(input().strip())
    for _ in range(t):
        grid = [[int(x) for x in get_numbers(input())] for _ in range(5)]
        grid[2] = grid[2][:2] + [-1] + grid[2][2:]
        extractions = []
        while len(extractions) < 75:
            extractions.extend(get_numbers(input()))
        extraction_id = solve(grid, extractions)
        print(f'BINGO after {extraction_id + 1} numbers announced')


if __name__ == '__main__':
    main()
