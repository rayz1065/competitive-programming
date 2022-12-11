import re
from math import lcm

class Monkey:
    def __init__(self, idx, items, operation, test_mod, if_true, if_false, inspected=0):
        self.idx = idx
        self.items = list(items)
        self.operation = operation
        self.test_mod = test_mod
        self.if_true = if_true
        self.if_false = if_false
        self.inspected = inspected

    def copy (self):
        return Monkey(self.idx, self.items, self.operation,
                      self.test_mod, self.if_true, self.if_false, self.inspected)

    def calculate_worry (self, item):
        b = item if self.operation[1] == 'old' else self.operation[1]
        if self.operation[0] == '+':
            return (item + b)
        elif self.operation[0] == '*':
            return (item * b)
        else:
            assert False

    def calculate_toss (self, item):
        return self.if_true if item % self.test_mod == 0 else self.if_false

    def __str__(self):
        items_str = ', '.join(str(x) for x in self.items)
        return f'Monkey {self.idx}: {items_str}'

def simulate (monkeys, relief=3):
    monkeys = [x.copy() for x in monkeys]
    for i in range(len(monkeys)):
        for item in monkeys[i].items:
            item = monkeys[i].calculate_worry(item) // relief
            toss = monkeys[i].calculate_toss(item)
            assert toss != i and 0 <= toss < len(monkeys), toss
            monkeys[toss].items.append(item)
        monkeys[i].inspected += len(monkeys[i].items)
        monkeys[i].items = [] # all tossed
    return monkeys

def read_input ():
    monkeys = []
    try:
        while True:
            idx = int(re.match(r'^Monkey (\d+):$', input()).group(1))
            items_str = re.match(r'^\s*Starting items: ([\d,\s]+)$', input()).group(1)
            operation = re.match(r'^\s*Operation: new = old (\+|\*) (\d+|old)$', input()).groups()
            test_mod = int(re.match(r'^\s*Test: divisible by (\d+)$', input()).group(1))
            if_true = int(re.match(r'^\s*If true: throw to monkey (\d+)$', input()).group(1))
            if_false = int(re.match(r'^\s*If false: throw to monkey (\d+)$', input()).group(1))
            if operation[1] != 'old':
                operation = (operation[0], int(operation[1]))
            items = (int(x) for x in items_str.split(', '))
            monkeys.append(Monkey(idx, items, operation, test_mod, if_true, if_false))
            assert input() == ''
    except EOFError:
        pass
    return monkeys

def manage_worry (monkeys):
    monkeys = [x.copy() for x in monkeys]
    common_div = lcm(*[x.test_mod for x in monkeys])
    for i in range(len(monkeys)):
        monkeys[i].items = [item % common_div for item in monkeys[i].items]
    return monkeys

def part_1 (monkeys):
    for _ in range(20):
        monkeys = simulate(monkeys)
        # for monkey in monkeys:
        #     print(monkey)
        # print()
    inspected = sorted(monkey.inspected for monkey in monkeys)
    return inspected[-1] * inspected[-2]

def part_2 (monkeys):
    STEPS = 10000
    for step_idx in range(STEPS):
        if step_idx % 100 == 0:
            progress = 100 * step_idx//STEPS
            print('simulating...', f'{progress}%', end='\r')
        monkeys = simulate(monkeys, 1)
        monkeys = manage_worry(monkeys)
    inspected = sorted(monkey.inspected for monkey in monkeys)
    print(' '*50, end='\r')
    return inspected[-1] * inspected[-2]

def main ():
    monkeys = read_input()
    print('part_1:', part_1(monkeys))
    print('part_2:', part_2(monkeys))

if __name__ == '__main__':
    main()
