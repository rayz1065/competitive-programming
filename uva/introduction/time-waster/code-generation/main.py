OPERATORS_MAP = {
    '+': 'A',
    '-': 'S',
    '*': 'M',
    '/': 'D',
    '@': 'N',
}

def generate_code (line):
    stack = []
    operations = []
    temp_var_idx = 0
    register = None
    free_temp_variables = []


    def get_temp_var ():
        nonlocal temp_var_idx, free_temp_variables

        if len(free_temp_variables) > 0:
            return free_temp_variables.pop()

        curr_idx = temp_var_idx
        temp_var_idx += 1
        return f'${curr_idx}'


    def load_variable (variable):
        nonlocal register, operations, stack
        if variable == register:
            return

        if register is not None:
            # store the variable for later
            temp_var = get_temp_var()
            stack_idx = stack.index(register)
            stack[stack_idx] = temp_var
            operations.append(f'ST {temp_var}')

        operations.append(f'L {variable}')
        register = variable


    def pop_stack ():
        nonlocal stack, free_temp_variables
        variable = stack.pop()
        if isinstance(variable, str) and variable.startswith('$'):
            free_temp_variables.append(variable)
        return variable


    for i, operator in enumerate(line):
        if operator not in OPERATORS_MAP:
            stack.append(operator)
            continue

        if operator in '+-*/':
            if stack[-1] == register and operator != '/':
                # can commute, or commutes through negation
                stack[-1], stack[-2] = stack[-2], stack[-1]
                if operator == '-':
                    operations.append('N')
                    operator = '+'

            load_variable(stack[-2])
            op_2 = pop_stack()
            op_1 = pop_stack()

            operations.append(f'{OPERATORS_MAP[operator]} {op_2}')

        elif operator == '@':
            load_variable(stack[-1])
            op_1 = pop_stack()

            operations.append(f'{OPERATORS_MAP[operator]}')

        temp_var = f'res_{i}'
        register = temp_var
        stack.append(temp_var)

    if register is None:
        load_variable(stack[-1])

    return operations


def main ():
    tc = 0
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        tc += 1
        if tc > 1:
            print()
        print('\n'.join(generate_code(line)))


if __name__ == '__main__':
    main()
