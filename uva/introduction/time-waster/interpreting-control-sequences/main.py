DISPLAY_SIZE = 10


def tokenize (instructions):
    i = 0
    while i < len(instructions):
        instruction_len = None
        if instructions[i] != '^':
            instruction_len = 1
        elif '0' <= instructions[i + 1] <= '9':
            instruction_len = 3
        else:
            instruction_len = 2
        yield instructions[i:i + instruction_len]
        i += instruction_len


def get_empty_screen ():
    return [[' '] * DISPLAY_SIZE for _ in range(DISPLAY_SIZE)]


def execute_instructions (all_instructions):
    # overwrite: replaces current character
    # insert: shifts current and next characters to the right, then writes
    mode = 'o'
    screen = get_empty_screen()
    cursor_r, cursor_c = 0, 0

    for instruction in tokenize(all_instructions):
        if len(instruction) == 1 or instruction == '^^':
            character = instruction[0]
            if mode == 'o':
                # overwrite
                screen[cursor_r][cursor_c] = character
            else:
                # insert
                for c in reversed(range(cursor_c + 1, DISPLAY_SIZE)):
                    screen[cursor_r][c] = screen[cursor_r][c - 1]
                screen[cursor_r][cursor_c] = character
            cursor_c = min(cursor_c + 1, DISPLAY_SIZE - 1)

        elif instruction[1] in 'hbdulr':
            CURSOR_POSITIONS = {
                'h': (0, 0),
                'b': (cursor_r, 0),
                'd': (cursor_r + 1, cursor_c),
                'u': (cursor_r - 1, cursor_c),
                'l': (cursor_r, cursor_c - 1),
                'r': (cursor_r, cursor_c + 1),
            }
            cursor_r, cursor_c = (max(min(x, DISPLAY_SIZE - 1), 0)
                                  for x in CURSOR_POSITIONS[instruction[1]])
        elif len(instruction) == 3:
            cursor_r, cursor_c = int(instruction[1]), int(instruction[2])

        elif instruction[1] == 'c':
            screen = get_empty_screen()
        elif instruction[1] == 'e':
            for c in range(cursor_c, len(screen[cursor_r])):
                screen[cursor_r][c] = ' '

        elif instruction[1] in 'io':
            mode = instruction[1]
        else:
            print(f'{instruction} not recognized')

    return screen


def print_screen (screen):
    print('+----------+')
    for line in screen:
        print(f'|{"".join(line)}|')
    print('+----------+')


def main ():
    tc = 0
    while True:
        n_instructions = int(input().strip())
        if n_instructions == 0:
            break
        instructions = ''.join(input() for _ in range(n_instructions))
        screen = execute_instructions(instructions)

        tc += 1
        print(f'Case {tc}')
        print_screen(screen)


if __name__ == '__main__':
    main()
