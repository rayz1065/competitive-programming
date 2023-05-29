import re

CHARACTERS = [
    ' ***  ', '****  ', ' **** ', '****  ', '***** ', '***** ', ' **** ', '*   * ', '***** ',
    '*   * ', '*   * ', '*   * ', '*   * ', '*     ', '*     ', '*     ', '*   * ', '  *   ',
    '***** ', '****  ', '*     ', '*   * ', '***   ', '***   ', '*  ** ', '***** ', '  *   ',
    '*   * ', '*   * ', '*     ', '*   * ', '*     ', '*     ', '*   * ', '*   * ', '  *   ',
    '*   * ', '****  ', ' **** ', '****  ', '***** ', '*     ', ' ***  ', '*   * ', '***** ',

    '  *** ', '*   * ', '*     ', '*   * ', '*   * ', ' ***  ', '****  ', ' ***  ', '****  ',
    '   *  ', '*  *  ', '*     ', '** ** ', '**  * ', '*   * ', '*   * ', '*   * ', '*   * ',
    '   *  ', '***   ', '*     ', '* * * ', '* * * ', '*   * ', '****  ', '*   * ', '****  ',
    '*  *  ', '*  *  ', '*     ', '*   * ', '*  ** ', '*   * ', '*     ', '*  ** ', '*  *  ',
    ' **   ', '*   * ', '***** ', '*   * ', '*   * ', ' ***  ', '*     ', ' **** ', '*   * ',

    ' **** ', '***** ', '*   * ', '*   * ', '*   * ', '*   * ', '*   * ', '***** ', '      ',
    '*     ', '* * * ', '*   * ', '*   * ', '*   * ', ' * *  ', ' * *  ', '   *  ', '      ',
    ' ***  ', '  *   ', '*   * ', ' * *  ', '* * * ', '  *   ', '  *   ', '  *   ', '      ',
    '    * ', '  *   ', '*   * ', ' * *  ', '** ** ', ' * *  ', '  *   ', ' *    ', '      ',
    '****  ', ' ***  ', ' ***  ', '  *   ', '*   * ', '*   * ', '  *   ', '***** ', '      ',
]
CHARACTERS_GRID = [
    'ABCDEFGHI',
    'JKLMNOPQR',
    'STUVWXYZ '
]
CHARACTERS_MAP = {
    char: [CHARACTERS[i * 9 + r * 5 * 9 + c] for i in range(5)]
    for r, row in enumerate(CHARACTERS_GRID)
    for c, char in enumerate(row)
}


def in_range (paper, r, c):
    return 0 <= r < len(paper) and 0 <= c < len(paper[r])


def paper_write (paper, r, c, ink):
    # writes using the ink at the row and column, if possible
    if ink == ' ' or not in_range(paper, r, c):
        return
    paper[r][c] = ink


def print_c5_character (paper, row, column, character):
    for r, character_row in enumerate(CHARACTERS_MAP[character]):
        for c, ink in enumerate(character_row):
            paper_write(paper, row + r, column + c, ink)


def print_c5 (paper, row, column, string):
    for i, character in enumerate(string):
        print_c5_character(paper, row, column + i * 6, character)


def print_c1 (paper, row, column, string):
    for i, ink in enumerate(string):
        paper_write(paper, row, column + i, ink)


def blank_sheet ():
    return [['.'] * 60 for _ in range(60)]


def execute_print (commands):
    paper = blank_sheet()

    for command in commands:
        res = re.match(r'^\.([PLRC])\s*(C1|C5)\s*'   # operation, font
                       r'(?:(\d+))?\s*(?:(\d+))?\s*' # row, column
                       r'\|([^\|]+)\|', command)     # string
        assert res is not None, f'Failed to parse command {command}'
        operation, font, row, column, string = res.groups()
        row, column = (int(x) if x is not None else None for x in (row, column))

        string_length = len(string)
        if font == 'C5':
            string_length *= 6

        if operation == 'L':
            # left
            column = 1
        elif operation == 'R':
            # right
            column = 61 - string_length
        elif operation == 'C':
            # center
            column = 31 - string_length // 2

        # 0-based indexes
        row -= 1
        column -= 1

        if font == 'C5':
            print_c5(paper, row, column, string)
        else:
            print_c1(paper, row, column, string)

    return paper


def show_paper (paper):
    for row in paper:
        print(''.join(row))
    print()
    print('-' * len(paper[0]))
    print()


def read_commands ():
    while True:
        line = input().strip()
        if line == '.EOP':
            break
        yield line


def main ():
    while True:
        try:
            commands = list(read_commands())
        except EOFError:
            break
        paper = execute_print(commands)
        show_paper(paper)


if __name__ == '__main__':
    main()
