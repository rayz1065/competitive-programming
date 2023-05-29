ASSEMBLY_CODES = {
    '0': ('ADD', (['R','A','N'],['R','A'])),
    '1': ('SUB', (['R','A','N'],['R','A'])),
    '2': ('MUL', (['R','A','N'],['R','A'])),
    '3': ('DIV', (['R','A','N'],['R','A'])),
    '4': ('MOV', (['R','A','N'],['R','A'])),
    '5': ('BREQ', ('A',)),
    '6': ('BRLE', ('A',)),
    '7': ('BRLS', ('A',)),
    '8': ('BRGE', ('A',)),
    '9': ('BRGR', ('A',)),
    'A': ('BRNE', ('A',)),
    'B': ('BR', ('A',)),
    'C': ('AND', (['R','A','N'],['R','A','N'],['R','A'])),
    'D': ('OR', (['R','A','N'],['R','A','N'],['R','A'])),
    'E': ('XOR', (['R','A','N'],['R','A','N'],['R','A'])),
    'F': ('NOT', (['R','A'],)),
}


def read_assembled ():
    code = []
    while True:
        try:
            line = input()
        except EOFError:
            break
        code.append(line)
    return ''.join(code)


def get_operations (code):
    i = 0
    while i < len(code):
        op_code = code[i]
        op_name, arguments = ASSEMBLY_CODES[op_code]
        values = [code[i + 1 + j * 4:i + 1 + (j + 1) * 4]
                  for j in range(len(arguments))]
        yield op_name, values
        i += 1 + len(arguments) * 4
    assert i == len(code)


def split_operator (operator):
    operator = int(operator, base=16)
    mode = operator >> 14 # first 2 bits
    value = operator - (mode << 14)
    return mode, value


def pretty_operator (mode, value):
    if mode == 0:
        # register
        return f'R{value}'
    if mode == 1:
        # absolute
        return f'${value}'
    if mode == 2:
        # pc-relative
        return f'PC+{value}'

    assert mode == 3
    return f'{value}'


def main ():
    code = read_assembled()
    for op_name, values in get_operations(code):
        operators = (pretty_operator(*split_operator(x)) for x in values)
        print(op_name, ','.join(operators))


if __name__ == '__main__':
    main()
