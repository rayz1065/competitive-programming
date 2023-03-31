import sys
from math import log2, floor, ceil

variable_names = []
variables_map = {}
constants_map = {}
operations = {}

def calc_height (variable):
    if variable not in operations:
        assert(isinstance(variable_names[variable], int) or 'out' not in variable_names[variable])
        return 0
    _, op1, op2 = operations[variable]
    return max(calc_height(op1) + 1, calc_height(op2) + 1)

def getv (base = 'tmp', idx = None):
    idx = idx if idx is not None else len(variable_names)
    name = f'{base}[{idx}]'
    if name in variables_map:
        return variables_map[name]
    next_idx = len(variable_names)
    variable_names.append(name)
    variables_map[name] = next_idx
    return next_idx

def getc (value):
    if value in constants_map:
        return constants_map[value]
    next_idx = len(variable_names)
    variable_names.append(value)
    variables_map[value] = next_idx
    return next_idx

def add_operation (res, operator, op1, op2):
    operations[res] = (operator, op1, op2)
    return res

# def sum_circuit (variables):
#     # returns the variable for the sum circuit
#     if len(variables) == 1:
#         return variables[0]
#     # split in half
#     mid = len(variables) // 2
#     op1 = sum_circuit(variables[:mid])
#     op2 = sum_circuit(variables[mid:])
#     return add_operation(getv(), '+', op1, op2)

def range_sum_circuit (i, j):
    if i == j:
        return getv('in', i)
    sz = ceil(log2(j - i + 1)) # first largest power of 2
    mid = i + 2 ** (sz - 1) - 1
    op1 = range_sum_circuit(i, mid)
    op2 = range_sum_circuit(mid + 1, j)
    return add_operation(getv(f'sum_from_{i}_to', j), '+', op1, op2)

def prefix_sum_circuit (i, c):
    if i == 0:
        return add_operation(getv('out', 0), '+', getc(0), getv('in', 0))
    if calc_height(getv('out', i - 1)) < c:
        return add_operation(getv('out', i), '+', getv('out', i - 1), getv('in', i))
    return range_sum_circuit(0, i)

def max_sub_circuit (i, j):
    if i == j:
        max_or_0 = add_operation(getv('max_or_0', i), 'max', getv('in', i), getc(0))
        return (max_or_0, max_or_0, max_or_0)
    sz = ceil(log2(j - i + 1)) # first largest power of 2
    mid = i + 2 ** (sz - 1) - 1
    a_max_mid, a_max_l, a_max_r = max_sub_circuit(i, mid)
    b_max_mid, b_max_l, b_max_r = max_sub_circuit(mid + 1, j)
    max_mid = add_operation(getv(f'tmp_max_mid_from_{i}_to', j), 'max', a_max_mid, b_max_mid)
    max_mid = add_operation(getv(f'max_mid_from_{i}_to', j), 'max', max_mid,
        add_operation(getv(), '+', a_max_r, b_max_l)) # mid = max(a.mid, b.mid, a.r + b.l)
    max_l = add_operation(getv(f'max_l_from_{i}_to', j), 'max', a_max_l,
        add_operation(getv(), '+', range_sum_circuit(i, mid), b_max_l)) # l = max(a.l, a + b.l)
    max_r = add_operation(getv(f'max_r_from_{i}_to', j), 'max', b_max_r,
        add_operation(getv(), '+', range_sum_circuit(mid + 1, j), a_max_r)) # r = max(b.r, b + a.r)
    return (max_mid, max_l, max_r)

def print_circuit ():
    for res, value in operations.items():
        operator, op1, op2 = value
        res, op1, op2 = (str(variable_names[x]).replace('_', 'Z') for x in (res, op1, op2))
        print(res, '=', op1, operator, op2)

def main ():
    global variable_names
    task, n, c = (int(x) for x in input().split())
    for i in range(n):
        getv('in', i)
    if task == 1:
        res = range_sum_circuit(0, n - 1)
        # res = sum_circuit(list(range(n)))
        variable_names[res] = 'out[0]'
    elif task == 2:
        for i in range(n):
            res = prefix_sum_circuit(i, c)
            variable_names[res] = f'out[{i}]'
            variables_map[f'out[{i}]'] = res
    elif task == 3:
        res, _, _ = max_sub_circuit(0, n - 1)
        variable_names[res] = 'out[0]'
    print(task, n, c)
    print_circuit()

if __name__ == '__main__':
    main()
