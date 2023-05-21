def normalize_word (word):
    return ''.join(word).split('*', maxsplit=1)[0]


def find_words (grid):
    next_number = 1
    across = []
    down = []
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if cell == '*':
                continue

            found = False
            if c == 0 or row[c - 1] == '*':
                # find across
                found = True
                word = row[c:]
                across.append((next_number, normalize_word(word)))
            if r == 0 or grid[r - 1][c] == '*':
                # find down
                found = True
                word = [grid[r2][c] for r2 in range(r, len(grid))]
                down.append((next_number, normalize_word(word)))

            if found:
                next_number += 1

    return (across, down)


def main ():
    puzzle_id = 0
    while True:
        line = input().strip()
        if line == '0':
            break
        rows, _ = (int(x) for x in line.split())
        grid = [input().strip() for _ in range(rows)]

        across, down = find_words(grid)

        puzzle_id += 1
        if puzzle_id > 1:
            print()
        print(f'puzzle #{puzzle_id}:')
        print('Across')
        for assigned_number, word in across:
            assigned_number = str(assigned_number).rjust(3)
            print(f'{assigned_number}.{word}')
        print('Down')
        for assigned_number, word in down:
            assigned_number = str(assigned_number).rjust(3)
            print(f'{assigned_number}.{word}')

if __name__ == '__main__':
    main()
