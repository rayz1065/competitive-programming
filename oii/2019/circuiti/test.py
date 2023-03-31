import re
from random import randint
inputs = {}
variable_definitions = {}

def calc_height (variable):
    if variable not in variable_definitions:
        return 0
    op1, _, op2 = variable_definitions[variable]
    return max(calc_height(op1) + 1, calc_height(op2) + 1)

def parse_circuit ():
    while True:
        try:
            line = input()
            res = re.match('^(\w+\[\d+\]) = (\w+\[\d+\]|\d+) (\+|-|max) (\w+\[\d+\]|\d+)$', line)
            assert res is not None
            op_res, op1, operator, op2 = res.groups()
            variable_definitions[op_res] = (op1, operator, op2)
        except EOFError:
            break

def compute (variable):
    if variable in inputs:
        return inputs[variable]
    elif variable not in variable_definitions:
        return int(variable)
    op1, operator, op2 = variable_definitions[variable]
    if operator == '+':
        return compute(op1) + compute(op2)
    elif operator == 'max':
        return max(compute(op1), compute(op2))
    assert False, 'not implemented'

def test_sums (n):
    randomize_inputs(n)
    assert sum(inputs.values()) == compute('out[0]')

def test_pref_sums (n):
    randomize_inputs(n)
    total_sum = 0
    for i in range(n):
        total_sum += inputs[f'in[{i}]']
        assert total_sum == compute(f'out[{i}]')

def test_max_subarray(n):
    randomize_inputs(n)
    s = 0
    for i in range(n):
        curr = 0
        for j in range(i, n):
            curr += inputs[f'in[{j}]']
            s = max(s, curr)
    circuit_s = compute('out[0]')
    assert s == circuit_s, (inputs, 'expected', s, 'actual', circuit_s)

def randomize_inputs (n):
    global inputs
    inputs = { f'in[{i}]': randint(0, 100) for i in range(n) }

def main ():
    task, n, c = (int(x) for x in input().split())
    randomize_inputs(n)
    parse_circuit()
    if task == 1:
        tree_height = calc_height('out[0]')
        for test_idx in range(20):
            test_sums(n)
            print('Test', test_idx, 'passed...')
    elif task == 2:
        tree_height = max(calc_height(f'out[{i}]') for i in range(n))
        for test_idx in range(20):
            test_pref_sums(n)
            print('Test', test_idx, 'passed...')
    elif task == 3:
        tree_height = calc_height('out[0]')
        for test_idx in range(20):
            test_max_subarray(n)
            print('Test', test_idx, 'passed...')
    s_att = max(len(variable_definitions), 1) # number of circuit components
    score = 10 * min(1, c / tree_height) * min(1, 1100/s_att)
    print('All tests passed!')
    print('Tree height is', tree_height, '/', c)
    print('Used components: ', s_att, '/', 1100)
    print('Score is ', score, '/', 10)

if __name__ == '__main__':
    main()
