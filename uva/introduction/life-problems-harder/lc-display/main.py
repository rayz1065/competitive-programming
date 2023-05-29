NUMBERS = [
    ' - ', '   ', ' - ', ' - ', '   ', ' - ', ' - ', ' - ', ' - ', ' - ',
    '| |', '  |', '  |', '  |', '| |', '|  ', '|  ', '  |', '| |', '| |',
    '   ', '   ', ' - ', ' - ', ' - ', ' - ', ' - ', '   ', ' - ', ' - ',
    '| |', '  |', '|  ', '  |', '  |', '  |', '| |', '  |', '| |', '  |',
    ' - ', '   ', ' - ', ' - ', '   ', ' - ', ' - ', '   ', ' - ', ' - ',
]


def number_rows (digit):
    for k in range(len(NUMBERS) // 10):
        yield NUMBERS[(digit + k * 10)]


def get_segments (digit):
    for i, row in enumerate(number_rows(digit)):
        for j, cell in enumerate(row):
            if cell == '-':
                yield i // 2, None, cell
            if cell == '|':
                yield i // 2, j // 2, cell


def resize_digit (digit, scale):
    # this is overly complicated
    square_size = scale + 1
    height = square_size * 2 + 1
    width = square_size + 1

    result = [[' '] * width for _ in range(height)]
    for row, column, segment in get_segments(digit):
        if segment == '-':
            for j in range(1, square_size):
                result[row * (scale + 1)][j] = '-'
        else:
            for i in range(1, square_size):
                result[row * (scale + 1) + i][column * square_size] = '|'

    return [''.join(x) for x in result]


def print_number (scale, number):
    resized_digits = [resize_digit(int(digit), scale) for digit in number]

    for r in range(len(resized_digits[0])):
        for i, digit in enumerate(resized_digits):
            if i > 0:
                print(end=' ')
            print(digit[r], end='')
        print()
    print()


def main ():
    while True:
        scale, number = input().strip().split()
        scale = int(scale)
        if scale == 0:
            break
        print_number(scale, number)


if __name__ == '__main__':
    main()
